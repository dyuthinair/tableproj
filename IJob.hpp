/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include <vector>

using namespace std;

template<typename IOp, typename R, typename RuntimeVariables>
class IJob {
    public:
        virtual vector<IJob<IOp, R, RuntimeVariables>*>* getChildren() = 0;
        virtual R Value() = 0;
        virtual void Op(RuntimeVariables &variables) = 0;
};

