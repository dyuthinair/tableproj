/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"


MultiLValue::MultiLValue(Type type, string name, vector<CVarRef*> groupByCols) {
    this->type = type;
    this->name = name;
    this->groupByCols = groupByCols;
}

Type MultiLValue::getType() {
    return type;
}

string MultiLValue::Name() {
    return name;
}

Record MultiLValue::Value() {
    return *(find());
}

void MultiLValue::Update(Record* value) {
    find()->copy(*value);
}

void MultiLValue::Combine(Record* value) {
    throw("How to combine LValue?");
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
                throw("Cannot group by on floats");
            case Boolean: 
                colKey += to_string(col->Value().booleans.at(0));
                break;
            case EnumCount:
                throw("Invalid type");  
                break;
        }
    }
    if(hashedRecords.count(colKey) == 0) {
        hashedRecords.insert({colKey, new IntValue(0)});
    } 
    return hashedRecords.at(colKey);
}