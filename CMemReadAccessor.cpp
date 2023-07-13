/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemReadAccessor.hpp"

using namespace std;

CMemReadAccessor::CMemReadAccessor(string tableName, 
    std::vector<string> *colNames, 
    std::vector<Type> *colTypes, 
    std::vector<Record*> *records) {

    this->tableName = tableName;
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->records = records;

    row = 0;
}

unsigned int CMemReadAccessor::getCols() {
    return colNames->size();
}

Type CMemReadAccessor::getColType(int col) {
    return colTypes->at(col);
}

std::string CMemReadAccessor::getColName(int col) {
    return colNames->at(col);
}

Record* CMemReadAccessor::getNextRecord() {
    if (row < records->size()) {
        row++;
        return records->at(row-1);
    } else {
        row = 0;
        return nullptr;
    }
}

string CMemReadAccessor::getName() {
    return tableName;
}

