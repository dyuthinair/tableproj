/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IRelOp.hpp" 
#include "CMemTable.hpp"
#include "CVarRuntimeUsingRecord.hpp"

AccessorRelOp::AccessorRelOp(IAccessor& table)
    : table(table)
    {}

void AccessorRelOp::Op(vector<IVariable*>& params) {
    }

IAccessor* AccessorRelOp::Value() {
    return &table;
    }

vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* AccessorRelOp::getChildren() {
    ITracer::GetTracer()->Trace("AccessorRelOp::getChildren Called\n");

    return nullptr;
}
