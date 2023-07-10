/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include "IAccessor.hpp"
#include "IJob.hpp"
using namespace std;

class IVariable;

class IScalar : public IJob<IScalar, Record, vector<IVariable*>>{
    public:
        virtual Type getType() = 0;
        virtual Record Value() = 0;
        virtual void Op(vector<IVariable*> &variables) = 0;
};

class IVariable:public IScalar {
    public:
        virtual string Name() = 0;
        virtual Type getType() = 0;
        virtual Record Value() = 0;
};

class IScaOp: public IScalar {
    public:

};

class CConstVal: public IScalar {

    Type type;

    public:
        virtual Type getType() = 0;
        virtual Record Value() = 0;
        virtual void Op(vector<IVariable*>& params) {};
};

class CVarRef: public IVariable {
    string name;
    Type type;
    Record* value;

    public:
        CVarRef(Type type, string name);
        string Name();
        Type getType();
        Record Value();
        void Op(vector<IVariable*>& params);
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {return nullptr;};
};

class CVarRuntime: public IVariable {
    string name;
    Type type;
    Record* value;

    public:
        CVarRuntime(Type type, string name, Record* value);
        string Name();
        Type getType();
        Record Value();
        void update(Record* value);
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {return nullptr;};
        virtual void Op(vector<IVariable*>& params){};
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
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {
            return nullptr;
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
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {
            return nullptr;
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
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {
            return nullptr;
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
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {
            return nullptr;
        }
};

