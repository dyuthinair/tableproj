/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CScaOp.hpp"

using namespace std;

ScaOpEq::ScaOpEq(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpEq::Op(vector<IVariable*>& params) {
    this->eval = BoolValue(val1->Value() == val2->Value());
}

Record ScaOpEq::Value() {
    return eval.Value();
}

Type ScaOpEq::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
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
                throw("Cannot add strings"); 
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
                throw("Cannot add booleanas"); 
                break;
            case EnumCount:
                throw("Not a real type");
                break;
        }
    }  else {
        throw("Type mismatch");
    }
}

Record ScaOpAdd::Value() {
    return result->Value();
}

Type ScaOpAdd::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
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
                throw("Cannot subtract strings"); 
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
                throw("Cannot subtract booleanas"); 
                break;
            case EnumCount:
                throw("Not a real type");
                break;
        }
    }  else {
        throw("Type mismatch");
    }
}

Record ScaOpSub::Value() {
    return result->Value();
}

Type ScaOpSub::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
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
                throw("Cannot compare strings"); 
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
                throw("Cannot compare booleanas"); 
                break;
            case EnumCount:
                throw("Not a real type");
                break;
        }
    }  else {
        throw("Type mismatch");
    }
}

Record ScaOpGt::Value() {
    return eval.Value();
}

Type ScaOpGt::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
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
                throw("Cannot compare strings"); 
                break;
            case Int: 
                result = val1->Value().nums.at(0) < val2->Value().nums.at(0);
                this->eval = BoolValue(result);
                ITracer::GetTracer()->Trace("ScaOpLt::Op result: %d > %d is %s\n", val1->Value().nums.at(0), val2->Value().nums.at(0), result ? "true" : "false");
                break;
            case Float: 
                this->eval = BoolValue(val1->Value().floats.at(0) < val2->Value().floats.at(0));
                ITracer::GetTracer()->Trace("ScaOpLt::Op result %s\n",  eval.Value().booleans.at(0) ? "true" : "false");
                break;
            case Boolean: 
                throw("Cannot compare booleanas"); 
                break;
            case EnumCount:
                throw("Not a real type");
                break;
        }
    }  else {
        throw("Type mismatch");
    }
}

Record ScaOpLt::Value() {
    return eval.Value();
}

Type ScaOpLt::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
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
        throw("Cannot call convert float to int without a float");
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
        throw("Type mismatch");
    }
}
*/