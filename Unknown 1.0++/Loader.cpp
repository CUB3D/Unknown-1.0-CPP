#include "stdafx.h"
#include "Loader.h"

#include "document.h"
#include "Utils.h"
#include "UI.h"
#include "Log.h"

#include <map>
#include <iostream>
#include <memory>
#include <sstream>
#include "Entity/BasicRenderComponent.h"
#include "Entity/PhysicsBodyComponent.h"
#include "Entity/TimerComponent.h"
#include "Entity/ImageRenderComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::map<std::string, std::shared_ptr<Unknown::Graphics::Image>> Unknown::Loader::imagePool;

std::shared_ptr<Unknown::Entity>
Unknown::Loader::loadEntityAt(const std::string &name, double x, double y) {
	auto ent = loadEntity(name);
	ent->setPosition(x, y);
	return ent;
}

std::shared_ptr<Unknown::Entity> Unknown::Loader::loadEntity(const std::string &name)
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
		printf("[ERR] Entity %s has no size\n", name.c_str());
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

#ifdef WIN32
	// I absolutely dispise the individual who decided to put the inverse of this define in windows.h
	// What is this, some kind of sick joke
#define GetObjectA GetObject
#endif

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
			auto phys = std::make_shared<PhysicsBodyComponent>(ent);

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

		        if(colliderTypeString == "Kinematic") {
					bodyType = b2_kinematicBody;
				}
		    }
		    phys->bodyDefinition.type = bodyType;


		    auto bulletValue = component.FindMember("Bullet");
		    bool bullet = false;
		    if(bulletValue != component.MemberEnd()) {
		        bullet = bulletValue->value.GetBool();
		    }
		    phys->bodyDefinition.bullet = bullet;

		    auto groupIndexValue = component.FindMember("GroupIndex");
		    int groupIndex = 0;
		    if(groupIndexValue != component.MemberEnd()) {
		        groupIndex = groupIndexValue->value.GetInt();
		    }
		    phys->filter.groupIndex = groupIndex;


		    auto maxSpeedValue = component.FindMember("MaxSpeed");
		    if(maxSpeedValue != component.MemberEnd()) {
		    	double maxSpeed = maxSpeedValue->value.GetDouble();
		    	phys->maxSpeed = maxSpeed;
		    }

		    bool sensor = false;
		    auto sensorValue = component.FindMember("Sensor");
		    if(sensorValue != component.MemberEnd()) {
		        sensor = sensorValue->value.GetBool();
		    }
            phys->fixtureDefinition.isSensor = sensor;

		    bool fixedRotation = true;
		    auto frValue = component.FindMember("FixedRotation");
		    if(frValue != component.MemberEnd()) {
		        fixedRotation = frValue->value.GetBool();
		    }
		    phys->bodyDefinition.fixedRotation = fixedRotation;

		    float density = 1;
		    auto dValue = component.FindMember("Density");
		    if(dValue != component.MemberEnd()) {
		        density = dValue->value.GetFloat();
		    }
		    phys->fixtureDefinition.density = density;

		    double radius = 1;
		    auto rValue = component.FindMember("Radius");
		    if(rValue != component.MemberEnd()) {
		        radius = rValue->value.GetDouble();
		    }
		    phys->circle.m_radius = radius;

		    double restitution = 0;
		    auto reValue = component.FindMember("Restitution");
		    if(reValue != component.MemberEnd()) {
		        restitution = reValue->value.GetDouble();
		    }
		    phys->fixtureDefinition.restitution = restitution;


		    b2Shape* shape = &phys->shape;
		    auto shapeValue = component.FindMember("Shape");
		    if(shapeValue != component.MemberEnd()) {
		        std::string shapeName = std::string(shapeValue->value.GetString());
		        if(shapeName == "Circle") {
                    shape = &phys->circle;
                }
		    }
		    phys->fixtureDefinition.shape = shape;


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
			std::shared_ptr<Graphics::Image> image = loadImage(imageLocation.c_str());
			
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

	return animation.get();
}

std::shared_ptr<::Unknown::Graphics::Image> Unknown::Loader::loadImage(const std::string &name) {
	if (imagePool.find(name) != imagePool.end()) {
		return imagePool.find(name)->second;
	}

	std::shared_ptr<Graphics::Image> image = std::make_shared<Graphics::Image>(name);

	// copy to map
	imagePool[name] = image;

	//Again, clone to keep original unmodified
    // After std::move image.get() -> nullptr therefore clone the one in the pool
	//return imagePool[name]->clone();
	return image;
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

        if(typeString == "Image") {
            comp = std::make_shared<ImageComponent>();
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
                   // std::cout << "Bounds[" << x << "] = " << boundsArray[x] << std::endl;
                }
            }

            comp->location = Point<int>(boundsArray[0], boundsArray[1]);
            comp->size = Dimension<int>(boundsArray[2], boundsArray[3]);

            //std::cout << "W = " << comp->size.width << "; H = " << comp->size.height << std::endl;

            if(comp->size.width == -1)
            {
                comp->size.width = getUnknown().screenSize->width;
            }

            if(comp->size.height == -1)
            {
                comp->size.height = getUnknown().screenSize->height;
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

std::shared_ptr<MeshContainer> Unknown::Loader::loadModel(const std::string &name) {
    std::function<void(aiNode*, const aiScene*, std::vector<aiMesh*>&)> recurseMeshTree = [&recurseMeshTree](aiNode* node, const aiScene* sce, std::vector<aiMesh*>& meshes) {
        for(int i = 0; i < node->mNumMeshes; i++) {
            meshes.push_back(sce->mMeshes[node->mMeshes[i]]);
        }

        for(int i = 0; i < node->mNumChildren; i++) {
            recurseMeshTree(node->mChildren[i], sce, meshes);
        }
    };

    auto loadMaterialTextures = [](aiMaterial* mat, aiTextureType type, const std::string& typeStr, std::vector<TextureInfo>& vec) {
        for(int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str(typeStr);
            mat->GetTexture(type, i, &str);
            std::string s = std::string(str.C_Str());
            vec.push_back(::Unknown::getRendererBackend()->loadTexture(s));
        }
    };



	auto meshContainer = std::make_shared<MeshContainer>();

	Assimp::Importer importer;

	//TODO: use filesystem
	const aiScene* scene = importer.ReadFile(name, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes);

    std::vector<aiMesh*> meshes;
    recurseMeshTree(scene->mRootNode, scene, meshes);

	for(auto& mesh : meshes) {
		Mesh m;
		printf("Found %d verticies\n", mesh->mNumVertices);
		for(int i = 0; i < mesh->mNumVertices; i ++) {

			auto& v = mesh->mVertices[i];
			m.verticies.push_back(glm::vec3(v.x, v.y, v.z));

			if(mesh->HasNormals()) {
				auto& n = mesh->mNormals[i];
				m.normals.push_back(glm::vec3(n.x, n.y, n.z));
			}

			if(mesh->mTextureCoords[0]) {
				auto& t = mesh->mTextureCoords[0][i];
				m.uvs.push_back(glm::vec2(t.x, t.y));
			} else {
				m.uvs.emplace_back(0.0f, 0.0f);
			}
		}

		for(int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for(int j = 0; j < face.mNumIndices; j++) {
				m.indicies.push_back(face.mIndices[j]);
			}
		}
		// Check for materials
		//TODO: remove
		if(mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
            loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse", m.diffuseMaps);
            loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular", m.specularMaps);
		}

		printf("Found %d indicies\n", m.indicies.size());

		meshContainer->meshes.push_back(m);
	}

	return meshContainer;
}
