/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"
#include "CHashTableAccessor.hpp"


MultiLValue::MultiLValue(Type type, string name, vector<CVarRef*> groupByCols) {
    this->type = type;
    this->name = name;
    this->groupByCols = groupByCols;

    vector<string> colNames;
    vector<Type> colTypes;

    for(CVarRef* curRef : groupByCols) {
        colNames.push_back(curRef->Name());
        colTypes.push_back(curRef->getType());
    }
    colNames.push_back(name);
    colTypes.push_back(type);
    hashedRecords = new TableHashMap(&colNames, &colTypes);
}

Type MultiLValue::getType() {
    return type;
}

string MultiLValue::Name() {
    return name;
}

Record MultiLValue::Value() {
    Record* foundVal = find();
    foundVal->SetValue = new CHashTableAccessor(*hashedRecords);
    return *foundVal;
}

void MultiLValue::Update(const Record& value) {
    Record* toBeUpdated = find();
    switch(type) {
        case String:   
            toBeUpdated->strings.at(0) = value.strings.at(0);
            break;
        case Int:   
            toBeUpdated->nums.at(0) = value.nums.at(0);
            break;
        case Float: 
            toBeUpdated->floats.at(0) = value.floats.at(0);
            break;
        case Boolean: 
            toBeUpdated->booleans.at(0) = value.booleans.at(0);
            break;
        case Datetime: 
            toBeUpdated->datetimes.at(0) = value.datetimes.at(0);
            break;
        case EnumCount: 
            throw std::invalid_argument("Not a real type");
            break;
    }    
}

void MultiLValue::Combine(Record* value) {
    throw std::invalid_argument("How to combine LValue?");
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* MultiLValue::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    for(CVarRef *col: groupByCols) {
        children->push_back(col);
    }
    return children;
}

Record* MultiLValue::find() {
    string colKey = "";
    for(CVarRef *col: groupByCols) {
        Type colType = col->getType();
        switch(colType) {
            case String:
                colKey += col->Value().strings.at(0);
                break;
            case Int:
                colKey += to_string(col->Value().nums.at(0));
                break;
            case Float:
                throw std::invalid_argument("Cannot group by on floats");
            case Boolean: 
                colKey += to_string(col->Value().booleans.at(0));
                break;
            case Datetime:
                throw std::invalid_argument("Cannot group by on datetimes");
            case EnumCount:
                throw std::invalid_argument("Invalid type");  
                break;
        }
    }
    if(!hashedRecords->contains(colKey)) {
        Record *recWithCols = new Record();
        recWithCols->nums.push_back(0);
        for(CVarRef *col: groupByCols) {
            Type colType = col->getType();
            switch(colType) {
                case String:
                    recWithCols->strings.push_back(col->Value().strings.at(0));
                    break;
                case Int:
                    recWithCols->nums.push_back(col->Value().nums.at(0));
                    break;
                case Float:
                    throw std::invalid_argument("Cannot group by on floats");
                case Boolean: 
                    recWithCols->booleans.push_back(col->Value().booleans.at(0));
                    break;
                case Datetime:
                    throw std::invalid_argument("Cannot group by on datetimes");
                case EnumCount:
                    throw std::invalid_argument("Invalid type");  
                    break;
            }
        }
        recWithCols->nums.push_back(0);
        hashedRecords->insert(colKey, recWithCols);
    } 
    return hashedRecords->value(colKey);
}