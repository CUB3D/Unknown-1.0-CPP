#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "Entity.h"
#include "UI.h"
#include "rapidjson\document.h"
#include "Utils.h"

#include <map>

#include <iostream>

std::map<const char*, Unknown::Sprite*> Unknown::Loader::spritePool;
std::map<const char*, Unknown::Entity*> Unknown::Loader::entityPool;
std::map<const char*, Unknown::Graphics::Image*> Unknown::Loader::imagePool;

Unknown::Sprite* Unknown::Loader::loadSprite(const char* name)
{
	if (spritePool.find(name) != spritePool.end())
	{
		Sprite* spritePrefab = spritePool.find(name)->second;
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

	Sprite* sprite = NULL;

	rapidjson::Value* typeValue = getValue("Type", rapidjson::Type::kStringType, doc);

	if (typeValue)
	{
		std::string type = typeValue->GetString();
		if (type == "Sprite")
		{
			sprite = new Sprite(x, y);
		}
		else
		{
			if (type == "Image")
			{
				rapidjson::Value* imageValue = getValue("Image", rapidjson::Type::kStringType, doc);

				if (imageValue)
				{
					Graphics::Image* image = new Graphics::Image(imageValue->GetString());

					sprite = new Graphics::ImageSprite(x, y, image);
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

						sprite = new Graphics::AnimatedSprite(x, y, animation);
					}
				}
			}
		}
	}

	spritePool[name] = sprite;

	return sprite;
}

Unknown::Entity* Unknown::Loader::loadEntity(const char* name)
{
	if (entityPool.find(name) != entityPool.end())
	{
		Entity* entityPrefab = entityPool.find(name)->second;
		Entity* returnValue = entityPrefab->clone();
		return returnValue;
	}

	rapidjson::Document doc = readJSONFile(name);

	rapidjson::Value* spriteValue = getValue("Sprite", rapidjson::Type::kStringType, doc);

	Sprite* sprite = NULL;

	if (spriteValue)
	{
		std::string spriteName = spriteValue->GetString();

		sprite = UK_LOAD_SPRITE(spriteName.c_str());
	}

	Entity* entity = NULL;

	rapidjson::Value* typeValue = getValue("Type", rapidjson::Type::kStringType, doc);

	if (typeValue)
	{
		std::string type = typeValue->GetString();

		if (type == "Entity")
		{
			entity = new Entity(sprite);
		}
		else
		{
			if (type == "TwoState")
			{
				entity = new TwoStateEntity(sprite);
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

					entity = new HealthEntity(sprite, health, maxHealth);
				}
			}
		}
	}

	entityPool[name] = entity;

	return entity;
}

Unknown::Graphics::Animation* Unknown::Loader::loadAnimation(const char* name)
{
	rapidjson::Document json = readJSONFile(name);

	::Unknown::Graphics::Animation* animation = new ::Unknown::Graphics::Animation();

	for (rapidjson::Value::MemberIterator member = json.MemberBegin(); member != json.MemberEnd(); member++)
	{
		if (member->name == "Frame")
		{
			std::string imageLocation = member->value.FindMember("Image")->value.GetString();
			Graphics::Image* image = new Graphics::Image(imageLocation.c_str());
			
			rapidjson::Value::MemberIterator delayMemeber = member->value.FindMember("Delay");

			int delay = 0;

			if (delayMemeber != member->value.MemberEnd())
			{
				delay = delayMemeber->value.GetInt();
			}

			::Unknown::Graphics::AnimationFrame animationFrame;

			animationFrame.delayms = delay;
			animationFrame.frameImage = image;

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

	return animation;
}

::Unknown::Graphics::Image* Unknown::Loader::loadImage(const char* name)
{
	if (imagePool.find(name) != imagePool.end())
	{
		Graphics::Image* imagePrefab = imagePool.find(name)->second;
		Graphics::Image* returnValue = imagePrefab->clone();
		return returnValue;
	}

	Graphics::Image* image = new Graphics::Image(name);

	imagePool[name] = image;

	return image;
}

::Unknown::UIContainer Unknown::Loader::loadUI(const char * name)
{
	rapidjson::Document doc = readJSONFile(name);

	UIContainer container;

	for (auto member = doc.MemberBegin(); member != doc.MemberEnd(); member++)
	{
		std::string componenetName = member->name.GetString();
		std::string typeString = member->value.FindMember("Type")->value.GetString();

        UIComponent* comp = nullptr;

        if(typeString == "Rect")
        {
            comp = new RectComponent();
            comp->type = UI_RECT;
        }

		comp->name = componenetName;

		auto bounds = member->value.FindMember("Bounds");

		if (bounds != member->value.MemberEnd())
		{
			int boundsArray[4];

			int x = 0;

			for (int x = 0; x < bounds->value.Size(); x++)
			{
				boundsArray[x] = bounds->value[x].GetInt();
			}

            comp->location = {boundsArray[0], boundsArray[1]};
            comp->size = {boundsArray[2], boundsArray[3]};
		}

		auto colour = member->value.FindMember("Colour");

		if (colour != member->value.MemberEnd())
		{
			std::string colourString = colour->value.GetString();
			comp->colour = getColourFromString(colourString);

			//std::cout << "Colour loaded: (" << comp.colour->alpha << ", " << comp.colour->red << ", " << comp.colour->green << ", " << comp.colour->blue << ")" << std::endl;
		}

		auto insideComponent = member->value.FindMember("InsideComponent");

		if (insideComponent != member->value.MemberEnd())
		{
			std::string parentName = insideComponent->value.GetString();
			comp->parentName = parentName;
		}

		auto offsetBounds = member->value.FindMember("OffsetBounds");
        int boundsArray[4];

		if (offsetBounds != member->value.MemberEnd())
		{
			for (int x = 0; x < offsetBounds->value.Size(); x++)
			{
				boundsArray[x] = offsetBounds->value[x].GetInt();
			}
		}

		auto content = member->value.FindMember("Content");

		if (content != member->value.MemberEnd())
		{
			std::string contentString = content->value.GetString();
			comp->content = contentString;
		}

		// calculate OffsetBounds for a component

		if (!comp->parentName.empty())
		{
			UIComponent* parent = nullptr;

			for (auto component2 : container.components)
			{
				if (comp->parentName == component2->name)
				{
					parent = component2;
					break;
				}
			}

			if (parent == nullptr)
			{
				std::cout << "Error: no parent found for " << comp->name << std::endl;
			}


            comp->location.x = parent->location.x + boundsArray[0];
            comp->location.y = parent->location.y + boundsArray[1];
            comp->size.width = parent->size.width + boundsArray[2];
            comp->size.height = parent->size.height + boundsArray[3];
		}

		container.components.push_back(comp);
	}

	std::cout << "Loaded UI data, found " << container.components.size() << " components" << std::endl;

	//for (auto comp : container.components)
	//{
	//	std::cout << "Component: " << comp.name << ", Bounds (" << comp.location.x << ", " << comp.location.y << ", " << comp.size.width << ", " << comp.size.height << ")" << std::endl;
	//	std::cout << "Component: " << comp.name << ", Bounds (" << comp.offsetBounds[0] << ", " << comp.offsetBounds[1] << ", " << comp.offsetBounds[2] << ", " << comp.offsetBounds[3] << ")" << std::endl;
	//}

	return container;
}
