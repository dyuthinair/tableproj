#include  "JobEval.hpp"
#include "IScaOp.hpp"
#include "IRelOp.hpp"
#include <vector>

using namespace std;

template<typename IOp, typename R, typename Runtime>
R JobEval<IOp, R, Runtime>::evalTree(IJob<IOp, R, Runtime> *root,Runtime& params) {   
    traversed.clear();
    while(!todo.empty()) {
        todo.pop();
    }
    todo.push(root);
    while(!todo.empty()) {
        IJob<IOp, R, Runtime>* cur = todo.top();
        todo.pop();
        traversed.insert(cur);
        vector<IJob<IOp, R, Runtime>*>* children = cur->getChildren();
        if(children != nullptr && !children->empty()) {
            bool allChildrenTravered  = true;
            for(IJob<IOp, R, Runtime>* child : *children) {
                if(traversed.count(child) == 0) {
                    allChildrenTravered = false;
                    break;
                }
            }
            if(!allChildrenTravered) {
                todo.push(cur);
                for(IJob<IOp, R, Runtime>* child : *children) {
                    todo.push(child);
                }
            } else {
                cur->Op(params);
            }
        } else {
            cur->Op(params);
        }  
    } 
    ITracer::GetTracer()->Trace("JobEval Over\n");
    return root->Value();
}

template class JobEval<IScalar, Record, vector<IVariable*>>;
template class JobEval<IRelOp, vector<IAccessor*>*, vector<IVariable*>>;

