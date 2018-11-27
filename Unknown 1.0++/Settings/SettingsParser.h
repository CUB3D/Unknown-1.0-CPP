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
#include "../Types/Colour.h"
#include "../Utils.h"

#ifdef WIN32
// I absolutely dispise the individual who decided to put the inverse of this define in windows.h
// What is this, some kind of sick joke
#define GetObjectA GetObject
#endif

namespace Unknown {
    class SettingsParser {
    public:
        static void parseJSONObject(const rttr::type& objType, rapidjson::GenericMember<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& obj, rttr::variant& data) {
            printf("Parsing value %s from type %s\n", obj.name.GetString(),
                    objType.get_name().to_string().c_str());

            // Get the property that relates to this element
            auto property = objType.get_property(std::string(obj.name.GetString()));
            auto type = property.get_type();

            if(type.is_valid()) {
                if (type == rttr::type::get<int>()) {
                    bool status = property.set_value(data, obj.value.GetInt());
                    printf("New value: %d\n", obj.value.GetInt());
                } else if (type == rttr::type::get<bool>()) {
                    property.set_value(data, obj.value.GetBool());
                } else if (type == rttr::type::get<std::string>()) {
                    property.set_value(data, std::string(obj.value.GetString()));
                } else if(type == rttr::type::get<::Unknown::Colour>()) {
                    property.set_value(data, *::Unknown::getColourFromString(std::string(obj.value.GetString())));
                } else if(type.is_class()) {

                    // Retrived the obj from the base
                    rttr::variant subObj = property.get_value(data);

                    // Loop over all of the entries in this sub json object
                    for(auto& i : obj.value.GetObject()) {
                        //printf("Recursing for type %s\n", type.get_name().to_string().c_str());
                        parseJSONObject(type, i, subObj);
                    }

                   bool status = property.set_value(data, subObj);
                }
            } else {
                printf("Prop type  not valid\n");
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

        static void parseDocument(rttr::variant& data, rapidjson::Document& doc, rttr::type& type) {
            for(auto& i : doc.GetObject()) {
                parseJSONObject(type, i, data);
            }
        }

        template<typename T>
        static T parseSettings(const std::string &file) {
            rapidjson::Document d = loadDocument(file);

            T data;
            rttr::variant variantData(&data);
            auto type = rttr::type::get<T>();

            parseDocument(variantData, d, type);

            return variantData.get_wrapped_value<T>();
        }
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H
