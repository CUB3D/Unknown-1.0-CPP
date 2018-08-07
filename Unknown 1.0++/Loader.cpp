#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "UI.h"
#include "document.h"
#include "Log.h"

#include <map>
#include <iostream>
#include <memory>
#include <sstream>
#include "Entity/BasicRenderComponent.h"
#include "Entity/PhysicsBodyComponent.h"
#include "Entity/TimerComponent.h"
#include "Entity/ImageRenderComponent.h"

std::map<const char*, std::unique_ptr<Unknown::Sprite>> Unknown::Loader::spritePool;
std::map<const char*, std::unique_ptr<Unknown::Graphics::Image>> Unknown::Loader::imagePool;

Unknown::Sprite* Unknown::Loader::loadSprite(const char* name)
{
	if (spritePool.find(name) != spritePool.end())
	{
		std::unique_ptr<Sprite>& spritePrefab = spritePool.find(name)->second;
		Sprite* returnValue = spritePrefab->clone();
		return returnValue;
	}

	int x;
	int y;

	rapidjson::Document doc = readJSONFile(name);

	rapidjson::Value* xValue = getValue("X", rapidjson::Type::kNumberType, doc);

	if (xValue)
	{
		x = xValue->GetInt();
	}

	rapidjson::Value* yValue = getValue("Y", rapidjson::Type::kNumberType, doc);

	if (yValue)
	{
		y = yValue->GetInt();
	}

	std::unique_ptr<Sprite> sprite;

	std::unique_ptr<rapidjson::Value> typeValue(getValue("Type", rapidjson::Type::kStringType, doc));

	if (typeValue)
	{
		std::string type = typeValue->GetString();
		if (type == "Sprite")
		{
			sprite = std::unique_ptr<Sprite>(new Sprite(x, y));
		}
		else
		{
			if (type == "Image")
			{
				rapidjson::Value* imageValue = getValue("Image", rapidjson::Type::kStringType, doc);

				if (imageValue)
				{
					Graphics::Image* image = new Graphics::Image(imageValue->GetString());

					sprite = std::unique_ptr<Graphics::ImageSprite>(new Graphics::ImageSprite(x, y, image));
				}
			}
			else
			{
				if (type == "Animated")
				{
					rapidjson::Value* animationLocation = getValue("Animation", rapidjson::kStringType, doc);

					if (animationLocation)
					{
						Graphics::Animation* animation = UK_LOAD_ANIMATION(animationLocation->GetString());

						sprite = std::unique_ptr<Graphics::AnimatedSprite>(new Graphics::AnimatedSprite(x, y, animation));
					}
				}
			}
		}
	}

	spritePool[name] = std::move(sprite);

	return sprite.get();
}

std::shared_ptr<Unknown::Entity>
Unknown::Loader::loadEntityAt(const std::string &name, Scene &scene, double x, double y) {
	auto ent = loadEntity(name, scene);
	ent->setPosition(x, y);
	return ent;
}

std::shared_ptr<Unknown::Entity> Unknown::Loader::loadEntity(const std::string& name, Scene& scene)
{
	rapidjson::Document doc = readJSONFile(name.c_str());


	auto widthValue = getValue("Width", rapidjson::Type::kNumberType, doc);
	auto heightValue = getValue("Height", rapidjson::Type::kNumberType, doc);
	auto tagValue = getValue("Tag", rapidjson::Type::kStringType, doc);

	std::shared_ptr<Entity> ent;
	
	std::string tag = tagValue ? std::string(tagValue->GetString()) : "";
	ent = std::make_shared<Entity>(tag);

	if(widthValue && heightValue) {
		double width = widthValue->GetDouble();
		double height = heightValue->GetDouble();
		ent->size = Dimension<double>(width, height);
	} else {
		printf("[WARN] Entity %s has no size\n", name.c_str());
		return ent;
	}

	auto xvalue = getValue("X", rapidjson::Type::kNumberType, doc);
	auto yvalue = getValue("Y", rapidjson::Type::kNumberType, doc);

	if(xvalue) {
		ent->position.x = xvalue->GetDouble();
	}

	if(yvalue) {
		ent->position.y = yvalue->GetDouble();
	}

	auto components = getValue("Components", rapidjson::Type::kObjectType, doc);

	if(!components) {
		printf("[WARN] Entity %s has no components\n", name.c_str());
		return ent;
	}

	for(auto x = components->GetObject().MemberBegin(); x != components->MemberEnd(); x++) {
		auto component = x->value.GetObject();

		auto typeValue = component.FindMember("Type");
		if(typeValue == component.MemberEnd()) {
			printf("[ERR] Component %s of entity %s has no type\n", x->name.GetString(), name.c_str());
			return ent;
		}

		auto typeString = std::string(typeValue->value.GetString());

		// TODO: migrate all loading to this if it works on windows
		std::shared_ptr<ClassInfoBase> classInfo = (*Reflex::getInstance().m1)[typeString + "Component"];
		if(classInfo) {
		    UK_LOG_INFO("Found class info for", typeString);
			std::shared_ptr<Component> instance((Component*)classInfo->newRawInstance());

			// For all of the attributes of this component
			for(auto attr = component.MemberBegin(); attr != component.MemberEnd(); attr++) {
				std::string name = std::string(attr->name.GetString());
				UK_LOG_INFO("Loading attr for", name);

				// Find the field in the class with that name
				std::shared_ptr<FieldDataBase> field = classInfo->fields[name];
				if(field) {
				    UK_LOG_INFO("Found field", field->name);
					if(field->getType(instance.get()) == typeid(int)) {
						field->setValue(instance.get(), attr->value.GetInt());
					}
					if(field->getType(instance.get()) == typeid(Colour)) {
						field->setValue(instance.get(), *getColourFromString(attr->value.GetString()));
					}
				}
			}

			ent->components.push_back(instance);
		}

		// Loading basic renderers
		if(typeString == "BasicRenderer") {
			auto colourValue = component.FindMember("Colour");
			Colour col = Colour::BLUE;

			if(colourValue != component.MemberEnd()) {
				col = *getColourFromString(colourValue->value.GetString());
			}

			auto renderValue = component.FindMember("RenderScale");
			int renderScale = 1;

			if (renderValue != component.MemberEnd()) {
				renderScale = renderValue->value.GetInt();
			}

			//printf("rs: %d, col{%d, %d, %d}\n", renderScale, col.red, col.green, col.blue);

			ent->components.push_back(std::make_shared<BasicRenderComponent>(col, renderScale));
		}

		if(typeString == "ImageRenderer") {
            auto renderValue = component.FindMember("RenderScale");
            int renderScale = 1;

            if (renderValue != component.MemberEnd()) {
                renderScale = renderValue->value.GetInt();
            }


		    auto filenameValue = component.FindMember("File");
		    if(filenameValue != component.MemberEnd()) {
		        ent->components.push_back(std::make_shared<ImageRenderComponent>(std::string(filenameValue->value.GetString()), renderScale));
		    }
		}


		if(typeString == "Collider") {
		    auto colliderTypeValue = component.FindMember("ColliderType");
			b2BodyType bodyType = b2_staticBody;

		    if(colliderTypeValue != component.MemberEnd()) {
		        auto colliderTypeString = std::string(colliderTypeValue->value.GetString());

		        if(colliderTypeString == "Dynamic") {
		            bodyType = b2_dynamicBody;
		        }

		        if(colliderTypeString == "Static") {
		        	bodyType = b2_staticBody;
		        }
		    }


		    auto bulletValue = component.FindMember("Bullet");
		    bool bullet = false;
		    if(bulletValue != component.MemberEnd()) {
		        bullet = bulletValue->value.GetBool();
		    }

		    auto groupIndexValue = component.FindMember("GroupIndex");
		    int groupIndex = 0;

		    if(groupIndexValue != component.MemberEnd()) {
		        groupIndex = groupIndexValue->value.GetInt();
		    }

		    auto phys = std::make_shared<PhysicsBodyComponent>(ent, &scene, bodyType, bullet, groupIndex);


		    auto maxSpeedValue = component.FindMember("MaxSpeed");
		    if(maxSpeedValue != component.MemberEnd()) {
		    	double maxSpeed = maxSpeedValue->value.GetDouble();
		    	phys->maxSpeed = maxSpeed;
		    }

            ent->components.push_back(phys);
		}


		if(typeString == "Timer") {
			auto delayValue = component.FindMember("Delay");
			if(delayValue != component.MemberEnd()) {
				if(delayValue->value.IsInt()) {
					ent->components.push_back(std::make_shared<TimerComponent>(delayValue->value.GetInt()));
				}
			}
		}
	}

	return ent;
}

Unknown::Graphics::Animation* Unknown::Loader::loadAnimation(const char* name)
{
	rapidjson::Document json = readJSONFile(name);

	std::unique_ptr<::Unknown::Graphics::Animation> animation(new ::Unknown::Graphics::Animation());

	for (rapidjson::Value::MemberIterator member = json.MemberBegin(); member != json.MemberEnd(); member++)
	{
		if (member->name == "Frame")
		{
			std::string imageLocation = member->value.FindMember("Image")->value.GetString();
			std::unique_ptr<Graphics::Image> image = loadImage(imageLocation.c_str());
			
			rapidjson::Value::MemberIterator delayMemeber = member->value.FindMember("Delay");

			int delay = 0;

			if (delayMemeber != member->value.MemberEnd())
			{
				delay = delayMemeber->value.GetInt();
			}

			::Unknown::Graphics::AnimationFrame animationFrame;

			animationFrame.delayms = delay;
			animationFrame.frameImage = image.get();

			animation->addFrame(animationFrame);
		}
	}

	rapidjson::Value::MemberIterator overallDelayMember = json.FindMember("Delay");

	if (overallDelayMember != json.MemberEnd())
	{
		int overallDelay = overallDelayMember->value.GetInt();

		for (int i = 0; i < animation->frames.size(); i++)
		{
			animation->frames[i].delayms = overallDelay;
		}
	}

	return animation.get();
}

std::unique_ptr<::Unknown::Graphics::Image> Unknown::Loader::loadImage(const char* name)
{
	if (imagePool.find(name) != imagePool.end())
	{
		std::unique_ptr<Graphics::Image>& imagePrefab = imagePool.find(name)->second;
		//Clone so that original remains unmodified
		return imagePrefab->clone();
	}

	std::unique_ptr<Graphics::Image> image(new Graphics::Image(name));

	//Give the map ownership of the pointer
	imagePool[name] = std::move(image);

	//Again, clone to keep original unmodified
    // After std::move image.get() -> nullptr therefore clone the one in the pool
	return imagePool[name]->clone();
}

::Unknown::UIContainer Unknown::Loader::loadUI(const std::string &name)
{
	rapidjson::Document doc = readJSONFile(name.c_str());

	UIContainer container;

	for (auto member = doc.MemberBegin(); member != doc.MemberEnd(); member++)
	{
		std::string componenetName = member->name.GetString();
		std::string typeString = member->value.FindMember("Type")->value.GetString();

        std::shared_ptr<UIComponent> comp = std::make_shared<UIComponent>(UI_NULL);

        if(typeString == "Rect")
        {
            comp = std::make_shared<RectComponent>();
        }

		if (typeString == "Square")
		{
            comp = std::make_shared<SquareComponent>();
		}

		if(typeString == "Text")
		{
            comp = std::make_shared<TextComponent>();
		}

		if(typeString == "Button")
		{
            comp = std::make_shared<ButtonComponent>();
		}

        if(typeString == "TextBox")
        {
        	TextBoxComponent* comp_ = new TextBoxComponent();

            comp = std::shared_ptr<TextBoxComponent>(comp_);

            auto numerical = member->value.FindMember("Numerical");

            if(numerical != member->value.MemberEnd()) {
                comp_->isNumerical = numerical->value.GetBool();
            }
        }

		comp->name = componenetName;

		auto colour = member->value.FindMember("Colour");

		if (colour != member->value.MemberEnd())
		{
			std::string colourString = colour->value.GetString();
			comp->colour = getColourFromString(colourString);

			std::cout << "Colour loaded: (" << comp->colour->alpha << ", " << comp->colour->red << ", " << comp->colour->green << ", " << comp->colour->blue << ")" << std::endl;
		}

		auto insideComponent = member->value.FindMember("InsideComponent");

		if (insideComponent != member->value.MemberEnd())
		{
			std::string parentName = insideComponent->value.GetString();
			comp->parentName = parentName;
		}

		auto content = member->value.FindMember("Content");

		if (content != member->value.MemberEnd())
		{
			std::string contentString = content->value.GetString();
			comp->content = contentString;
		}

        std::shared_ptr<UIComponent> parent;

        if (!comp->parentName.empty())
        {
            for (auto &component2 : container.components)
            {
                if (comp->parentName == component2->name)
                {
                    parent = component2;
                    break;
                }
            }

            if(!parent)
            {
                std::cout << "Error: no parent found for " << comp->name << std::endl;
            }
        }

        auto bounds = member->value.FindMember("Bounds");

        if (bounds != member->value.MemberEnd())
        {
            int boundsArray[4];

            for (int x = 0; x < bounds->value.Size(); x++)
            {
                if(bounds->value[x].IsString())
                {
                    std::string location = bounds->value[x].GetString();
                    std::vector<std::string> tokens = tokenise(location, {"+", "-", "minX", "minY", "maxX", "maxY"});

                    int position = 0;
                    std::string operation;
                    for(auto token : tokens)
                    {
                        if(token == "minX")
                        {
                            position = parent->location.x;
                        }

                        if(token == "minY")
                        {
                            position = parent->location.y;
                        }

                        if(token == "maxX")
                        {
                            position = parent->location.x + parent->size.width;
                        }

                        if(token == "maxY")
                        {
                            position = parent->location.y + parent->size.height;
                        }

                        if(token == "+")
                        {
                            operation = "+";
                        }

                        if(token == "-")
                        {
                            operation = "-";
                        }

                        bool isNumber = true;

                        for(char c : token)
                        {
                            if(!isCharCodeNumber(&c))
                            {
                                isNumber = false;
                            }
                        }

                        if(isNumber)
                        {
                            if(operation == "+")
                            {
                                position += std::stoi(token);
                            }
                            if(operation == "-")
                            {
                                position -= std::stoi(token);
                            }
                        }
                    }
                    boundsArray[x] = position;
                }
                if(bounds->value[x].IsInt())
                {
                    boundsArray[x] = bounds->value[x].GetInt();
                    std::cout << "Bounds[" << x << "] = " << boundsArray[x] << std::endl;
                }
            }

            comp->location = Point<int>(boundsArray[0], boundsArray[1]);
            comp->size = Dimension<int>(boundsArray[2], boundsArray[3]);

            std::cout << "W = " << comp->size.width << "; H = " << comp->size.height << std::endl;

            if(comp->size.width == -1)
            {
                comp->size.width = getUnknown()->screenSize->width;
            }

            if(comp->size.height == -1)
            {
                comp->size.height = getUnknown()->screenSize->height;
            }
        }

        container.components.push_back(comp);
	}

    UK_LOG_INFO("Loaded UI data, found", intToString(container.components.size()), "components");

	for (auto& comp : container.components)
	{
		std::cout << "Component: " << comp->name << ", Bounds (" << comp->location.x << ", " << comp->location.y << ", " << comp->size.width << ", " << comp->size.height << ")" << std::endl;
		//std::cout << "Component: " << comp->name << ", Bounds (" << comp->offsetBounds[0] << ", " << comp.offsetBounds[1] << ", " << comp.offsetBounds[2] << ", " << comp.offsetBounds[3] << ")" << std::endl;
	}

	return container;
}
