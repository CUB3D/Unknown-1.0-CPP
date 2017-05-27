#include "stdafx.h"
#include "Loader.h"

#include "Sprite.h"
#include "Utils.h"
#include "Entity.h"
#include "UI.h"
#include "document.h"
#include "Utils.h"
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
	return image->clone();
}

::Unknown::UIContainer Unknown::Loader::loadUI(const char * name)
{
	rapidjson::Document doc = readJSONFile(name);

	UIContainer container;

	for (auto member = doc.MemberBegin(); member != doc.MemberEnd(); member++)
	{
		std::string componenetName = member->name.GetString();
		std::string typeString = member->value.FindMember("Type")->value.GetString();

        std::unique_ptr<UIComponent> comp(new UIComponent(UI_NULL));

        if(typeString == "Rect")
        {
			comp = std::unique_ptr<UIComponent>(new RectComponent());
        }

		if (typeString == "Square")
		{
			comp = std::unique_ptr<UIComponent>(new SquareComponent());
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
			for (auto& component2 : container.components)
			{
				if (comp->parentName == component2->name)
				{
					comp->location.x = component2->location.x + boundsArray[0];
					comp->location.y = component2->location.y + boundsArray[1];
					comp->size.width = component2->size.width + boundsArray[2];
					comp->size.height = component2->size.height + boundsArray[3];
					goto done; // Found the parent, now jump to end
				}
			}
			
			// If a parent is found then this will be skipped
			std::cout << "Error: no parent found for " << comp->name << std::endl;
		}

		done:{
			container.components.push_back(std::move(comp));
		}
	}

	std::stringstream tempStream;
	tempStream << container.components.size();

	UK_LOG_INFO(::Unknown::concat({ "Loaded UI data, found ", tempStream.str(), " components" }).c_str());

	tempStream.clear();

	//for (auto comp : container.components)
	//{
	//	std::cout << "Component: " << comp.name << ", Bounds (" << comp.location.x << ", " << comp.location.y << ", " << comp.size.width << ", " << comp.size.height << ")" << std::endl;
	//	std::cout << "Component: " << comp.name << ", Bounds (" << comp.offsetBounds[0] << ", " << comp.offsetBounds[1] << ", " << comp.offsetBounds[2] << ", " << comp.offsetBounds[3] << ")" << std::endl;
	//}

	return container;
}
