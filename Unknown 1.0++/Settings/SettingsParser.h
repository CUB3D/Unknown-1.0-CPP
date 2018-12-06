//
// Created by cub3d on 03/11/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H
#define UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H

#include <string>
#include <istreamwrapper.h>
#include "../Filesystem/Filesystem.h"
#include "document.h"
#include <rttr/type.h>
#include <rttr/enumeration.h>
#include "../Types/Colour.h"
#include "../Utils.h"
#include <Image.h>

#ifdef WIN32
// I absolutely dispise the individual who decided to put the inverse of this define in windows.h
// What is this, some kind of sick joke
#define GetObjectA GetObject
#endif

namespace Unknown {
    class SettingsParser {
    public:
        /**
         * Parse a property in a object from a json value
         * @param type
         * @param obj
         * @param data
         * @param property
         */
        static void parseJSONValue(const rttr::type& type, const rapidjson::GenericValue<rapidjson::UTF8<char>>& obj, rttr::variant& data, rttr::property& property) {

                // Handle basic types
                if (type == rttr::type::get<int>()) {
                    bool status = property.set_value(data, obj.GetInt());
                } else if (type == rttr::type::get<bool>()) {
                    property.set_value(data, obj.GetBool());
                } else if(type == rttr::type::get<float>()) {
                    property.set_value(data, obj.GetFloat());
                } else if(type == rttr::type::get<double>()) {
                    property.set_value(data, obj.GetDouble());
                } else if (type == rttr::type::get<std::string>()) {
                    property.set_value(data, std::string(obj.GetString()));
                } else if(type == rttr::type::get<::Unknown::Colour>()) {
                    property.set_value(data, *::Unknown::getColourFromString(std::string(obj.GetString())));
                } else if(type == rttr::type::get<::Unknown::Image>()) {
                    property.set_value(data, ::Unknown::Image(std::string(obj.GetString())));
                } else if(type.is_sequential_container()) {
                    printf("Got vec %s\n", type.get_name().to_string().c_str());

                    // Get the type of the elements of the list (first template param)
                    auto& contained = *(type.get_template_arguments().begin());

                    if(!contained.is_valid()) {
                        printf("Invalid container elements\n");
                        return;
                    }

                    for(auto& item : obj.GetArray()) {

                        // If object has string then getString => name
                        // Name is used as type to allow for polymorphism

                        rttr::variant instance;
                        auto instanceType = contained;

                        // Item has name
                        if(item.IsString()) {
                            std::string name(item.GetString());

                            auto itemType = rttr::type::get_by_name(name);

                            instance = itemType.get_constructor({}).invoke();
                            instanceType = itemType;
                        } else {
                            // No polymorphism, just construct type of element
                            instance = contained.get_constructor({}).invoke();
                        }

                        // Parse the item into the element
                        for(auto& i : item.GetObject()) {
                            parseJSONMember(instanceType, i, instance);
                        }
                        // Add to list
                        type.get_method("push_back", {contained}).invoke(property, instance);

                        //TODO: figure out why this method is invalid
                        printf("%d - valid\n", type.get_method("push_back", {contained}).is_valid());

                        printf("Added\n");
                    }

                } else if(type.is_class()) {

                    // Retrived the obj from the base
                    rttr::variant subObj = property.get_value(data);

                    // Loop over all of the entries in this sub json object
                    for(auto& i : obj.GetObject()) {
                        //printf("Recursing for type %s\n", type.get_name().to_string().c_str());
                        parseJSONMember(type, i, subObj);
                    }

                    bool status = property.set_value(data, subObj);
                } else if(type.is_enumeration()) {
                    //printf("Parsing enum\n");
                    //TODO: register enum, test this
                    auto enumName = std::string(obj.GetString());
                    property.set_value(data, type.get_enumeration().name_to_value(enumName));
                }
        }

        /**
         * Parse a element of a json object into a property of the same name in an object
         * @param objType
         * @param obj
         * @param data
         */
         //TODO change name of obj as well as type to that of obj.value
        static void parseJSONMember(const rttr::type &objType,
                                    const rapidjson::GenericMember<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj,
                                    rttr::variant &data) {

            // Get the property that relates to this element
            auto property = objType.get_property(std::string(obj.name.GetString()));
            auto type = property.get_type();

            if(type.is_valid()) {
                parseJSONValue(type, obj.value, data, property);
            } else {
                printf("Prop type %s not valid\n", obj.name.GetString());
            }
        }

        //TODO: remove the one in utils
        static rapidjson::Document loadDocument(const std::string& fileName) {
            auto stream = Filesystem::readFile(fileName);

            rapidjson::Document d;
            rapidjson::IStreamWrapper wrapper(*stream);
            d.ParseStream(wrapper);

            return d;
        }

        static void parseJSONObject(rttr::variant &data, const rapidjson::GenericValue<rapidjson::UTF8<char>> &doc, rttr::type &type) {
            for(auto& member : doc.GetObject()) {
                parseJSONMember(type, member, data);
            }
        }

        template<typename T>
        static T parseSettings(const std::string &file) {
            rapidjson::Document d = loadDocument(file);

            T data;
            rttr::variant variantData(&data);
            auto type = rttr::type::get<T>();

            parseJSONObject(variantData, d.GetObject(), type);

            return variantData.get_wrapped_value<T>();
        }
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H
