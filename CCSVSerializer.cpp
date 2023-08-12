/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CCSVSerializer.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

CCSVSerializer::CCSVSerializer() {

}

void CCSVSerializer::serialize(string path, IAccessor &tableReader) {
    std::ofstream file(path); 
    
    string header = "";
    for(unsigned int i = 0; i < tableReader.getCols(); i++) {
        header += tableReader.getColName(i) + ":";
        header += toString(tableReader.getColType(i)) + ", ";
    }
    header = string(header.begin(), header.end() - 2);
    file << header << "\n";

    int rowNum = 1;
    while(true) {
        Record *record = tableReader.getNextRecord();
        if(record == nullptr) {
            break;
        }
        string row = "";
        vector<int> indices (EnumCount, 0);
        for(unsigned int i = 0; i < tableReader.getCols(); i++) {
            Type type = tableReader.getColType(i);
            switch(type)
            {
                case String: 
                {
                    row += record->strings.at(indices[String]);
                    indices[String]++;
                    break;
                }
                case Int: 
                {
                    row += to_string(record->nums.at(indices[Int]));
                    indices[Int]++;
                    break;
                }
                case Float: 
                {
                    row += to_string(record->floats.at(indices[Float]));
                    indices[Float]++;
                    break;
                }
                case Boolean:
                {
                    bool val = record->booleans.at(indices[Boolean]);
                    indices[Boolean]++;
                    if(val == true) {
                        row +="True";
                    } else if(val == false) {
                        row += "False";
                    } else {
                        throw std::invalid_argument("Invalid boolean value");
                    }
                    break;
                }
                case Datetime: 
                {
                    time_t val;
                    val = record->datetimes.at(indices[Datetime]);
                    indices[Datetime]++;
                    char timeString[size("yyyy-mm-ddThh:mm:ssZ")];
                    strftime(timeString, size(timeString), "%Y-%m-%d %H:%M:%S", gmtime(&val));
                    row += timeString;
                    break;
                }
                case EnumCount:
                {
                    throw std::invalid_argument("Invalid type");
                    break;
                }
            }
            row += ", ";
        }
        row = string(row.begin(), row.end() - 2);
        ITracer::GetTracer()->Trace("Row %d printed\n", rowNum);
        file << row + "\n";
        rowNum++;
    }
    file.close();
}

