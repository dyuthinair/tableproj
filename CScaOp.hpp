/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IScaOp.hpp"
#pragma once

class CScaOp: public IScaOp {
    //virtual Record op(std::vector<IVariable>& evalParams) = 0;
    virtual Record Op() = 0;
    Record rootEval();
};

class ScaOpEq: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;

    public:
        ScaOpEq(IScalar *val1, IScalar *val2);
        //Record Op(std::vector<IVariable>& evalParams);
        Record Op();
        Record Value();
        Type getType();
};

class ScaOpAdd: public CScaOp
{
    IScalar *eval;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpAdd(IScalar *val1, IScalar *val2);
        Record Op();
        Record Value();
        Type getType();
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
};
/**/








