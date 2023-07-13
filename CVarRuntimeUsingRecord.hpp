/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include "IScaOp.hpp"

using namespace std;

class CVarRuntimeUsingRecord: public CVarRuntime {
    string name;
    Type type;
    Record* prow;
    Record returnValue;
    int col;

    public:
        CVarRuntimeUsingRecord(Type type, string name, int column);
        CVarRuntimeUsingRecord(Type type, string name, int column, string tableName);
        virtual Record Value();
        virtual vector<IJob<IScalar, Record, vector<IVariable*>>*>* getChildren() {return nullptr;};
        virtual void Op(vector<IVariable*>& params){};
        virtual void Update(Record* value);
        virtual void Combine(Record* value);
};