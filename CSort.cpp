/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"
#include "CScaOp.hpp"
#include "SortedVector.hpp"

CSortOp::CSortOp(IRelOp& child, string colName) {
    this->children.push_back(&child);
    this->childJobs.assign(children.begin(), children.end());
    this->colName = colName;
    producedAccessors = new vector<IAccessor*>();
}


void CSortOp::Op(vector<IVariable*>& params) {

    ITracer::GetTracer()->Trace("CSortOp::Op Called\n");

    IAccessor& inputAccessor = *children.at(0)->Value()->at(0);
    
    SortedVector *sortedRecords = new SortedVector(inputAccessor, colName, true);

    producedAccessors->push_back(&sortedRecords->getAccessor());
}


vector<IAccessor*>* CSortOp::Value() {
    return producedAccessors;
}

vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* CSortOp::getChildren() {
    ITracer::GetTracer()->Trace("CSortOp::getChildren Called\n");

    return &childJobs;
}