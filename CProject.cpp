/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"

CProject::CProject(IAccessor& inputAccessor, vector<string> colNames, vector<Type> colTypes, 
                    vector<IScalar*> trees) 
                    : inputAccessor(inputAccessor) {
    this->colNames = colNames;
    this->colTypes = colTypes;
    this->trees = trees;
    outputAccessor = nullptr;
}


void CProject::Op(vector<IVariable*>& params) {
    CMemTable *outputTable = new CMemTable();
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    writeAccessor.setColNames(colNames);
    writeAccessor.setColTypes(colTypes);

    for(IScalar* tree : trees) {
        while(true) {
            vector<IVariable*> params;
            Record *curRecord = inputAccessor.getNextRecord();
            if(curRecord == nullptr) {
                break;
            }
            vector<int> indices (EnumCount, 0);
            for(int i = 0; i < inputAccessor.getCols(); i++) {
                Type curType = inputAccessor.getColType(i);
                switch(curType)
                {
                    case String:
                        params.push_back(new CVarRuntime(String, inputAccessor.getColName(i), new StringValue(curRecord->strings[indices[String]])));
                        indices[String]++;
                        break;
                    case Int: 
                        params.push_back(new CVarRuntime(Int, inputAccessor.getColName(i), new IntValue(curRecord->nums[indices[Int]])));
                        indices[Int]++;
                        break;
                    case Float: 
                        params.push_back(new CVarRuntime(Float, inputAccessor.getColName(i), new FloatValue(curRecord->floats[indices[Float]])));
                        indices[Float]++;
                        break;
                    case Boolean: 
                        params.push_back(new CVarRuntime(Boolean, inputAccessor.getColName(i), new BoolValue(curRecord->booleans[indices[Boolean]])));
                        indices[Boolean]++;
                        break;
                    case EnumCount:
                        throw("Invalid type");  
                        break;
                }
            }
            JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
            Record* output = new Record();
            output->copy(evaluator->evalTree(tree, params));
            writeAccessor.pushRow(output);
            ITracer::GetTracer()->Trace("Record done, %f added\n", output->floats.at(0));
        }
    }
    this->outputAccessor = &outputTable->getAccessor();
}

IAccessor* CProject::Value() {
    return outputAccessor;
}
