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
        std::stringstream iss(line);
        Record* prow = !isFirstRow ? new Record() : nullptr;
        int col = 0;
        while (iss.good())
        {
            string substr;
            getline(iss, substr, ',');
            substr.erase(remove(substr.begin(), substr.end(), '"'), substr.end());
            if (isFirstRow)
            {
                for(std::string::iterator it=substr.begin(); it != substr.end(); it++)
                {
                    if (*it==':')
                    {
                        string name = std::string(substr.begin(), it);
                        trim(name);
                        colNames.push_back(name);
                        string typeName  = std::string(it+1, substr.end());
                        trim(typeName);
                        Type type = enumMap.at(typeName);
                        colTypes.push_back(type);
                        break;
                    }
                }
                col++;
            }
            else
            {
                Type type = colTypes[col];
                switch(type)
                {
                    case String: 
                        prow->strings.push_back(substr);
                        break;
                    case Int: 
                        prow->nums.push_back(atoi(substr.c_str()));
                        break;
                    case Float: 
                        prow->floats.push_back(atof(substr.c_str()));
                        break;
                    case Boolean: 
                        bool val;
                        if(substr.compare("True") == 0 || substr.compare("true") == 0) {
                            val = true;
                        } else if(substr.compare("False") == 0 || substr.compare("false") == 0){
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
                col++;
            }
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
