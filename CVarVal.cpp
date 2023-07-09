/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"
#include <iostream>

using namespace std;

CVarRef::CVarRef(Type type, string name) {
    this->type = type;
    this->name = name;
}

Type CVarRef::getType() {
    return type;
}

string CVarRef::Name() {
    return name;
}

Record CVarRef::Value() {
    return *value;
}

void CVarRef::Op(vector<IVariable*>& params) {
    for(IVariable* curVar : params) {
        if(curVar->Name().compare(this->name) == 0 && curVar->getType() == this->type) {
            Record *var = new Record();
            var->copy(curVar->Value());
            value = var;

            ITracer::GetTracer()->Trace("CVarRef::Op value of %s is %d.\n", curVar->Name().c_str(), value->nums.at(0));
        }
    }
}