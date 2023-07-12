/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"

CProject::CProject(IRelOp& child, vector<string> colNames, vector<Type> colTypes, 
                    vector<IScalar*> trees) {
    this->children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->trees = trees;
    outputAccessor = nullptr;
}


void CProject::Op(vector<IVariable*>& params) {
    ITracer::GetTracer()->Trace("CProject::Op Called\n");

    IAccessor& inputAccessor = *children.at(0)->Value();
    CMemTable *outputTable = new CMemTable();
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    writeAccessor.setColNames(colNames);
    writeAccessor.setColTypes(colTypes);

    vector<CVarRuntimeUsingRecord*> runtimeParams;
    vector<int> indices (EnumCount, 0);
    for(int i = 0; i < inputAccessor.getCols(); i++) {
        Type curType = inputAccessor.getColType(i);
        string colName = inputAccessor.getColName(i);
        switch(curType)
        {
            case String:
                runtimeParams.push_back(new CVarRuntimeUsingRecord(String, colName, indices[String]));
                indices[String]++;
                break;
            case Int: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Int, colName, indices[Int]));
                indices[Int]++;
                break;
            case Float: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Float, colName, indices[Float]));
                indices[Float]++;
                break;
            case Boolean: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Boolean, colName, indices[Boolean]));
                indices[Boolean]++;
                break;
            case EnumCount:
                throw("Invalid type");  
                break;
        }
    }

    while(true) {
        Record *curRecord = inputAccessor.getNextRecord();
        if(curRecord == nullptr) {
            break;
        }
        for(CVarRuntimeUsingRecord* param: runtimeParams) {
            param->Update(curRecord);
        }
        vector<IVariable*> varParams;
        varParams.assign(runtimeParams.begin(), runtimeParams.end());
        
        JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
        Record* output = new Record();
        for(IScalar* tree : trees) {
            Record curEval = evaluator->evalTree(tree, varParams);
            if(!curEval.strings.empty()) {
                output->strings.push_back(curEval.strings.at(0));
                ITracer::GetTracer()->Trace("String added: %s\n", curEval.strings.at(0).c_str());
            } else if(!curEval.nums.empty()) {
                output->nums.push_back(curEval.nums.at(0));
                ITracer::GetTracer()->Trace("Int added: %d\n", curEval.nums.at(0));
            } else if(!curEval.floats.empty()) {
                output->floats.push_back(curEval.floats.at(0));
                ITracer::GetTracer()->Trace("Float added: %f\n", curEval.floats.at(0));
            } else if(!curEval.booleans.empty()) {
                output->booleans.push_back(curEval.booleans.at(0));
                ITracer::GetTracer()->Trace("Boolean added: %s\n", curEval.booleans.at(0) ? "true" : "false");
            } else {
                throw ("Scalar evaluation not done properly");
            }
        }
        writeAccessor.pushRow(output);
    }
    
    this->outputAccessor = &outputTable->getAccessor();
}

IAccessor* CProject::Value() {
    return outputAccessor;
}

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* CProject::getChildren() {
    ITracer::GetTracer()->Trace("CProject::getChildren Called\n");

    return &childJobs;
}
