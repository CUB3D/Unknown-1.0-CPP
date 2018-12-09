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

//        /**
//         * Parse a property in a object from a json value
//         * @param type
//         * @param obj
//         * @param data
//         * @param property
//         */
//        static void parseJSONValue(const rttr::type& type, const rapidjson::GenericValue<rapidjson::UTF8<char>>& obj, rttr::variant& data, rttr::property& property) {
//
//                // Handle basic types
//                if (type == rttr::type::get<int>()) {
//                    bool status = property.set_value(data, obj.GetInt());
//                } else if (type == rttr::type::get<bool>()) {
//                    property.set_value(data, obj.GetBool());
//                } else if(type == rttr::type::get<float>()) {
//                    property.set_value(data, obj.GetFloat());
//                } else if(type == rttr::type::get<double>()) {
//                    property.set_value(data, obj.GetDouble());
//                } else if (type == rttr::type::get<std::string>()) {
//                    property.set_value(data, std::string(obj.GetString()));
//                } else if(type == rttr::type::get<::Unknown::Colour>()) {
//                    property.set_value(data, *::Unknown::getColourFromString(std::string(obj.GetString())));
//                } else if(type == rttr::type::get<::Unknown::Image>()) {
//                    property.set_value(data, ::Unknown::Image(std::string(obj.GetString())));
//                } else if(type.is_sequential_container()) {
//                    auto seqView = property.get_value(data).create_sequential_view();
//
//                    printf("Got vec %s : %d\n", type.get_name().to_string().c_str(), static_cast<int>(seqView.get_size()));
//
////                    // Get the type of the elements of the list (first template param)
////                    auto contained = seqView.get_value_type();
////
////                    if(!contained.is_valid()) {
////                        printf("Invalid container elements\n");
////                        return;
////                    }
//
//                    seqView.set_size(obj.GetArray().Size());
//
//                    printf("Got vec2 %s : %d\n", type.get_name().to_string().c_str(), static_cast<int>(seqView.get_size()));
//
//                    int i = 0;
//                    for(auto& item : obj.GetArray()) {
//                        auto val = seqView.get_value(i);
//                        auto t = val.extract_wrapped_value();
//
//                        // Parse the item into the element
//                        for(auto& ii : item.GetObject()) {
//                            parseJSONMember(seqView.get_value_type(), ii, t);
//                        }
//
//                        seqView.set_value(i++, t);
//                    }
//
//                    printf("VVV: %d\n", seqView.is_valid());
//                    printf("Size: %d\n", static_cast<int>(seqView.get_size()));
////                        // If object has string then getString => name
////                        // Name is used as type to allow for polymorphism
////
////                        rttr::variant instance;
////                        auto instanceType = contained;
////
////                        // Item has name
////                        if(item.IsString()) {
////                            std::string name(item.GetString());
////
////                            auto itemType = rttr::type::get_by_name(name);
////
////                            instance = itemType.get_constructor({}).invoke();
////                            instanceType = itemType;
////                        } else {
////                            // No polymorphism, just construct type of element
////                            instance = contained.get_constructor({}).invoke();
////                        }
////
////                        printf("Created a %s\n", instanceType.get_name().to_string().c_str());
////                        printf("I:%d\n", instance.is_valid());
//////
//////                        // Parse the item into the element
//////                        for(auto& i : item.GetObject()) {
//////                            parseJSONMember(instanceType, i, instance);
//////                        }
//////
//////
////                        // Add to list
////                        auto result = seqView.insert(seqView.end(), instance);
////                        printf("Valid: %d\n", (*result).is_valid());
////                    }
//
//
//
//
//                } else if(type.is_class()) {
//
//                    // Retrived the obj from the base
//                    rttr::variant subObj = property.get_value(data);
//
//                    // Loop over all of the entries in this sub json object
//                    for(auto& i : obj.GetObject()) {
//                        //printf("Recursing for type %s\n", type.get_name().to_string().c_str());
//                        parseJSONMember(type, i, subObj);
//                    }
//
//                    bool status = property.set_value(data, subObj);
//                } else if(type.is_enumeration()) {
//                    //printf("Parsing enum\n");
//                    //TODO: register enum, test this
//                    auto enumName = std::string(obj.GetString());
//                    property.set_value(data, type.get_enumeration().name_to_value(enumName));
//                }
//        }
//
//        /**
//         * Parse a element of a json object into a property of the same name in an object
//         * @param objType
//         * @param obj
//         * @param data
//         */
//         //TODO change name of obj as well as type to that of obj.value
//        static void parseJSONMember(const rttr::type &objType,
//                                    const rapidjson::GenericMember<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj,
//                                    rttr::variant &data) {
//
//            // Get the property that relates to this element
//            auto property = objType.get_property(std::string(obj.name.GetString()));
//            auto type = property.get_type();
//
//            if(type.is_valid()) {
//                parseJSONValue(type, obj.value, data, property);
//            } else {
//                printf("Prop type %s not valid\n", obj.name.GetString());
//            }
//        }

        //TODO: remove the one in utils
        static rapidjson::Document loadDocument(const std::string& fileName) {
            auto stream = Filesystem::readFile(fileName);

            rapidjson::Document d;
            rapidjson::IStreamWrapper wrapper(*stream);
            d.ParseStream(wrapper);

            return d;
        }

//        static void parseJSONObject(rttr::variant &data, const rapidjson::GenericValue<rapidjson::UTF8<char>> &doc, rttr::type &type) {
//            for(auto& member : doc.GetObject()) {
//                parseJSONMember(type, member, data);
//            }
//        }


        static void parseProperty(rttr::type& propertyType, const rttr::property& property, rttr::variant& propertyParentObject, const rapidjson::Value& value) {
            printf("Parsing property %s from object %s\n", property.get_name().to_string().c_str(), value.GetString());

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
            } else if(propertyType.is_sequential_container()) {
                auto propertyValue = property.get_value(propertyParentObject);
                auto view = propertyValue.create_sequential_view();
                view.set_size(value.Size());
                printf("Loading Vector of size %d=%d\n", value.Size(), static_cast<int>(view.get_size()));

                int i = 0;

                if(value.IsArray()) {
                    auto vectorElementType = view.get_value_type();

                    for(auto &jsonElement : value.GetArray()) {
                        auto vectorElement = view.get_value(i);

                        parseJSONObject(vectorElement, vectorElementType, jsonElement.GetObject());

                        i++;
                    }
                } else {
                    for(auto &jsonElement : value.GetObject()) {
                        auto vectorElement = view.get_value(i);


                        auto vectorElementType = rttr::type::get_by_name(std::string(jsonElement.name.GetString()));
                        vectorElement = vectorElementType.create();
                        printf("V: %s %d %d\n", vectorElementType.get_name().to_string().c_str(), vectorElementType.is_valid(), vectorElement.is_valid());

//                        if(vectorElement.can_convert(rttr::type::get_by_name("std::shared_ptr<PhysicsBodyComponent>"))) {
//                            vectorElement.convert(rttr::type::get_by_name("std::shared_ptr<PhysicsBodyComponent>"));
//                            printf("Converted\n");
//                        }

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
            } else if(propertyType.is_enumeration()) {
                auto enumName = std::string(value.GetString());
                property.set_value(propertyParentObject, propertyType.get_enumeration().name_to_value(enumName));
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
