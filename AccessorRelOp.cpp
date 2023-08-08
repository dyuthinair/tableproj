/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"

AccessorRelOp::AccessorRelOp(IAccessor* table) {
    producedAccessors = new vector<IAccessor*>();
    producedAccessors->push_back(table);
}

void AccessorRelOp::Op(vector<IVariable*>& params) {

}

vector<IAccessor*>* AccessorRelOp::Value() {
    return producedAccessors;
}

vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* AccessorRelOp::getChildren() {
    ITracer::GetTracer()->Trace("AccessorRelOp::getChildren Called\n");

    return nullptr;
}
