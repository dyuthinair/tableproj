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

void CVarRuntimeUsingRecord::Update(const Record& value) {

    Type type = getType();
    returnValue.booleans.clear();
    returnValue.nums.clear();
    returnValue.floats.clear();
    returnValue.strings.clear();
    returnValue.datetimes.clear();
    
    switch(type)
    {
        case String:
            returnValue.strings.push_back(value.strings.at(this->col));
            break;
        case Int:
            returnValue.nums.push_back(value.nums.at(this->col));
            break;
        case Float:
            returnValue.floats.push_back(value.floats.at(this->col));
            break;
        case Boolean: 
            returnValue.booleans.push_back(value.booleans.at(this->col));
            break;
        case Datetime: 
            returnValue.datetimes.push_back(value.datetimes.at(this->col));
            break;
        case EnumCount:
            throw std::invalid_argument("Invalid type");  
            break;
    }
}

void CVarRuntimeUsingRecord::Combine(Record* value) {
   throw std::invalid_argument("What?");
}

Record CVarRuntimeUsingRecord::Value() {
    return returnValue;
}


