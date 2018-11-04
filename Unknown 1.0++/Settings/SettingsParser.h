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
//#include <rttr/property.h>

namespace Unknown {
    class SettingsParser {
    public:
        template<typename T>
        static T parseSettings(const std::string &file) {
            auto stream = Filesystem::readFile(file);

            rapidjson::Document d;
            rapidjson::IStreamWrapper wrapper(*stream);
            d.ParseStream(wrapper);

            T data;
            auto type = rttr::type::get<T>();

            for(auto& i : d.GetObject()) {
                // Find the property that relates to this element, if it exists
                auto property = type.get_property(std::string(i.name.GetString()));
                if(property.is_valid()) {
                    auto propertyType = property.get_type();

                    if(propertyType == rttr::type::get<int>())
                        property.set_value(data, i.value.Get<int>());
                    if(propertyType == rttr::type::get<bool>())
                        property.set_value(data, i.value.Get<bool>());
                    if(propertyType == rttr::type::get<std::string>())
                        property.set_value(data, std::string(i.value.GetString()));
                }
            }

            return data;
        }
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SETTINGSPARSER_H
