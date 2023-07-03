/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemDeserializer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

std::unordered_map<std::string, Type> enumMap;

CMemDeserializer::CMemDeserializer() {
    initMap();
}

void CMemDeserializer::initMap() {
    enumMap["string"] = String;
    enumMap["int"] = Int;
    enumMap["float"] = Float;
}

void CMemDeserializer::deserialize(string path, IWriteAccessor &tableWriter) {
    std::ifstream myfile(path);    
    vector<Record*> table;
    std::string line;
    vector<string> colNames;
    vector<Type> colTypes;
    bool isFirstRow = true;
    while (std::getline(myfile, line))
    {
        std::stringstream iss(line);
        Record* prow = isFirstRow ? new Record() : nullptr;
        int col = 0;
        while (iss.good())
        {
            string substr;
            getline(iss, substr, ',');
            if (isFirstRow)
            {
                int loop = 1;
                for(std::string::iterator it=substr.begin(); it != substr.end(); it++)
                {
                    if (*it==':')
                    {
                        colNames.push_back(std::string(substr.begin(), it-1));
                        string typeName  = std::string(it+1, substr.end());
                        Type type = enumMap.at(typeName);
                        colTypes.push_back(type);
                        break;
                    }
                    loop++;
                }
            }
            else
            {
                Type type = colTypes[col];
                std::cout << type << "\n";
                switch(type)
                {
                    case String: 
                        prow->strings.push_back(substr);
                        break;
                    case Int: 
                        prow->nums.push_back(atoi(substr.c_str()));
                        break;
                    case Float: 
                        prow->floats.push_back(atoi(substr.c_str()));
                        break;
                }
                col++;
            }
        }
        if(isFirstRow) {
            isFirstRow = false;
        } else {
            table.push_back(prow);
        }
    }
    printTable(&table);
}

void CMemDeserializer::printTable(vector<Record*> *table) {
    std::cout << "s" << "\n";
    for(Record* r : *table) {
        std::cout << "s" << "\n";
        for(string s : r->strings) {
            std::cout << "s" << "\n";
        }
    }
}
