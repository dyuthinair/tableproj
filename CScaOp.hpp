/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once
#include "IScaOp.hpp"

using namespace std;

class CScaOp: public IScaOp {
    virtual void Op(vector<IVariable*>& params) = 0;
    virtual int Comp(IScalar& rhs) {throw std::invalid_argument("Should never be called");};
};

class ScaOpEq: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;

    public:
        ScaOpEq(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpAdd: public CScaOp
{
    IScalar *result;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpAdd(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpSub: public CScaOp
{
    IScalar *result;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpSub(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpGt: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpGt(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpLt: public CScaOp
{
    BoolValue eval;
    IScalar *val1;
    IScalar *val2;
    
    public:
        ScaOpLt(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpFtoI: public CScaOp
{
    IntValue eval;
    IScalar *val1;
    
    public:
        ScaOpFtoI(IScalar *val1);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpComp: public CScaOp
{
    IntValue eval;
    IScalar *val1;
    IScalar *val2;

    int normalizeEval(int difference);
    
    public:
        ScaOpComp(IScalar *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpAssign: public CScaOp
{
    ILValue *eval;
    ILValue *val1;
    IScalar *val2;

    public:
        ScaOpAssign(ILValue *val1, IScalar *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
};

class ScaOpBin: public CScaOp
{
    IScalar *eval;
    IScalar *val1;
    IntValue *val2;

    public:
        ScaOpBin(IScalar *val1, IntValue *val2);
        void Op(vector<IVariable*>& params);
        Record Value();
        Type getType();
        vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren();
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








