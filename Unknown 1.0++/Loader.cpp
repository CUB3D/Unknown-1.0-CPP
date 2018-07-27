#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "Entity.h"
#include "UI.h"
#include "document.h"
#include "Log.h"

#include <map>
#include <iostream>
#include <memory>
#include <sstream>

std::map<const char*, std::unique_ptr<Unknown::Sprite>> Unknown::Loader::spritePool;
std::map<const char*, std::unique_ptr<Unknown::Entity>> Unknown::Loader::entityPool;
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

std::unique_ptr<Unknown::Entity> Unknown::Loader::loadEntity(const char* name)
{
	if (entityPool.find(name) != entityPool.end())
	{
		std::unique_ptr<Entity>& entityPrefab = entityPool.find(name)->second;
		return std::unique_ptr<Entity>(entityPrefab->clone());
	}

	rapidjson::Document doc = readJSONFile(name);

	rapidjson::Value* spriteValue = getValue("Sprite", rapidjson::Type::kStringType, doc);

	Sprite* sprite = NULL;

	if (spriteValue)
	{
		std::string spriteName = spriteValue->GetString();

		sprite = UK_LOAD_SPRITE(spriteName.c_str());
	}

	std::unique_ptr<Entity> entity;

	std::unique_ptr<rapidjson::Value> typeValue(getValue("Type", rapidjson::Type::kStringType, doc));

	if (typeValue)
	{
		std::string type = typeValue->GetString();

		if (type == "Entity")
		{
			entity = std::unique_ptr<Entity>(new Entity(sprite));
		}
		else
		{
			if (type == "TwoState")
			{
				entity = std::unique_ptr<Entity>(new TwoStateEntity(sprite));
			}
			else
			{
				if (type == "Health")
				{
					int health = 0;
					int maxHealth = 0;

					rapidjson::Value* healthValue = getValue("Health", rapidjson::Type::kNumberType, doc);

					if (healthValue)
					{
						health = healthValue->GetInt();
					}

					rapidjson::Value* maxHealthValue = getValue("MaxHealth", rapidjson::Type::kNumberType, doc);

					if (maxHealthValue)
					{
						maxHealth = maxHealthValue->GetInt();
					}
					else
					{
						maxHealth = health;
					}

					entity = std::unique_ptr<HealthEntity>(new HealthEntity(sprite, health, maxHealth));
				}
			}
		}
	}

	entityPool[name] = std::move(entity);

	return entity;
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

        std::shared_ptr<UIComponent> parent = nullptr;

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

    log(UK_LOG_LEVEL_INFO, concat("Loaded UI data, found", intToString(container.components.size()), "components"));

	for (auto& comp : container.components)
	{
		std::cout << "Component: " << comp->name << ", Bounds (" << comp->location.x << ", " << comp->location.y << ", " << comp->size.width << ", " << comp->size.height << ")" << std::endl;
		//std::cout << "Component: " << comp->name << ", Bounds (" << comp->offsetBounds[0] << ", " << comp.offsetBounds[1] << ", " << comp.offsetBounds[2] << ", " << comp.offsetBounds[3] << ")" << std::endl;
	}

	return container;
}
