//
// Created by cub3d on 16/07/2018.
//

#include <iostream>
#include <sstream>
#include "SharedVariable.h"

Unknown::SharedVariable::SharedVariable(const std::string &name) :name(name) {
	::Unknown::getUnknown()->variablelookup[name] = this;
}

const std::type_info& Unknown::SharedVariable::type() const {
    return this->data.type();
}

bool Unknown::SharedVariable::initalised() {
    return type() != typeid(void);
}

double Unknown::SharedVariable::operator++() {
    if(!initalised()) {
        *this = 0;
    }

    this->data = getValue<double>() + 1;
    return getValue<double>();
}

double Unknown::SharedVariable::operator++(int dummy) {
    if(!initalised()) {
        *this = 0;
    }

    double old = getValue<double>();
    this->data = old + 1;
    return old;
}

Unknown::SharedVariable::operator double() {
    return getValue<double>();
}

Unknown::SharedVariable::operator std::string() {
    return getValue<std::string>();
}

Unknown::SharedVariable::operator bool() {
    return getValue<bool>();
}

std::string Unknown::SharedVariable::toString() {
    if(type() == typeid(std::string)) {
        return getValue<std::string>();
    }
    if(type() == typeid(double)) {
        std::stringstream ss;
        ss << getValue<double>();
        return ss.str();
    }

    return "N/A";
}
