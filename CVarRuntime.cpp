/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


CVarRuntime::CVarRuntime(Type type, string name, Record* value) {
    this->type = type;
    this->name = name;
    this->result.ScaValue = value;
}

CVarRuntime::CVarRuntime(Type type, string name, Record* value, string tableName) {
    this->type = type;
    this->name = tableName + ":" + name;
    this->result.ScaValue = value;
}

Type CVarRuntime::getType() {
    return type;
}

string CVarRuntime::Name() {
    return name;
}

Record CVarRuntime::Value() {
    return *result.ScaValue;
}

void CVarRuntime::Update(const Record& value) {
    this->result.ScaValue->copy(value);
}

void CVarRuntime::Combine(Record* value) {
    throw std::invalid_argument("How to combine CVarRunTIme?");
}
