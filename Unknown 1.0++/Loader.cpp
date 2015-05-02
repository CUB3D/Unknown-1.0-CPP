#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "Entity.h"
#include "rapidjson\document.h"

Unknown::Sprite* Unknown::Loader::loadSprite(const char* name)
{
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

	return sprite;
}

Unknown::Entity* Unknown::Loader::loadEntity(const char* name)
{
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


	return entity;
}