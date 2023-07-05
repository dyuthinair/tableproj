/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IWriteAccessor.hpp"

using namespace std;

#pragma once

class CMemWriteAccessor : public IWriteAccessor {
    
    vector<string> *colNames;
    vector<Type> *colTypes;
    vector<Record*> *records;
    
    public:
        CMemWriteAccessor(std::vector<string> *colNames, 
            std::vector<Type> *colTypes, 
            std::vector<Record*> *records);
        void setColNames(vector<string> colNames);
        void setColTypes(vector<Type> colTypes);
        void pushRow(Record *record);
};
