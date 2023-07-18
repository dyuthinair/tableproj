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
        virtual void Update(Record* value) = 0;
        virtual void Combine(Record* value) = 0;
};

class IScaOp: public IScalar {
    public:

};

class CConstVal: public IScalar, public Record {

    Type type;

    public:
        virtual Type getType() = 0;
        virtual Record Value() = 0;
        virtual void Op(vector<IVariable*>& params) {};
        virtual void update(Record* value) {};
};

class CVarRef: public IVariable {
    string name;
    Type type;
    Record* value;
    int index;

    public:
        CVarRef(Type type, string name);
        CVarRef(Type type, string name, string tableName);

        // Implement IVariable
        virtual string Name();
        virtual Type getType();
        virtual Record Value();
        virtual void Update(Record* value);
        virtual void Combine(Record* value);

        // Implement IScalar
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {return nullptr;};
};

class CVarRuntime: public IVariable {
    string name;
    Type type;
    Record* value;

    public:
        CVarRuntime(Type type, string name, Record* value);
        CVarRuntime(Type type, string name, Record* value, string tableName);
        
         // Implement IVariable
        virtual string Name();
        virtual Type getType();
        virtual Record Value();
        virtual void Update(Record* value);
        virtual void Combine(Record* value);

        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {return nullptr;};
        virtual void Op(vector<IVariable*>& params){};
};

class IntValue: public CConstVal
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
        virtual void update(int value) {
            nums.pop_back();
            nums.push_back(value);
        }
};

class StringValue: public CConstVal
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
        virtual void update(string value) {
            strings.pop_back();
            strings.push_back(value);
        }
};

class FloatValue: public CConstVal
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
        virtual void update(float value) {
            floats.pop_back();
            floats.push_back(value);
        }
};

class BoolValue: public CConstVal
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
        virtual void update(bool value) {
            booleans.pop_back();
            booleans.push_back(value);
        }
};



