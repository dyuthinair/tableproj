/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
 
 #pragma once

#include "IAccessor.hpp"
#include <unordered_map>

 using namespace std;

 class TableHashMap {

    unordered_map<string, Record*> hashedRecords;

    vector<string> colNames;
    vector<Type> colTypes;

    public:
        TableHashMap(vector<string> *colNames, vector<Type> *colTypes);
        void insert(string tableKey, Record* tableValue);
        bool contains(string tableKey);
        Record* value(string tableKey);

        unordered_map<string, Record*>::const_iterator begin() const;
        unordered_map<string, Record*>::const_iterator end() const;

        const vector<string>& getColNames() const;
        const vector<Type>& getColTypes() const;
 };