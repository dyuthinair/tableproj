#include  "IJob.hpp"
#include <stack>
#include <unordered_set>

using namespace std;

template<typename IOp, typename R>
class JobEval {
    stack<IJob*> todo;
    unordered_set<IJob*> traversed;
    public:
        R* evalTree(IJob<IOp, R> *root) {            
            todo.push(root);
            while(!todo.empty()) {
                IJob* cur;
                cur = todo.pop();
                traversed.insert(cur);
                bool childrenDone = true;
                vector<IJob<IOp, R>*>* children = cur->getChildren();
                if(!children->empty()) {
                    bool allChildrenTravered  = true;
                    for(Ijob* child : children) {
                        if(traversed.count(child) == 0) {
                            allChildrenTravered = false;
                            break;
                        }
                    }
                    if (!allChildrenTravered)
                    {
                        todo.push(cur);
                        for(Ijob* child : children) {
                            todo.push(child);
                        }
                    }                  
                    else {
                        cur.op();
                    }
                }  
            } 
            return root.Value();
        }
};