/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CCSVDeserializer.hpp"
#include "Tokenizer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <string.h>

using namespace std;

std::unordered_map<std::string, Type> enumMap;

CCSVDeserializer::CCSVDeserializer() {
    initMap();
}

void CCSVDeserializer::initMap() {
    enumMap["string"] = String;
    enumMap["int"] = Int;
    enumMap["float"] = Float;
    enumMap["boolean"] = Boolean;
    enumMap["datetime"] = Datetime;
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
                string name = tokenizer.GetToken({',', ':'});
                colNames.push_back(name);
                string type = tokenizer.GetToken({',', ':'});
                colTypes.push_back(enumMap.at(type));
            } else {
                string token = tokenizer.GetToken({','});
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
                throw std::invalid_argument("Invalid boolean value");
            }
            prow->booleans.push_back(val);
            break;
        case Datetime:
        {
            time_t parsedTime;
            struct tm tm;
            istringstream ss(value);
            ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S"); // or just %T in this case
            parsedTime = mktime(&tm);
            prow->datetimes.push_back(parsedTime);
            break;
        }
        case EnumCount:
            throw std::invalid_argument("Invalid type");
            break;
    }
}