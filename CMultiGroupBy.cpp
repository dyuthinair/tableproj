#include "IRelOp.hpp"
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include <memory>
#include <queue>


using namespace std;

CMultiGroupBy::CMultiGroupBy(vector<IRelOp&>* hashAccessors) {
    for(IRelOp& accessor : *hashAccessors) {
        children.push_back(&accessor);
    }
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
    
    IAccessor& inputAccessor1 = *children.at(0)->Value();
    IAccessor& inputAccessor2 = *children.at(1)->Value();

    vector<string> outputNames;
    vector<Type> outputTypes;

    vector<CVarRuntimeUsingRecord*> runtimeParams;


    writeAccessor.setColNames(outputNames);
    writeAccessor.setColTypes(outputTypes);

    Record* leftRecord = inputAccessor1.getNextRecord();
    Record* rightRecord = inputAccessor2.getNextRecord();

    bool changedLeftRow = true;
    bool changedRightRow = true;

    vector<Record*> duplicates;
    
      
    producedAccessors->push_back(&outputTable->getAccessor());
}

vector<IAccessor*>* CMultiGroupBy::Value() {
    return producedAccessors;
}

