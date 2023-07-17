/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemTable.hpp"
#include <memory>

using namespace std;

CMemTable::CMemTable() {
    colNames = new vector<string>();
    colTypes = new vector<Type>();
    records = new vector<Record*>();
}

CMemTable::CMemTable(string tableName) {
    this->tableName = tableName;
    colNames = new vector<string>();
    colTypes = new vector<Type>();
    records = new vector<Record*>();
}

CMemReadAccessor& CMemTable::getAccessor() {
    unique_ptr<CMemReadAccessor> reader(new CMemReadAccessor(tableName, colNames, colTypes, records));
    return *reader;
}

CMemWriteAccessor& CMemTable::getWriteAccessor() {
    CMemWriteAccessor *writer = new CMemWriteAccessor(colNames, colTypes, records);
    return *writer;
}