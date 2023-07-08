#include  "JobEval.hpp"
#include "IScaOp.hpp"
#include <vector>

using namespace std;

template<typename IOp, typename R>
R JobEval<IOp, R>::evalTree(IJob<IOp, R> *root) {            
    todo.push(root);
    while(!todo.empty()) {
        IJob<IOp, R>* cur = todo.top();
        todo.pop();
        traversed.insert(cur);
        vector<IJob<IOp, R>*>* children = cur->getChildren();
        if(!children->empty()) {
            bool allChildrenTravered  = true;
            for(IJob<IOp, R>* child : *children) {
                if(traversed.count(child) == 0) {
                    allChildrenTravered = false;
                    break;
                }
            }
            if(!allChildrenTravered)
            {
                todo.push(cur);
                for(IJob<IOp, R>* child : *children) {
                    todo.push(child);
                }
            } else {
                cur->Op();
            }
        }  
    } 
    return root->Value();
}

template class JobEval<IScalar, Record>;
