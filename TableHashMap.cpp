/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
 

#include "TableHashMap.hpp"

using namespace std;

TableHashMap::TableHashMap(vector<string> *colNames, vector<Type> *colTypes) {
    this->colNames = colNames;
    this->colTypes = colTypes;
}

void TableHashMap::insert(string tableKey, Record* tableValue) {
    hashedRecords.insert({tableKey, tableValue});
}

bool TableHashMap::contains(string tableKey) {
    if(hashedRecords.count(tableKey) == 0) {
        return false;
    } else {
        return true;
    }
}

Record* TableHashMap::value(string tableKey) {
    return hashedRecords.at(tableKey);
}

unordered_map<string, Record*>::const_iterator TableHashMap::begin() const {
    return hashedRecords.begin();
}

unordered_map<string, Record*>::const_iterator TableHashMap::end() const {
    return hashedRecords.end();
}

const vector<string>& TableHashMap::getColNames() const {
    return *colNames;
}

const vector<Type>& TableHashMap::getColTypes() const {
    return *colTypes;
}
