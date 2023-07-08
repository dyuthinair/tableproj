/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IAccessor.hpp"
#include "IJob.hpp"
#pragma once



class IScalar : public IJob<IScalar,Record>{
    public:
        virtual Type getType() = 0;
        virtual Record Value() = 0;
        virtual void Op() = 0;
        
};

class IVariable:public IScalar {
    public:
        virtual string Name() = 0;
        virtual Type getType() = 0;
        virtual Record Value() = 0;
};

class IScaOp: public IScalar, public IOp {
    public:
        //virtual Record op(IScalar& param1, IScalar& param2, std::vector<IVariable>& evalParams) = 0;
        //virtual Record op(IScalar& param1, std::vector<IVariable>& evalParams) = 0;
};

class CConstVal: public IScalar, public R {

    Type type;

    public:
        virtual Type getType() = 0;
        virtual Record Value() = 0;
        virtual void Op() {};
};

class CVarVal: public IVariable {
    string name;
    Type type;
    Record value;

    public:
        CVarVal(string name, Type type, Record val);
        string Name();
        Type getType();
        Record Value();
        
};

class IntValue: public Record, public CConstVal
{
    public:
        IntValue(){};
        IntValue(int value)
        {
            nums.push_back(value);
        }
        virtual Record Value()
        {
            return *this;
        }
        virtual Type getType() {
            return Int;
        }
        virtual vector<IJob<IScalar, Record>*>* getChildren() {
            vector<IJob<IScalar, Record>*>* none = new vector<IJob<IScalar, Record>*>;
            return none;
        }
};

class StringValue: public Record, public CConstVal
{
    public:
        StringValue(){};
        StringValue(string value)
        {
            strings.push_back(value);
        }
        virtual Record Value()
        {
            return *this;
        }
        virtual Type getType() {
            return String;
        }
        virtual vector<IJob<IScalar, Record>*>* getChildren() {
            vector<IJob<IScalar, Record>*>* none = new vector<IJob<IScalar, Record>*>;
            return none;
        }
};

class FloatValue: public Record, public CConstVal
{
    public:
        FloatValue(){};
        FloatValue(float value)
        {
            floats.push_back(value);
        }
        virtual Record Value()
        {
            return *this;
        }
        virtual Type getType() {
            return Float;
        }
        virtual vector<IJob<IScalar, Record>*>* getChildren() {
            vector<IJob<IScalar, Record>*>* none = new vector<IJob<IScalar, Record>*>;
            return none;
        }
};

class BoolValue: public Record, public CConstVal
{
    public:
        BoolValue(){};
        BoolValue(bool value)
        {
            booleans.push_back(value);
        }
        virtual Record Value()
        {
            return *this;
        }
        virtual Type getType() {
            return Boolean;
        }
        virtual vector<IJob<IScalar, Record>*>* getChildren() {
            vector<IJob<IScalar, Record>*>* none = new vector<IJob<IScalar, Record>*>;
            return none;
        }
};

