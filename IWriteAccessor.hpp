/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IAccessor.hpp"
#include <string>
#include <vector>

using namespace std;

#pragma once

class IWriteAccessor {
        public: 
                void virtual setColNames(vector<string> colNames) = 0;
                void virtual setColTypes(vector<Type> colTypes) = 0;
                void virtual pushRow(Record *record) = 0;
};