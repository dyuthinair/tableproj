/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include <memory>

CProject::CProject(IRelOp& child, vector<string> colNames, vector<Type> colTypes, 
                    vector<IScalar*> trees, bool projectAgg) {
    this->children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->trees = trees;
    outputAccessor = nullptr;
    this->projectAgg = projectAgg;
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
    for(unsigned int i = 0; i < inputAccessor.getCols(); i++) {
        Type curType = inputAccessor.getColType(i);
        string colName = inputAccessor.getColName(i);
        runtimeParams.push_back(new CVarRuntimeUsingRecord(curType, colName, indices[curType]));
        indices[curType]++;
    }

    Record* prevRecord = nullptr;

    while(true) {
        Record* output = new Record();

        Record *curRecord = inputAccessor.getNextRecord();
        if(curRecord == nullptr) {
            if(projectAgg && prevRecord != nullptr) {  
                writeAccessor.pushRow(prevRecord);
            } 
            break;
        }
        for(CVarRuntimeUsingRecord* param: runtimeParams) {
            param->Update(*curRecord);
        }
        vector<IVariable*> varParams;
        varParams.assign(runtimeParams.begin(), runtimeParams.end());
        
        JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
        
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
        if(!projectAgg) { 
            writeAccessor.pushRow(output);                 
        } else {
            prevRecord = output;
        }
        
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
