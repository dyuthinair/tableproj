/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CHashTableAccessor.hpp"

using namespace std;

CHashTableAccessor::CHashTableAccessor(const TableHashMap &keyedRecords)
    : colNames(keyedRecords.getColNames()), colTypes(keyedRecords.getColTypes()) {

    nextRecord = keyedRecords.begin();
    endRecord = keyedRecords.end();

    endOfMap = false;
}

unsigned int CHashTableAccessor::getCols() {
    return colNames.size();    
}

Type CHashTableAccessor::getColType(int col) {
    return colTypes.at(col);
}

std::string CHashTableAccessor::getColName(int col) {
    return colNames.at(col);
}

Record* CHashTableAccessor::getNextRecord() {

    if(nextRecord == endRecord) {
        endOfMap = true;
    }

    if(endOfMap) {
        return nullptr;
    } 
    
    unordered_map<string, Record*>::const_iterator prevRecord = nextRecord++;
    Record* recValue = prevRecord->second;  
    Type swtichType = colTypes.at(colTypes.size() - 1);
    switch (swtichType)
    {
        case String:   
            recValue->strings.at(recValue->strings.size()-1) = recValue->strings.at(0);
            recValue->strings.erase(recValue->strings.begin());
            break;
        case Int:   
            recValue->nums.at(recValue->nums.size()-1) = recValue->nums.at(0);
            recValue->nums.erase(recValue->nums.begin());
            break;
        case Float: 
            recValue->floats.at(recValue->floats.size()-1) = recValue->floats.at(0);
            recValue->floats.erase(recValue->floats.begin());
            break;
        case Boolean: 
            recValue->booleans.at(recValue->booleans.size()-1) = recValue->booleans.at(0);
            recValue->booleans.erase(recValue->booleans.begin());
            break;
        case Datetime: 
            recValue->datetimes.at(recValue->datetimes.size()-1) = recValue->datetimes.at(0);
            recValue->datetimes.erase(recValue->datetimes.begin());
            break;
        case EnumCount: 
            throw std::invalid_argument("Not a real type");
            break;
    }
    return recValue;
}

string CHashTableAccessor::getName() {
    throw std::invalid_argument("Should never be called");
}

