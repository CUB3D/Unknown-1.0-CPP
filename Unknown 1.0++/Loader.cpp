#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "Entity.h"
#include "rapidjson\document.h"

#include <map>

#include <iostream>

std::map<const char*, Unknown::Sprite*> Unknown::Loader::spritePool;
std::map<const char*, Unknown::Entity*> Unknown::Loader::entityPool;

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

Unknown::Graphics::Animation Unknown::Loader::loadAnimation(const char* name)
{
	rapidjson::Document json = readJSONFile(name);

	::Unknown::Graphics::Animation animation;

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

			animation.addFrame(animationFrame);
		}
	}

	rapidjson::Value::MemberIterator overallDelayMember = json.FindMember("Delay");

	if (overallDelayMember != json.MemberEnd())
	{
		int overallDelay = overallDelayMember->value.GetInt();

		for (int i = 0; i < animation.frames.size(); i++)
		{
			animation.frames[i].delayms = overallDelay;
		}
	}

	return animation;
}