/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


CVarRuntime::CVarRuntime(Type type, string name, Record* value) {
    this->type = type;
    this->name = name;
    this->value = value;
}

Type CVarRuntime::getType() {
    return type;
}

string CVarRuntime::Name() {
    return name;
}

Record CVarRuntime::Value() {
    return *value;
}

void CVarRuntime::update(Record* value) {
    this->value = value;
}


