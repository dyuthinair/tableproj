/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CScaOp.hpp"
#include <time.h>

using namespace std;

ScaOpEq::ScaOpEq(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{

}

void ScaOpEq::Op(vector<IVariable*>& params) {
    ITracer::GetTracer()->Trace("ScaOpEq::Op called \n");
    bool result;

    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw std::invalid_argument("Cannot compare strings"); 
                break;
            case Int: 
                result = val1->Value().nums.at(0) == val2->Value().nums.at(0);
                this->eval = BoolValue(result);
                ITracer::GetTracer()->Trace("ScaOpEq::Op result: %d = %d is %s\n", val1->Value().nums.at(0), val2->Value().nums.at(0), result ? "true" : "false");
                break;
            case Float: 
                this->eval = BoolValue(val1->Value().floats.at(0) == val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpEq::Op result %s\n",  eval.Value().booleans.at(0) ? "true" : "false");
                break;
            case Boolean: 
                throw std::invalid_argument("Cannot compare booleanas"); 
                break;
            case Datetime:
                throw std::invalid_argument("Cannot compare datetimes"); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpEq::Value() {
    return eval.Value();
}

Type ScaOpEq::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpEq::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpAdd::ScaOpAdd(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpAdd::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpAdd::Op called ");

    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw std::invalid_argument("Cannot add strings"); 
                break;
            case Int: 
                this->result = new IntValue(val1->Value().nums.at(0) + val2->Value().nums.at(0));
                ITracer::GetTracer()->Trace("ScaOpAdd::Op result %d\n",  result->Value().nums.at(0));
                break;
            case Float: 
                this->result = new FloatValue(val1->Value().floats.at(0) + val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpAdd::Op result %f\n",  result->Value().floats.at(0));
                break;
            case Boolean: 
                throw std::invalid_argument("Cannot add booleanas"); 
                break;
            case Datetime: 
                throw std::invalid_argument("Cannot add datetimes"); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpAdd::Value() {
    return result->Value();
}

Type ScaOpAdd::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpAdd::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpSub::ScaOpSub(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpSub::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpSub::Op called ");

    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw std::invalid_argument("Cannot subtract strings"); 
                break;
            case Int: 
                this->result = new IntValue(val1->Value().nums.at(0) - val2->Value().nums.at(0));
                ITracer::GetTracer()->Trace("ScaOpSub::Op result %d\n",  result->Value().nums.at(0));
                break;
            case Float: 
                this->result = new FloatValue(val1->Value().floats.at(0) - val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpSub::Op result %f\n",  result->Value().floats.at(0));
                break;
            case Boolean: 
                throw std::invalid_argument("Cannot subtract booleanas"); 
                break;
            case Datetime: 
                throw std::invalid_argument("Cannot subtract datetimes"); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpSub::Value() {
    return result->Value();
}

Type ScaOpSub::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpSub::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpGt::ScaOpGt(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpGt::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpGt::Op called \n");
    bool result;

    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw std::invalid_argument("Cannot compare strings"); 
                break;
            case Int: 
                result = val1->Value().nums.at(0) > val2->Value().nums.at(0);
                this->eval = BoolValue(result);
                ITracer::GetTracer()->Trace("ScaOpGt::Op result: %d > %d is %s\n", val1->Value().nums.at(0), val2->Value().nums.at(0), result ? "true" : "false");
                break;
            case Float: 
                this->eval = BoolValue(val1->Value().floats.at(0) > val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpGt::Op result %s\n",  eval.Value().booleans.at(0) ? "true" : "false");
                break;
            case Boolean: 
                throw std::invalid_argument("Cannot compare booleanas"); 
                break;
            case Datetime: 
                throw std::invalid_argument("Cannot compare datetimes"); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpGt::Value() {
    return eval.Value();
}

Type ScaOpGt::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpGt::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpLt::ScaOpLt(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpLt::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpLt::Op called \n");
    bool result;

    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw std::invalid_argument("Cannot compare strings"); 
                break;
            case Int: 
                result = val1->Value().nums.at(0) < val2->Value().nums.at(0);
                this->eval = BoolValue(result);
                ITracer::GetTracer()->Trace("ScaOpLt::Op result: %d < %d is %s\n", val1->Value().nums.at(0), val2->Value().nums.at(0), result ? "true" : "false");
                break;
            case Float: 
                this->eval = BoolValue(val1->Value().floats.at(0) < val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpLt::Op result %s\n",  eval.Value().booleans.at(0) ? "true" : "false");
                break;
            case Boolean: 
                throw std::invalid_argument("Cannot compare booleanas"); 
                break;
            case Datetime: 
                throw std::invalid_argument("Cannot compare datetimes"); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpLt::Value() {
    return eval.Value();
}

Type ScaOpLt::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpLt::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpFtoI::ScaOpFtoI(IScalar *val1) 
 : val1(val1)
{
    
}

void ScaOpFtoI::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpFtoI::Op called \n");

    if(val1->getType() != Float) {
        throw std::invalid_argument("Cannot call convert float to int without a float");
    }  else {
        int num = static_cast<int>(val1->Value().floats.at(0));
        eval = IntValue(num);
        ITracer::GetTracer()->Trace("ScaOpFtoI::Op converted %f to %d \n", val1->Value().floats.at(0), num);
    }
}

Record ScaOpFtoI::Value() {
    return eval.Value();
}

Type ScaOpFtoI::getType() {
    return Int;
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpFtoI::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    return children;
}

ScaOpComp::ScaOpComp(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpComp::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpComp::Op called \n");
    
    int comp;
    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                comp = val1->Value().strings.at(0).compare(val2->Value().strings.at(0));
                this->eval = IntValue(normalizeEval(comp));
                ITracer::GetTracer()->Trace("ScaOpComp::Op result %d\n", eval.Value().nums.at(0));
                break;
            case Int: 
                comp = val1->Value().nums.at(0) - val2->Value().nums.at(0);
                this->eval = IntValue(normalizeEval(comp));
                ITracer::GetTracer()->Trace("ScaOpComp::Op result %d\n", eval.Value().nums.at(0));
                break;
            case Float: 
                comp = static_cast<int>(100*(val1->Value().floats.at(0) - val2->Value().floats.at(0)));
                this->eval = IntValue(normalizeEval(comp));
                ITracer::GetTracer()->Trace("ScaOpComp::Op between %f and %f results in %d\n", 
                    val1->Value().floats.at(0), val2->Value().floats.at(0), eval.Value().nums.at(0));
                break;
            case Boolean: 
                comp = val1->Value().booleans.at(0) - val2->Value().booleans.at(0);
                this->eval = IntValue(normalizeEval(comp));
                ITracer::GetTracer()->Trace("ScaOpComp::Op result %d\n", eval.Value().nums.at(0));
                break;
            case Datetime: 
                comp = (int) difftime(val1->Value().datetimes.at(0), val1->Value().datetimes.at(0));
                this->eval = IntValue(normalizeEval(comp));
                ITracer::GetTracer()->Trace("ScaOpComp::Op result %d\n", eval.Value().nums.at(0)); 
                break;
            case EnumCount:
                throw std::invalid_argument("Not a real type");
                break;
        }
    }  else {
        throw std::invalid_argument("Type mismatch");
    }
}

Record ScaOpComp::Value() {
    return eval.Value();
}

Type ScaOpComp::getType() {
    return Int;
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpComp::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

int ScaOpComp::normalizeEval(int difference) {
    if(difference == 0) {
        return 0;
    } else if(difference > 0) {
        return 1;
    } else if (difference < 0) {
        return -1;
    } else {
        throw std::invalid_argument("Unreachable code");
    }
}

ScaOpAssign::ScaOpAssign(ILValue *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    eval = val1;
}

void ScaOpAssign::Op(vector<IVariable*>& params)
{
    ITracer::GetTracer()->Trace("ScaOpAssign::Op called \n");
    val1->Update(val2->Value());
}

Record ScaOpAssign::Value() {
    return eval->Value();
}

Type ScaOpAssign::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpAssign::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpBin::ScaOpBin(IScalar *val1, IntValue *val2) 
 : val1(val1), val2(val2)
{
    eval = nullptr;
}

void ScaOpBin::Op(vector<IVariable*>& params)
{
    int bucketSize = val2->Value().nums.at(0);
    switch(val1->getType()) {
        case String: 
            throw std::invalid_argument("Cannot bin strings");
            break;
        case Int: 
            eval = new IntValue(val1->Value().nums.at(0) / bucketSize);
            ITracer::GetTracer()->Trace("ScaOpBin::Op between %d and %d results in %d\n", 
                val1->Value().nums.at(0), bucketSize, eval->Value().nums.at(0));
            break;
        case Float: 
            eval = new IntValue(static_cast<int>(val1->Value().floats.at(0)) / bucketSize);
            ITracer::GetTracer()->Trace("ScaOpBin::Op between %f and %f results in %d\n", 
                val1->Value().floats.at(0), val2->Value().floats.at(0), eval->Value().floats.at(0));
            break;
        case Boolean: 
            throw std::invalid_argument("Cannot bin booleans");
            break;
        case Datetime: 
        {
            time_t valDate;
            valDate = val1->Value().datetimes.at(0);
            valDate = valDate - (valDate % bucketSize);
            eval = new DatetimeValue(valDate);
            char timeString[size("yyyy-mm-ddThh:mm:ssZ")];
            strftime(timeString, size(timeString), "%Y-%m-%d %H:%M:%S", gmtime(&valDate));
            ITracer::GetTracer()->Trace("ScaOpBin::Op result %s\n", timeString); 
            break;
        }
        case EnumCount:
            throw std::invalid_argument("Not a real type");
            break;
    }
}

Record ScaOpBin::Value() {
    return eval->Value();
}

Type ScaOpBin::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}

vector<IJob<IScalar, Record, vector<IVariable*>>*>* ScaOpBin::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}


/*

ScaOpAnd::ScaOpAnd(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

Record ScaOpAnd::Op()
{
    this->eval = new BoolValue(val1->Value().booleans.at(0) && val2->Value().booleans.at(0));
    return eval.Value();
}

Record ScaOpAnd::Value() {
    return eval.Value();
}

Type ScaOpAnd::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw std::invalid_argument("Type mismatch");
    }
}
*/