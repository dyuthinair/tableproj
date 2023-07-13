/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "ITable.hpp"
#pragma once

using namespace std;

class CMemTable : public ITable {

    string tableName;
    vector<string> *colNames;
    vector<Type> *colTypes;
    vector<Record*> *records;

    public:
        CMemTable();
        CMemTable(string tableName);
        CMemReadAccessor& getAccessor();
        CMemWriteAccessor& getWriteAccessor();
};