/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


LValue::LValue(Type type, string name, Record* value) {
    this->type = type;
    this->name = name;
    this->value = value;
}

Type LValue::getType() {
    return type;
}

string LValue::Name() {
    return name;
}

Record LValue::Value() {
    return *value;
}

void LValue::Update(Record* value) {
    this->value = value;
}

void LValue::Combine(Record* value) {
    throw("How to combine LValue?");
}

Record* LValue::getRecord() {
    return value;
}
