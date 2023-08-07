
/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include <vector>
#include <string>
#include "IJob.hpp"
#include "itracer.hpp"

using namespace std;

enum Type
{
    String,
    Int,
    Float, 
    Boolean,
    EnumCount
};

inline string toString(Type t)
{
    switch (t)
    {
        case String:   
            return "string";
        case Int:   
            return "int";
        case Float: 
            return "float";
        case Boolean: 
            return "boolean";
        case EnumCount: 
            throw("Not a real type");
    }
    throw("Unreachable code");
}

class IAccessor;

class Record
{
    public:
        std::vector<std::string> strings;
        std::vector<int> nums;
        std::vector<float> floats;
        std::vector<bool> booleans;

        IAccessor* SetValue{nullptr};

        bool operator==(const Record &rhs ) {
            return strings == rhs.strings
            && nums == rhs.nums
            && floats == rhs.floats
            && booleans == rhs.booleans;
        }   

        void copy(const Record& rec) {
            this->strings.clear();
            this->nums.clear();
            this->floats.clear();
            this->booleans.clear();
            this->add(rec);
        }

        void add(const Record& rec) {
            for(string str : rec.strings) {
                this->strings.push_back(str);
            }
            for(unsigned int num : rec.nums) {
                this->nums.push_back(num);
            }
            for(float num : rec.floats) {
                this->floats.push_back(num);
            }
            for(bool boolean : rec.booleans) {
                this->booleans.push_back(boolean);
            }
            this->SetValue = rec.SetValue;
        }
};

class IAccessor
{
    public: 
        unsigned int virtual getCols() = 0;
        Type virtual getColType(int col) = 0;
        string virtual getColName(int col) = 0;
        Record virtual *getNextRecord() = 0;
        string virtual getName() = 0;
};


