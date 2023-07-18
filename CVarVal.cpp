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
    index = -1;
}

CVarRef::CVarRef(Type type, string name, string tableName) {
    this->type = type;
    this->name = tableName + ":" + name;
    index = -1;
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
    if(index == -1) {
        index++;
        for(IVariable* curVar : params) {
            if(curVar->Name().compare(this->name) == 0 && curVar->getType() == this->type) {
                Record *var = new Record();
                var->copy(curVar->Value());
                value = var;
                return;
                //ITracer::GetTracer()->Trace("CVarRef::Op value of %s is %d.\n", curVar->Name().c_str(), value->nums.at(0));
            }
            index++;
        }
        throw("Did not find runtime value");
    } else {
        IVariable* curVar = params.at(index);
        Record *var = new Record();
        var->copy(curVar->Value());
        value = var;
    }
}

void CVarRef::Update(Record* value)
{
    throw("Unsupported");
}

void CVarRef::Combine(Record* value)
{
    throw("Unsupported");
}