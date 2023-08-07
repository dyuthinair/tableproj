/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include "IAccessor.hpp"
#include "TableHashMap.hpp"

#include <unordered_map>

class CHashTableAccessor : public IAccessor {

    unordered_map<string, Record*>::const_iterator nextRecord;
    unordered_map<string, Record*>::const_iterator endRecord;
    
    bool endOfMap;
    const vector<string> &colNames;
    const vector<Type> &colTypes;

    public:
        CHashTableAccessor(const TableHashMap &keyedRecords);
        unsigned int getCols();
        Type getColType(int col);
        string getColName(int col);
        Record* getNextRecord();
        string getName();
};
