/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"
#include "IRelOp.hpp"
#include "CVarRuntimeUsingRecord.hpp"


CVarRuntimeUsingRecord::CVarRuntimeUsingRecord(Type type, string name, int column)
    : CVarRuntime(type, name, nullptr)
{
    this->col = column;
}

CVarRuntimeUsingRecord::CVarRuntimeUsingRecord(Type type, string name, int column, string tableName)
    : CVarRuntime(type, name, nullptr, tableName)
{
    this->col = column;
}

void CVarRuntimeUsingRecord::Update(Record* value) {
    this->prow = value;

    Type type = getType();
    returnValue.booleans.clear();
    returnValue.nums.clear();
    returnValue.floats.clear();
    returnValue.strings.clear();
    
    switch(type)
    {
        case String:
            returnValue.strings.push_back(this->prow->strings.at(this->col));
            break;
        case Int:
            returnValue.nums.push_back(this->prow->nums.at(this->col));
            break;
        case Float:
            returnValue.floats.push_back(this->prow->floats.at(this->col));
            break;
        case Boolean: 
            returnValue.booleans.push_back(this->prow->booleans.at(this->col));
            break;
        case EnumCount:
            throw("Invalid type");  
            break;
    }
}

void CVarRuntimeUsingRecord::Combine(Record* value) {
   throw("What?");
}

Record CVarRuntimeUsingRecord::Value() {
    return returnValue;
}


