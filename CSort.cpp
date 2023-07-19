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
    outputAccessor = nullptr;
}


void CSortOp::Op(vector<IVariable*>& params) {

    ITracer::GetTracer()->Trace("CSortOp::Op Called\n");

    IAccessor& inputAccessor = *children.at(0)->Value();
    
    SortedVector *sortedRecords = new SortedVector(inputAccessor, colName, true);

    this->outputAccessor = &sortedRecords->getAccessor();
}


IAccessor* CSortOp::Value() {
    return outputAccessor;
}

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* CSortOp::getChildren() {
    ITracer::GetTracer()->Trace("CSortOp::getChildren Called\n");

    return &childJobs;
}