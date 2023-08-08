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
#include "CVarRuntimeUsingRecord.hpp"

class IRelOp : public IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>> {
};

class IAccessorRelOp : public IRelOp {
};

class IProject : public IRelOp {
};

class ISelect : public IRelOp {
};

class IJoin : public IRelOp {
};

class AccessorRelOp: public IAccessorRelOp {
    vector<IAccessor*>* producedAccessors;
    public:
        AccessorRelOp(IAccessor* table);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CProject : public IProject {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    vector<string> colNames;
    vector<Type> colTypes;
    vector<IScalar*> trees;
    vector<IAccessor*>* producedAccessors;
    bool projectAgg;

    public:
        CProject(IRelOp& child, vector<string> colNames, vector<Type> colTypes, vector<IScalar*> trees, bool projectAgg);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CSelect : public ISelect {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    IScalar* tree;
    vector<IAccessor*>* producedAccessors;

    public:
        CSelect(IRelOp& child, IScalar* tree);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CInnerJoin : public IJoin {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    IScalar* tree;
    vector<IAccessor*>* producedAccessors;

    void CollectMetadata(IAccessor& accessor, vector<CVarRuntimeUsingRecord*>& runtimeParams, vector<string>& names, vector<Type>& types);

    public:
        CInnerJoin(IRelOp& child1, IRelOp& child2, IScalar* tree);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CSortOp : public IRelOp {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    string colName;
    vector<IAccessor*>* producedAccessors;

    public:
        CSortOp(IRelOp& child1, string colName);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CMergeJoin : public IJoin {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    IScalar* tree;
    JobEval<IScalar, Record, vector<IVariable*>>* evaluator;
    vector<IAccessor*>* producedAccessors;

    void CollectMetadata(IAccessor& accessor, vector<CVarRuntimeUsingRecord*>& runtimeParams, vector<string>& names, vector<Type>& types);
    int EvalCurrentRow(bool updateLeft, bool updateRight, int leftcols, Record* left, Record* right, vector<CVarRuntimeUsingRecord*>& runtimeParams);
    void ProduceRecord(Record* leftRecord, Record* rightRecord, IWriteAccessor& writeAccessor);
    void HandleDuplicates(Record* leftRecord, vector<Record*>& duplicates, int cols, IWriteAccessor& writeAccessor, vector<CVarRuntimeUsingRecord*>& runtimeParams);

    public:
        CMergeJoin(IRelOp& child1, IRelOp& child2, IScalar* tree);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

class CMultiGroupBy : public IJoin {
    vector<IRelOp*> children;
    vector<IJob<IRelOp, vector<IAccessor*>*, std::vector<IVariable*>>*> childJobs;
    IScalar* tree;
    JobEval<IScalar, Record, vector<IVariable*>>* evaluator;
    vector<IAccessor*>* producedAccessors;

    public:
        CMultiGroupBy(vector<IRelOp&>* hashAccessors);
        virtual vector<IJob<IRelOp, vector<IAccessor*>*, vector<IVariable*>>*>* getChildren();
        virtual void Op(vector<IVariable*>& params);
        virtual vector<IAccessor*>* Value();
};

