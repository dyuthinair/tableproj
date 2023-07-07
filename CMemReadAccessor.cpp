/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemReadAccessor.hpp"

using namespace std;

CMemReadAccessor::CMemReadAccessor(std::vector<string> *colNames, 
    std::vector<Type> *colTypes, 
    std::vector<Record*> *records) {
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->records = records;

    row = 0;
}

int CMemReadAccessor::getCols() {
    return colNames->size();
}

Type CMemReadAccessor::getColType(int col) {
    return colTypes->at(col);
}

std::string CMemReadAccessor::getColName(int col) {
    return colNames->at(col);
}

Record* CMemReadAccessor::getNextRecord() {
    row++;
    if(row > records->size()) {
        row = 0;
        return nullptr;
    } else {
        return records->at(row-1);
    }
}