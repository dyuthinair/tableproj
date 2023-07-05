/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemTable.hpp"

using namespace std;

CMemTable::CMemTable() {
    colNames = new vector<string>();
    colTypes = new vector<Type>();
    records = new vector<Record*>();
}

CMemReadAccessor& CMemTable::getAccessor() {
    CMemReadAccessor *reader = new CMemReadAccessor(colNames, colTypes, records);
    return *reader;
}

CMemWriteAccessor& CMemTable::getWriteAccessor() {
    CMemWriteAccessor *writer = new CMemWriteAccessor(colNames, colTypes, records);
    return *writer;
}