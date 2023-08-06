/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"

CRecordColumn::CRecordColumn(int col, Type type, Record* record) {

    ITracer::GetTracer()->Trace("CRecordColumn Constructor Called\n");

    this->col = col;
    this->type = type;
    this->record = record;
}

Type CRecordColumn::getType() {
    return type;
}

Record CRecordColumn::Value() {
    return *record;
}

void CRecordColumn::Op(vector<IVariable*> &variables) {

}

void CRecordColumn::Update(const Record& value) {

}

int CRecordColumn::Comp(IScalar& rhs) {
    ITracer::GetTracer()->Trace("CRecordColumn::Comp called\n");
    int comp;
    switch(type) {
        case String: 
            comp = record->strings.at(col).compare(rhs.Value().strings.at(col));
            comp = normalizeEval(comp);
            ITracer::GetTracer()->Trace("CRecordColumn::Comp result between %s and %s is %d\n", record->strings.at(col).c_str(), 
                                            rhs.Value().strings.at(col).c_str(), comp);
            break;
        case Int: 
            comp = record->nums.at(col) - rhs.Value().nums.at(col);
            comp = normalizeEval(comp);
            ITracer::GetTracer()->Trace("CRecordColumn::Comp result between %d and %d is %d\n", record->nums.at(col), 
                                            rhs.Value().nums.at(col), comp);
            break;
        case Float: 
            comp = static_cast<int>(100* (record->floats.at(col) - rhs.Value().floats.at(col)));
            comp = normalizeEval(comp);
            ITracer::GetTracer()->Trace("CRecordColumn::Comp result between %f and %f is %d\n", record->floats.at(col), 
                                            rhs.Value().floats.at(col), comp);
            break;
        case Boolean: 
            comp = record->booleans.at(col) - rhs.Value().booleans.at(col);
            comp = normalizeEval(comp);
            ITracer::GetTracer()->Trace("CRecordColumn::Comp result %d\n", comp);
            break;
        case EnumCount:
            throw("Not a real type");
            break;
    }
    return comp;
}

int CRecordColumn::normalizeEval(int difference) {
    if(difference == 0) {
        return 0;
    } else if(difference > 0) {
        return 1;
    } else if (difference < 0) {
        return -1;
    } else {
        throw("Unreachable code");
    }
}