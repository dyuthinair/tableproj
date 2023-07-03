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
    void virtual setColTypes(int rows, std::vector<Type>, std::vector<std::string>) = 0;
    void virtual pushRow(Record record) = 0;
};