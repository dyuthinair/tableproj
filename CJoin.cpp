#include "IRelOp.hpp"
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include <memory>

using namespace std;

CInnerJoin::CInnerJoin(IRelOp& child1, IRelOp& child2, IScalar* tree) {
    this->children.push_back(&child1);
    this->children.push_back(&child2);
    this->childJobs.assign(children.begin(), children.end());
    this->tree = tree;
    outputAccessor = nullptr;
}

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* CInnerJoin::getChildren() {
    return &childJobs;
}

void CInnerJoin::Op(vector<IVariable*>& params) {
    ITracer::GetTracer()->Trace("CJoin::Op Called\n");

    unique_ptr<CMemTable> outputTable(new CMemTable());
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    
    IAccessor& inputAccessor1 = *children.at(0)->Value();
    IAccessor& inputAccessor2 = *children.at(1)->Value();

    vector<string> outputNames;
    vector<Type> outputTypes;

    vector<CVarRuntimeUsingRecord*> runtimeParams;

    CollectMetadata(inputAccessor1, runtimeParams, outputNames, outputTypes);
    CollectMetadata(inputAccessor2, runtimeParams, outputNames, outputTypes);

    writeAccessor.setColNames(outputNames);
    writeAccessor.setColTypes(outputTypes);

    Record* nextRecord1 = inputAccessor1.getNextRecord();
    while (nextRecord1 != nullptr) {        
        for(unsigned int paramCol = 0; paramCol < inputAccessor1.getCols(); paramCol++) { //iterates over first half of the parameters
            CVarRuntimeUsingRecord* param = runtimeParams.at(paramCol);
            param->Update(nextRecord1);
        }

        Record* nextRecord2 = inputAccessor2.getNextRecord();
        while(nextRecord2 != nullptr) {  
            for(unsigned int paramCol = inputAccessor1.getCols(); paramCol < runtimeParams.size(); paramCol++) {
                CVarRuntimeUsingRecord* param = runtimeParams.at(paramCol);
                param->Update(nextRecord2);
            }          
            
            vector<IVariable*> varParams;
            varParams.assign(runtimeParams.begin(), runtimeParams.end());
            JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
            Record curEval = evaluator->evalTree(tree, varParams);
            if(curEval.booleans.empty()) {
                throw("Join scalars should evaluate to be a boolean value");
            } 
            if(curEval.booleans.at(0)) {
                Record* newRecord = new Record();
                newRecord->copy(*nextRecord1);
                newRecord->add(*nextRecord2);
                writeAccessor.pushRow(newRecord);
                ITracer::GetTracer()->Trace("Record added\n");
            }                
            nextRecord2 = inputAccessor2.getNextRecord();
        } 
        nextRecord1 = inputAccessor1.getNextRecord();
    }
    
    this->outputAccessor = &outputTable->getAccessor();
}

void CInnerJoin::CollectMetadata(IAccessor& accessor, 
    vector<CVarRuntimeUsingRecord*>& runtimeParams,
    vector<string>& names,
    vector<Type>& types) {

    vector<int> indices (EnumCount, 0);
    for(unsigned int i = 0; i < accessor.getCols(); i++) {
        string tableName = accessor.getName();
        string curName = accessor.getColName(i);
        Type curType = accessor.getColType(i);

        names.push_back(curName);        
        types.push_back(curType);

        switch(curType)
        {
            case String:
                runtimeParams.push_back(new CVarRuntimeUsingRecord(String, curName, indices[String], tableName));
                indices[String]++;
                break;
            case Int: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Int, curName, indices[Int], tableName));
                indices[Int]++;
                break;
            case Float: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Float, curName, indices[Float], tableName));
                indices[Float]++;
                break;
            case Boolean: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Boolean, curName, indices[Boolean], tableName));
                indices[Boolean]++;
                break;
            case EnumCount:
                throw("Invalid type");  
                break;
        }
    }
}

IAccessor* CInnerJoin::Value() {
    return outputAccessor;
}