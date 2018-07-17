//
// Created by cub3d on 16/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H

#include <map>
#include <any>

namespace Unknown
{
    class SharedVariable
    {
        std::string name;

    public:
        std::any data;

        SharedVariable(const std::string& name);
        SharedVariable(const std::string& name, double starting);
        SharedVariable(const std::string& name, const std::string& starting);

        SharedVariable& operator=(const std::string s);
        SharedVariable& operator=(const double num);

        const std::type_info& type() const;
        bool initalised();
        double getDouble() const;
        std::string getString() const;


        double operator ++();
        double operator ++(int dummy); // postfix
    };

    extern std::map<std::string, SharedVariable *> variablelookup;
}



#endif //UNKNOWN_DEVELOPMENT_TOOL_SHAREDVARIABLE_H
