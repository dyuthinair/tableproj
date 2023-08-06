/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


LValue::LValue(Type type, string name, Record* value) {
    this->type = type;
    this->name = name;
    this->result.ScaValue = value;
}

Type LValue::getType() {
    return type;
}

string LValue::Name() {
    return name;
}

Record LValue::Value() {
    return *result.ScaValue;
}

void LValue::Update(const Record& value) {
    result.ScaValue->copy(value);
}

void LValue::Combine(Record* value) {
    throw("How to combine LValue?");
}

