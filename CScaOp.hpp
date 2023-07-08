/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"
#pragma once

using namespace std;

class CScaOp: public IScaOp {
    //virtual Record op(std::vector<IVariable>& evalParams) = 0;
    virtual void Op() = 0;
};

class ScaOpEq: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;

    public:
        ScaOpEq(IScalar *val1, IScalar *val2);
        //Record Op(std::vector<IVariable>& evalParams);
        void Op();
        Record* Value();
        Type getType();
        vector<IJob<IScalar, Record>*>* getChildren();
};

class ScaOpAdd: public CScaOp
{
    IScalar *eval;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpAdd(IScalar *val1, IScalar *val2);
        void Op();
        Record* Value();
        Type getType();
        vector<IJob<IScalar, Record>*>* getChildren();
};

/*
class ScaOpAnd: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpAnd(IScalar *val1, IScalar *val2);
        Record Op();
        Record Value();
        Type getType();
};*/








