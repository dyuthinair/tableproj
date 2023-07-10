/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once
#include "IAccessor.hpp"
#include "ITable.hpp"
#include "JobEval.hpp"
#include "IScaOp.hpp"

class IRelOp : public IJob<IRelOp, IAccessor*, vector<IVariable*>> {
};

class IProject : public IRelOp {
    public: 
        IProject() {};
        IProject(IAccessor& table, vector<string> colNames, vector<Type> colTypes, vector<IScalar*> trees){};
};

class CProject : public IProject {

    IAccessor& inputAccessor;
    vector<string> colNames;
    vector<Type> colTypes;
    vector<IScalar*> trees;
    IAccessor* outputAccessor;

    public:
        CProject(IAccessor& inputAccessor, vector<string> colNames, vector<Type> colTypes, vector<IScalar*> trees);
        virtual vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* getChildren() {return nullptr;};
        virtual void Op(vector<IVariable*>& params);
        virtual IAccessor* Value();
};