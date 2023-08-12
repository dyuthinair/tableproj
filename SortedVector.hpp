/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once
#include "ITable.hpp"
#include "JobEval.hpp"
#include "CScaOp.hpp"

using namespace std;

class SortedVector: ITable {
    vector<Record*>* entries;
    Type sortType; 
    int sortIndex; 
    string colName;
    bool ascending;
    IAccessor& input;
    vector<string> colNames;
    vector<Type> colTypes;

    void AddRecord(Record* r);
    void Sort();
    
    public:
        SortedVector(IAccessor& input, string colName, bool ascending);
        CMemReadAccessor& getAccessor();
        CMemWriteAccessor& getWriteAccessor() { throw std::invalid_argument("unsupported");}
};