/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "ITable.hpp"
#pragma once

using namespace std;

class CMemTable : public ITable {

    vector<string> *colNames;
    vector<Type> *colTypes;
    vector<Record*> *records;

    public:
        CMemTable();
        CMemReadAccessor& getAccessor();
        CMemWriteAccessor& getWriteAccessor();
};