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

// IJob<IRelOp, IAccessor*, std::vector<IVariable*> >
class IRelOp : public IJob<IRelOp, IAccessor*, vector<IVariable*>> {
};

class IAccessorRelOp : public IRelOp {
};

class IProject : public IRelOp {
};

class ISelect : public IRelOp {
};

class AccessorRelOp: public IAccessorRelOp
{
    IAccessor& table;
    public:
        AccessorRelOp(IAccessor& table);
        virtual vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual IAccessor* Value();
};

class CProject : public IProject {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, IAccessor*, std::vector<IVariable*>>*> childJobs;
    vector<string> colNames;
    vector<Type> colTypes;
    vector<IScalar*> trees;
    IAccessor* outputAccessor;

    public:
        CProject(IRelOp& child, vector<string> colNames, vector<Type> colTypes, vector<IScalar*> trees);
        virtual vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual IAccessor* Value();
};

class CSelect : public ISelect {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, IAccessor*, std::vector<IVariable*>>*> childJobs;
    IScalar* tree;
    IAccessor* outputAccessor;

    public:
        CSelect(IRelOp& child, IScalar* tree);
        virtual vector<IJob<IRelOp, IAccessor*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual IAccessor* Value();
};
