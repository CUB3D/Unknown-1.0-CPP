//
// Created by cub3d on 16/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H

#include <string>
#include <map>
#include <any>
#include <functional>
#include <vector>

// If clang
#include <experimental/any>

namespace Unknown
{
    class SharedVariable
    {
        std::string name;

    public:
        // If clang
        std::experimental::any data;
        //std::any data;

        std::vector<std::function<void(SharedVariable v)>> changeListeners;

        SharedVariable(const std::string& name);

        template<typename T>
        SharedVariable(const std::string& name, T starting) : SharedVariable(name) {
            *this = starting;
        }


        template<typename T>
        SharedVariable& operator=(const T t) {
            for(auto& listeners : changeListeners) {
                listeners(*this);
            }

            this->data = t;
            return *this;
        }

        const std::type_info& type() const;
        bool initalised();

        template<typename U>
        U getValue() const {
            //return std::any_cast<U>(this->data);
            // if clang
            return std::experimental::any_cast<U>(this->data);
        }

        operator bool();
        operator double();
        operator std::string();


        std::string toString();


        double operator ++();
        double operator ++(int dummy); // postfix
    };
}



#endif //UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H
