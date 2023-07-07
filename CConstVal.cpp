/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


CConstVal::CConstVal(Type type, Record val) {
    this->type = type;
    this->value = val;
}

Type CConstVal::getType() {
    return type;
}

Record CConstVal::Value() {
    return value;
}