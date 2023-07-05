
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

inline string toString(Type t)
{
    switch (t)
    {
        case String:   return "string";
        case Int:   return "int";
        case Float: return "float";
    }
}

class Record
{
    public:
        std::vector<std::string> strings;
        std::vector<int> nums;
        std::vector<float> floats;
};

class IAccessor
{
    public: 
        int virtual getCols() = 0;
        Type virtual getColType(int col) = 0;
        string virtual getColName(int col) = 0;
        Record virtual *getNextRecord() = 0;
};

