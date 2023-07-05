/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IAccessor.hpp"
#pragma once

class CMemReadAccessor : public IAccessor {

    vector<string> *colNames;
    vector<Type> *colTypes;
    vector<Record*> *records;

    unsigned int row;

    public:
        CMemReadAccessor(std::vector<string> *colNames, 
            std::vector<Type> *colTypes, 
            std::vector<Record*> *records);
        int getCols();
        Type getColType(int col);
        string getColName(int col);
        Record* getNextRecord();
};
