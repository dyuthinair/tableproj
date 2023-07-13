/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IAccessor.hpp"
#pragma once

class CMemReadAccessor : public IAccessor {

    string tableName;
    vector<string> *colNames;
    vector<Type> *colTypes;
    vector<Record*> *records;

    unsigned int row;

    public:
        CMemReadAccessor(string tableName, std::vector<string> *colNames, 
            std::vector<Type> *colTypes, 
            std::vector<Record*> *records);
        unsigned int getCols();
        Type getColType(int col);
        string getColName(int col);
        Record* getNextRecord();
        string getName();
};
