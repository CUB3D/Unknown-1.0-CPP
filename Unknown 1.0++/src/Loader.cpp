#include "Loader.h"

#include <rapidjson/document.h>
#include <Utils.h>
#include <UI.h>
#include <core/log/Log.h>

#include <map>
#include <iostream>
#include <memory>
#include <sstream>
#include <Entity/BasicRenderComponent.h>
#include <Entity/PhysicsBodyComponent.h>
#include <Entity/TimerComponent.h>
#include <Entity/ImageRenderComponent.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Settings/SettingsParser.h>
#include <Entity/EntityPrototype.h>
#include <Entity/Entity.h>

// TODO: make create ent obj, add proto
std::shared_ptr<Unknown::Entity>
Unknown::Loader::loadEntityAt(const std::string &name, double x, double y) {
	auto ent = loadEntity(name);
	ent->setPosition(x, y);
	return ent;
}

//TODO: rename to loadentityproto
std::shared_ptr<Unknown::Entity> Unknown::Loader::loadEntity(const std::string &name)
{
    UK_INFO("Load Entity:", name);
    //TODO: Scene graph loader
    //TODO: remove massive comment
    //TODO: find way to handle the string->enum conversion (for bodydef) (wonder if rttr handles enums)
    return std::make_shared<Entity>(loadEntityPrototype(name));
}

Unknown::Animation* Unknown::Loader::loadAnimation(const char* name)
{
    UK_INFO("Load anim", name);
	rapidjson::Document json = SettingsParser::loadDocument(name);

	std::unique_ptr<Animation> animation = std::make_unique<Animation>();

	for (rapidjson::Value::MemberIterator member = json.MemberBegin(); member != json.MemberEnd(); member++)
	{
		if (member->name == "Frame")
		{
			std::string imageLocation = member->value.FindMember("Image")->value.GetString();
			auto image = std::make_shared<Image>(imageLocation.c_str());
			
			rapidjson::Value::MemberIterator delayMemeber = member->value.FindMember("Delay");

			int delay = 0;

			if (delayMemeber != member->value.MemberEnd())
			{
				delay = delayMemeber->value.GetInt();
			}

			AnimationFrame animationFrame;

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

::Unknown::UIContainer Unknown::Loader::loadUI(const std::string &name)
{
    UK_INFO("Loading UI", name);
	rapidjson::Document doc = SettingsParser::loadDocument(name);

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
			//comp->colour = getColourFromString(colourString);

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

    UK_INFO("Loaded UI data, found", std::to_string(container.components.size()), "components");

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
            UK_INFO("Loading mat texture:", s);
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

Unknown::EntityPrototype Unknown::Loader::loadEntityPrototype(const std::string &name) {
    // Load json doc
    auto document = SettingsParser::loadDocument(name);

    EntityPrototype proto;
    rttr::variant data(&proto);
    auto dataType = rttr::type::get<EntityPrototype>();

    // Parse easy fields for proto
    SettingsParser::parseJSONDocument(data, dataType, document);

    //Parse component list
    auto componentList = document.FindMember("Components");

    if(componentList != document.MemberEnd()) {
        for(auto& comp : componentList->value.GetObject()) {
            // Create instance of the component
            auto componentType = rttr::type::get_by_name(std::string(comp.name.GetString()));

            if(!componentType.is_valid()) {
                UK_ERROR("Invalid type", comp.name.GetString(), "for entity", name);
                continue;
            }

            auto componentInstance = componentType.create();

            // Load its vars from json
            for(auto& property : componentType.get_properties()) {
                auto jsonProperty = comp.value.GetObject().FindMember(property.get_name().to_string().c_str());
                if(jsonProperty != comp.value.GetObject().MemberEnd()) {
                    auto type = property.get_type();
                    SettingsParser::parseProperty(type, property, componentInstance, (*jsonProperty).value);
                }
            }


//            for(auto& jsonProperty : comp.value.GetObject()) {
//                auto property = componentType.get_property(std::string(jsonProperty.name.GetString()));
//
//                SettingsParser::parseProperty(componentType, property, componentInstance, jsonProperty.value);
//            }

            //printf("Comp: %s\n", comp.name.GetString());
            auto compPtr = componentInstance.get_value<std::shared_ptr<Component>>();
            proto.components.push_back(compPtr);
        }
    } else {
        UK_WARN("Entity", name, "has no components");
    }

    return proto;
}
