//
// Created by cub3d on 16/07/2018.
//

#include <iostream>
#include "SharedVariable.h"

std::map<std::string, Unknown::SharedVariable*> Unknown::variablelookup;

Unknown::SharedVariable::SharedVariable(const std::string &name) :name(name) {
    variablelookup[name] = this;
}

Unknown::SharedVariable::SharedVariable(const std::string &name, const double start) : name(name) {
    *this = start;
    variablelookup[name] = this;
}

Unknown::SharedVariable::SharedVariable(const std::string &name, const std::string &starting) {
    *this = starting;
    variablelookup[name] = this;
}

Unknown::SharedVariable &Unknown::SharedVariable::operator=(const std::string s) {
    this->data = s;
    return *this;
}

Unknown::SharedVariable &Unknown::SharedVariable::operator=(const double num) {
    this->data = num;
    return *this;
}

std::string Unknown::SharedVariable::getString() const {
    return std::any_cast<std::string>(this->data);
}

const std::type_info& Unknown::SharedVariable::type() const {
    return this->data.type();
}

double Unknown::SharedVariable::getDouble() const {
    return std::any_cast<double>(this->data);
}

bool Unknown::SharedVariable::initalised() {
    return type() != typeid(void);
}

double Unknown::SharedVariable::operator++() {
    if(!initalised()) {
        *this = 0;
    }

    this->data = getDouble() + 1;
    return getDouble();
}

double Unknown::SharedVariable::operator++(int dummy) {
    if(!initalised()) {
        *this = 0;
    }

    double old = getDouble();
    this->data = old + 1;
    return old;
}
