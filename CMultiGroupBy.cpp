#include "IRelOp.hpp"
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include <memory>
#include <queue>


using namespace std;

CMultiGroupBy::CMultiGroupBy(IRelOp& child) {

    children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    producedAccessors = new vector<IAccessor*>();
}

vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* CMultiGroupBy::getChildren() {
    return &childJobs;
}

void CMultiGroupBy::Op(vector<IVariable*>& params) {
    ITracer::GetTracer()->Trace("CMultiGroupBy::Op Called\n");

    unique_ptr<CMemTable> outputTable(new CMemTable());
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    
    vector<Record*> incompleteRecords;
    
    vector<IAccessor*>* accessors = children.at(0)->Value();
    IAccessor* firstHashTable = accessors->at(0);

    vector<string> outputNames;
    vector<Type> outputTypes;

    int numberOfCols = firstHashTable->getCols();
    for(int i = 0; i < numberOfCols; i++) {
        Type curType = firstHashTable->getColType(i);
        string colName = firstHashTable->getColName(i);

        outputNames.push_back(colName);
        outputTypes.push_back(curType);
    }
    if (accessors->size() > 1) {
        for(auto it = accessors->begin()+1; it != accessors->end(); it++) {
            Type lastColType = (*it)->getColType(numberOfCols-1);
            outputNames.push_back((*it)->getColName(numberOfCols-1));
            outputTypes.push_back(lastColType);
        }
    }

    writeAccessor.setColNames(outputNames);
    writeAccessor.setColTypes(outputTypes);

    producedAccessors->push_back(&outputTable->getAccessor());

    while(true) {
        Record* leftRecord = accessors->at(0)->getNextRecord();
        if (leftRecord == nullptr)
            return;

        if (accessors->size() > 1) {
            for(auto it = accessors->begin()+1; it != accessors->end(); it++) {
                Type lastColType = (*it)->getColType(numberOfCols-1);
                Record* rightRecord = (*it)->getNextRecord();
                
                switch (lastColType) {
                    case String:   
                        leftRecord->strings.push_back(rightRecord->strings.at(rightRecord->strings.size()-1));
                        break;
                    case Int:   
                        leftRecord->nums.push_back(rightRecord->nums.at(rightRecord->nums.size()-1));
                        break;
                    case Float: 
                        leftRecord->floats.push_back(rightRecord->floats.at(rightRecord->floats.size()-1));
                        break;
                    case Boolean: 
                        leftRecord->booleans.push_back(rightRecord->booleans.at(rightRecord->booleans.size()-1));
                        break;
                    case EnumCount: 
                        throw("Not a real type");
                }
            }
        } 
        writeAccessor.pushRow(leftRecord);
    }  
}

vector<IAccessor*>* CMultiGroupBy::Value() {
    return producedAccessors;
}

