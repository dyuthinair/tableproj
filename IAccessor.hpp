
/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include <vector>
#include <string>

using namespace std;

#pragma once
enum Type
{
    String,
    Int,
    Float
};

struct Record
{
    std::vector<std::string> strings;
    std::vector<int> nums;
    std::vector<float> floats;
    friend std::istream& operator>>(std::istream& input, Record& r);
};

class IAccessor
{
    int virtual getCols() = 0;
    Type virtual getType() = 0;
};

