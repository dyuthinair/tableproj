#include "IRelOp.hpp"
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include <memory>
#include <queue>


using namespace std;

CMergeJoin::CMergeJoin(IRelOp& child1, IRelOp& child2, IScalar* tree) {
    this->children.push_back(&child1);
    this->children.push_back(&child2);
    this->childJobs.assign(children.begin(), children.end());
    this->tree = tree;
    evaluator = new JobEval<IScalar, Record, vector<IVariable*>>();
    producedAccessors = new vector<IAccessor*>();
}

vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* CMergeJoin::getChildren() {
    return &childJobs;
}

void CMergeJoin::Op(vector<IVariable*>& params) {
    ITracer::GetTracer()->Trace("CMergeJoin::Op Called\n");

    unique_ptr<CMemTable> outputTable(new CMemTable());
    IWriteAccessor& writeAccessor = outputTable->getWriteAccessor();
    
    IAccessor& inputAccessor1 = *children.at(0)->Value()->at(0);
    IAccessor& inputAccessor2 = *children.at(1)->Value()->at(0);

    vector<string> outputNames;
    vector<Type> outputTypes;

    vector<CVarRuntimeUsingRecord*> runtimeParams;

    CollectMetadata(inputAccessor1, runtimeParams, outputNames, outputTypes);
    CollectMetadata(inputAccessor2, runtimeParams, outputNames, outputTypes);

    writeAccessor.setColNames(outputNames);
    writeAccessor.setColTypes(outputTypes);

    Record* leftRecord = inputAccessor1.getNextRecord();
    Record* rightRecord = inputAccessor2.getNextRecord();

    bool changedLeftRow = true;
    bool changedRightRow = true;

    vector<Record*> duplicates;
    while(leftRecord != nullptr && rightRecord != nullptr) {
        int eval = EvalCurrentRow(changedLeftRow, changedRightRow, inputAccessor1.getCols(), leftRecord, rightRecord, runtimeParams);
        
        if(eval == 0) {
            ProduceRecord(leftRecord, rightRecord, writeAccessor);
            duplicates.push_back(rightRecord);
        }
        if(eval == -1) {
            leftRecord = inputAccessor1.getNextRecord();
            changedLeftRow = true;
            changedRightRow = !duplicates.empty();
            if (changedRightRow)
            {
                HandleDuplicates(leftRecord, duplicates, inputAccessor1.getCols(), writeAccessor, runtimeParams);
            }
            ITracer::GetTracer()->Trace("table1 increments\n");
        } else
        {
            rightRecord = inputAccessor2.getNextRecord();
            changedLeftRow = false;
            changedRightRow = true;
        } 
    }
      
    producedAccessors->push_back(&outputTable->getAccessor());
}

int CMergeJoin::EvalCurrentRow(bool updateLeft, bool updateRight, int leftcols, Record* left, Record* right, vector<CVarRuntimeUsingRecord*>& runtimeParams)
{
    if(updateLeft) {
        for(int paramCol = 0; paramCol < leftcols; paramCol++) { //iterates over first half of the parameters
            CVarRuntimeUsingRecord* param = runtimeParams.at(paramCol);
            param->Update(*left);
        } 
    }

    if(updateRight) {
        for(int paramCol = leftcols; paramCol < (int) runtimeParams.size(); paramCol++) { //iterates over second half of the parameters
            CVarRuntimeUsingRecord* param = runtimeParams.at(paramCol);
            param->Update(*right);
        } 
    }

    vector<IVariable*> varParams;
    varParams.assign(runtimeParams.begin(), runtimeParams.end());
    
    Record curEval = evaluator->evalTree(tree, varParams);
    return curEval.nums.at(0);
}

void CMergeJoin::ProduceRecord(Record* leftRecord, Record* rightRecord, IWriteAccessor& writeAccessor)
{
    Record* newRecord = new Record();
    newRecord->copy(*leftRecord);
    newRecord->add(*rightRecord);
    writeAccessor.pushRow(newRecord);
    ITracer::GetTracer()->Trace("Record added\n");
}

void CMergeJoin::HandleDuplicates(Record* leftRecord, vector<Record*>& duplicates, int cols, IWriteAccessor& writeAccessor, vector<CVarRuntimeUsingRecord*>& runtimeParams)
{
    int eval = EvalCurrentRow(true, true, cols, leftRecord, duplicates.at(0), runtimeParams);
    if (eval == 0)
    {
        ITracer::GetTracer()->Trace("Duplicates on join condition found\n");
        for(Record* rec:duplicates)
        {
            ProduceRecord(leftRecord, rec, writeAccessor);
        }
    }
    duplicates.clear();
}

void CMergeJoin::CollectMetadata(IAccessor& accessor, 
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
            case Datetime: 
                runtimeParams.push_back(new CVarRuntimeUsingRecord(Datetime, curName, indices[Datetime], tableName));
                indices[Datetime]++;
                break;
            case EnumCount:
                throw std::invalid_argument("Invalid type");  
                break;
        }
    }
}

vector<IAccessor*>* CMergeJoin::Value() {
    return producedAccessors;
}

