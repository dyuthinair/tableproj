/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"

CSelect::CSelect(IRelOp& child, IScalar* tree) 
{
    this->children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    this->tree = tree;
    outputAccessor = nullptr;
}


void CSelect::Op(vector<IVariable*>& params) {

    ITracer::GetTracer()->Trace("CSelect::Op Called\n");

    IAccessor& inputAccessor = *children.at(0)->Value();
    CMemTable *outputTable = new CMemTable();
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    vector<string> colNames;
    vector<Type> colTypes;
    
    vector<CVarRuntimeUsingRecord*> runtimeParams;
    vector<int> indices (EnumCount, 0);
    for(int i = 0; i < inputAccessor.getCols(); i++) {
        Type curType = inputAccessor.getColType(i);
        string colName = inputAccessor.getColName(i);

        colNames.push_back(colName);
        colTypes.push_back(curType);
        
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
    writeAccessor.setColNames(colNames);
    writeAccessor.setColTypes(colTypes);

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
        Record curEval = evaluator->evalTree(tree, varParams);
        if(curEval.booleans.empty()) {
            throw("Input to select should be a boolean value");
        } 
        if(curEval.booleans.at(0)) {
            Record* newRecord = new Record();
            newRecord->copy(*curRecord);
            writeAccessor.pushRow(newRecord);
            ITracer::GetTracer()->Trace("Record added\n");
        }
        
    }    
    this->outputAccessor = &outputTable->getAccessor();
}

IAccessor* CSelect::Value() {
    return outputAccessor;
}

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* CSelect::getChildren() {
    ITracer::GetTracer()->Trace("CSelect::getChildren Called\n");

    return &childJobs;
}