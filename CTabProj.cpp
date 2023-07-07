/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CTabProj.hpp"
#include "CMemTable.hpp"
#include <map>

CTabProj::CTabProj() {

}

ITable& Op(CMemTable *tab1, vector<string> cols) {
    CMemTable *result = new CMemTable();
    CMemWriteAccessor writeAccessor = result->getWriteAccessor();
    writeAccessor.setColNames(cols);
    CMemReadAccessor readAccessor = tab1->getAccessor();
    vector<Type> types;
    vector<int> indeces (EnumCount, 0);
    vector<int> projIndex; 
    bool isFirstPass = true;
    for(string s : cols) {
        for(int i = 0; i < readAccessor.getCols(); i++) {
            Type curType = readAccessor.getColType(i);
            if(readAccessor.getColName(i).compare(s) == 0) {
                types.push_back(curType);
                projIndex.push_back(indeces.at(curType));
            }
            indeces.at(curType)++;
        }    
    }
    writeAccessor.setColTypes(types);
    Record *current = readAccessor.getNextRecord();
    while(current != nullptr) {
        Record *newRecord = new Record;
        for(Type t : types) {
            switch(t)
                {
                    case String: 
                        newRecord->strings.push_back();
                        break;
                    case Int: 
                        newRecord->nums.push_back();
                        break;
                    case Float: 
                        newRecord->floats.push_back();
                        break;
                }
        }
        current = readAccessor.getNextRecord();
    }    



}