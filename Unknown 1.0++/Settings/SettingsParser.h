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

        static rapidjson::Document loadDocument(const std::string& fileName) {
            auto stream = Filesystem::readFile(fileName);

            rapidjson::Document d;
            rapidjson::IStreamWrapper wrapper(*stream);
            d.ParseStream(wrapper);

            return d;
        }


        static void parseProperty(rttr::type& propertyType, const rttr::property& property, rttr::variant& propertyParentObject, const rapidjson::Value& value) {
            //printf("Parsing property %s from %s\n", property.get_name().to_string().c_str(), value.GetString());

            if (propertyType == rttr::type::get<int>()) {
                bool status = property.set_value(propertyParentObject, value.GetInt());
            } else if (propertyType == rttr::type::get<bool>()) {
                property.set_value(propertyParentObject, value.GetBool());
            } else if(propertyType == rttr::type::get<float>()) {
                property.set_value(propertyParentObject, value.GetFloat());
            } else if(propertyType == rttr::type::get<double>()) {
                property.set_value(propertyParentObject, value.GetDouble());
            } else if (propertyType == rttr::type::get<std::string>()) {
                property.set_value(propertyParentObject, std::string(value.GetString()));
            } else if(propertyType == rttr::type::get<::Unknown::Colour>()) {
                property.set_value(propertyParentObject, *::Unknown::getColourFromString(std::string(value.GetString())));
            } else if(propertyType == rttr::type::get<::Unknown::Image>()) {
                property.set_value(propertyParentObject, ::Unknown::Image(std::string(value.GetString())));
            } else if(propertyType.is_enumeration()) {
                auto enumName = std::string(value.GetString());
                property.set_value(propertyParentObject, propertyType.get_enumeration().name_to_value(enumName));
            } else if(propertyType.is_sequential_container()) {
                auto propertyValue = property.get_value(propertyParentObject);
                auto view = propertyValue.create_sequential_view();
                view.set_size(value.Size());

                int i = 0;
                if(value.IsArray()) {
                    auto vectorElementType = view.get_value_type();

                    for(auto &jsonElement : value.GetArray()) {
                        auto vectorElement = view.get_value(i);

                        parseJSONObject(vectorElement, vectorElementType, jsonElement.GetObject());

                        i++;
                    }
                } else {
                    //// CURRENTLY ONLY WORKS FOR NON PTR TYPES
                    return;
                    for(auto &jsonElement : value.GetObject()) {
                        //auto vectorElement = view.get_value(i);


                        auto vectorElementType = rttr::type::get_by_name(std::string(jsonElement.name.GetString()));
                        auto vectorElement = vectorElementType.create();
                        printf("V: %s %d %d\n", vectorElementType.get_name().to_string().c_str(), vectorElementType.is_valid(), vectorElement.is_valid());

                        auto testType = rttr::type::get_by_name("std::shared_ptr<PhysicsBodyComponent>");
                        auto test = testType.create({vectorElement});
                        printf("VVVVVV: %d\n", test.is_valid());


                        auto meth = rttr::type::get_global_method("std::make_shared<PhysicsBodyComponent>");
                        auto m = meth.invoke(rttr::variant(nullptr));

                        printf("%d, %d\n", meth.is_valid(), m.is_valid());

                        parseJSONObject(vectorElement, vectorElementType, jsonElement.value.GetObject());

                        view.set_value(i, vectorElement);

                        i++;
                    }
                }

                property.set_value(propertyParentObject, propertyValue);

            } else if(propertyType.is_class()) {
                    // Retrieve the obj from the base
                    rttr::variant subObj = property.get_value(propertyParentObject);
                    auto subObjectType = subObj.get_type();

                    parseJSONObject(subObj, subObjectType, value.GetObject());

                    property.set_value(propertyParentObject, subObj);
            }
        }

        static void parseJSONObject(rttr::variant& destinationObject, rttr::type& destinationType, const rapidjson::Value::ConstObject& object) {
            // For all of the properties in this type
            for(auto& subField : destinationType.get_properties()) {
                auto propertyType = subField.get_type();
                auto propertyJSONField = object.FindMember(subField.get_name().to_string().c_str());

                if(propertyJSONField != object.MemberEnd()) {
                    parseProperty(propertyType, subField, destinationObject, propertyJSONField->value);
                } else {
                   // printf("Unable to find %s::%s\n", destinationType.get_name().to_string().c_str(), subField.get_name().to_string().c_str());
                }
            }
        }

        static void parseJSONDocument(rttr::variant& destinationObject, rttr::type& destinationType, const rapidjson::Document& doc) {
            rapidjson::Value::ConstObject rootObject = doc.GetObject();

            parseJSONObject(destinationObject, destinationType, rootObject);
        }

        template<typename T>
        static T parseSettings(const std::string &file) {
            rapidjson::Document d = loadDocument(file);

            T data;
            rttr::variant variantData(&data);
            auto type = rttr::type::get<T>();

            parseJSONDocument(variantData, type, d);

            //parseJSONObject(variantData, d.GetObject(), type);

            return variantData.get_wrapped_value<T>();
        }
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H
