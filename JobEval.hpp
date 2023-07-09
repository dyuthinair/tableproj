#pragma once

#include  "IJob.hpp"
#include <stack>
#include <unordered_set>

using namespace std;

template<typename IOp, typename R, typename Runtime>
class JobEval {
    stack<IJob<IOp, R, Runtime>*> todo;
    unordered_set<IJob<IOp, R, Runtime>*> traversed;
    public:
        JobEval() {};  
        R evalTree(IJob<IOp, R, Runtime> *root, Runtime& params); 
};