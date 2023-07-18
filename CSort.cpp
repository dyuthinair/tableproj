/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include "CScaOp.hpp"
#include <set>

CSortOp::CSortOp(IRelOp& child, string colName) 
{
    this->children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    this->colName = colName;
    outputAccessor = nullptr;
}


void CSortOp::Op(vector<IVariable*>& params) {

    ITracer::GetTracer()->Trace("CSortOp::Op Called\n");

    IAccessor& inputAccessor = *children.at(0)->Value();
    CMemTable *outputTable = new CMemTable();
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    vector<string> colNames;
    vector<Type> colTypes;

    vector<CVarRuntimeUsingRecord*> runtimeParams;
    vector<int> indices (EnumCount, 0);
    Type sortType;
    int sortIndex = -1;
    for(unsigned int i = 0; i < inputAccessor.getCols(); i++) {
        Type curType = inputAccessor.getColType(i);
        string curColName = inputAccessor.getColName(i);
        
        colNames.push_back(curColName);
        colTypes.push_back(curType);
        if(colName.compare(curColName) == 0) {
            sortType = curType;
            sortIndex = indices[curType];
        }
        runtimeParams.push_back(new CVarRuntimeUsingRecord(curType, curColName, indices[curType]));
        indices[curType]++;
    }

    writeAccessor.setColNames(colNames);
    writeAccessor.setColTypes(colTypes);

    vector<Record*> sortedRecords;

    while(true) {
        Record *curRecord = inputAccessor.getNextRecord();
        if(curRecord == nullptr) {
            break;
        }

        CConstVal *valToInsert;
        switch(sortType) {
            case String: 
                valToInsert = new StringValue(curRecord->strings.at(sortIndex));
                break;
            case Int: 
                valToInsert = new IntValue(curRecord->nums.at(sortIndex));
                break;
            case Float: 
                valToInsert = new FloatValue(curRecord->floats.at(sortIndex));
                break;
            case Boolean: 
                valToInsert = new BoolValue(curRecord->booleans.at(sortIndex));
                break;
            case EnumCount:
                throw("Not a real type");
                break;
        }
        int lowIndex = 0;
        int highIndex = sortedRecords.size() - 1;
        int mid = 0;
        while(true) {    

            if(lowIndex > highIndex) {
                sortedRecords.insert(sortedRecords.begin() + lowIndex, curRecord);
                ITracer::GetTracer()->Trace("CSortOp added a record to the sorted vector\n");
                break;
            }

            mid = (lowIndex + highIndex) / 2;  
            Record *midRecord = sortedRecords.at(mid);

            for(CVarRuntimeUsingRecord* param: runtimeParams) {
                param->Update(midRecord);
            }

            vector<IVariable*> varParams;
            varParams.assign(runtimeParams.begin(), runtimeParams.end());
            JobEval<IScalar, Record, vector<IVariable*>>* evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
            ScaOpComp *comparer = new ScaOpComp(valToInsert, new CVarRef(sortType, colName));
            Record curEval = evaluator->evalTree(comparer, varParams);
            int compOutput = curEval.nums.at(0);

            if(compOutput == 0) {
                sortedRecords.insert(sortedRecords.begin() + highIndex, curRecord);
                ITracer::GetTracer()->Trace("CSortOp added a record to the sorted vector\n");
                break;
            } else if(compOutput == 1) {
                lowIndex = mid + 1;
            } else if(compOutput == -1) {
                highIndex = mid - 1;
            } else {
                throw("Issue with scalar comparator");
            }
        }
    }    

    for(Record* rec : sortedRecords) {
        writeAccessor.pushRow(rec);
    }

    this->outputAccessor = &outputTable->getAccessor();
}


IAccessor* CSortOp::Value() {
    return outputAccessor;
}

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* CSortOp::getChildren() {
    ITracer::GetTracer()->Trace("CSortOp::getChildren Called\n");

    return &childJobs;
}