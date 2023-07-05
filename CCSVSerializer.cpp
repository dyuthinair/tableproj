/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CCSVSerializer.hpp"
#include <iostream>
#include <fstream>

using namespace std;

CCSVSerializer::CCSVSerializer() {

}

void CCSVSerializer::serialize(string path, IAccessor &tableReader) {
    std::ofstream file(path); 
    
    string header = "";
    for(int i = 0; i < tableReader.getCols(); i++) {
        header += tableReader.getColName(i) + ":";
        header += toString(tableReader.getColType(i)) + ", ";
    }
    header = string(header.begin(), header.end() - 2);
    file << header << "\n";

    Record *record = tableReader.getNextRecord();
    while(record != nullptr) {
        string row = "";
        int strIndex = 0;
        int numIndex = 0;
        int floatIndex = 0;
        for(int i = 0; i < tableReader.getCols(); i++) {
            Type type = tableReader.getColType(i);
            switch(type)
            {
                case String: 
                    row += record->strings.at(strIndex);
                    strIndex++;
                    break;
                case Int: 
                    row += to_string(record->nums.at(numIndex));
                    numIndex++;
                    break;
                case Float: 
                    row += to_string(record->floats.at(floatIndex));
                    floatIndex++;
                    break;
            }
            row += ", ";
        }
        row = string(row.begin(), row.end() - 2);
        file << row + "\n";
        record = tableReader.getNextRecord();
    }    
    file.close();
}

