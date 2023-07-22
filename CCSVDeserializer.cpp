/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CCSVDeserializer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Tokenizer.hpp"

using namespace std;

std::unordered_map<std::string, Type> enumMap;

CCSVDeserializer::CCSVDeserializer() {
    initMap();
}

void CCSVDeserializer::initMap() {
    enumMap["string"] = String;
    enumMap["int"] = Int;
    enumMap["float"] = Float;
}

inline std::string trim(std::string& str)
{
    str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    return str;
}

void CCSVDeserializer::deserialize(string path, IWriteAccessor &tableWriter) {
    std::ifstream myfile(path);    
    std::string line;
    vector<string> colNames;
    vector<Type> colTypes;
    bool isFirstRow = true;
    while (std::getline(myfile, line))
    {
        Record* prow = !isFirstRow ? new Record() : nullptr;
        Tokenizer tokenizer(line);
        int col=0;
        while(tokenizer.HasMore())
        {
            if (isFirstRow) {
                string name = tokenizer.GetToken();
                colNames.push_back(name);
                string type = tokenizer.GetToken();
                colTypes.push_back(enumMap.at(type));
            } else {
                string token = tokenizer.GetToken();
                Type type = colTypes[col];
                insert(type, prow, token);
            }
            col++;
        }
        if(isFirstRow) {
            isFirstRow = false;
            tableWriter.setColNames(colNames);
            tableWriter.setColTypes(colTypes);
        } else {
            tableWriter.pushRow(prow);
        }

    }
    myfile.close();
}

void CCSVDeserializer::insert (Type type, Record* prow, string value) {
    switch(type)
    {
        case String: 
            prow->strings.push_back(value);
            break;
        case Int: 
            prow->nums.push_back(atoi(value.c_str()));
            break;
        case Float: 
            prow->floats.push_back(atof(value.c_str()));
            break;
        case Boolean: 
            bool val;
            if(value.compare("True") == 0 || value.compare("true") == 0) {
                val = true;
            } else if(value.compare("False") == 0 || value.compare("false") == 0){
                val = false;
            } else {
                throw("Invalid boolean value");
            }
            prow->booleans.push_back(val);
            break;
        case EnumCount:
            throw("Invalid type");
            break;
    }
}