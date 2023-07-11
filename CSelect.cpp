/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"

CSelect::CSelect(IAccessor& inputAccessor, vector<IScalar*> trees) 
                    : inputAccessor(inputAccessor) {
    this->trees = trees;
    outputAccessor = nullptr;
}


void CSelect::Op(vector<IVariable*>& params) {
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
        bool toKeep = true;
        JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
        for(IScalar* tree : trees) {
            Record curEval = evaluator->evalTree(tree, varParams);
            if(curEval.booleans.empty()) {
                throw("Input to select should be a boolean value");
            } else {
                if(curEval.booleans.at(0) == false) {
                    toKeep = false;
                } 
            }
        }
        if(toKeep) {
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
