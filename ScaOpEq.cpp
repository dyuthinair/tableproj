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

void ScaOpEq::Op() {
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

vector<IJob<IScalar, Record>*>* ScaOpEq::getChildren() {
    vector<IJob*>* children = new vector<IJob*>();
    children->push_back(val1);
    children->push_back(val2);
    return children;
}

ScaOpAdd::ScaOpAdd(IScalar *val1, IScalar *val2) 
 : val1(val1), val2(val2)
{
    
}

void ScaOpAdd::Op()
{
    if(val1->getType() == val2->getType()) {
        switch(val1->getType()) {
            case String: 
                throw("Cannot add strings"); 
                break;
            case Int: 
                this->eval = new IntValue(val1->Value().nums.at(0) + val2->Value().nums.at(0));
                break;
            case Float: 
                this->eval = new FloatValue(val1->Value().floats.at(0) + val2->Value().floats.at(0));
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
    return eval->Value();
}

Type ScaOpAdd::getType() {
    if(val1->getType() == val2->getType()) {
        return val1->getType();
    } else {
        throw("Type mismatch");
    }
}

vector<IJob<IScalar, Record>*>* ScaOpAdd::getChildren() {
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
        throw("Type mismatch");
    }
}
*/