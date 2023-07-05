/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemWriteAccessor.hpp"
#include <iostream>

using namespace std;

CMemWriteAccessor::CMemWriteAccessor(std::vector<string> *colNames, 
    std::vector<Type> *colTypes, 
    std::vector<Record*> *records) {
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->records = records;
}

void CMemWriteAccessor::setColNames(std::vector<string> colNames) {
    for(string name:colNames) {
        this->colNames->push_back(name);
    }
}

void CMemWriteAccessor::setColTypes(std::vector<Type> colTypes) {
    for(Type type:colTypes) {
        this->colTypes->push_back(type);
    }
}

void CMemWriteAccessor::pushRow(Record *record) {
    records->push_back(record);
}