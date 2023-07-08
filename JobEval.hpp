#include  "IJob.hpp"
#include <stack>
#include <unordered_set>

using namespace std;

template<typename IOp, typename R>
class JobEval {
    stack<IJob<IOp, R>*> todo;
    unordered_set<IJob<IOp, R>*> traversed;
    public:
        JobEval() {};  
        R* evalTree(IJob<IOp, R> *root); 
};