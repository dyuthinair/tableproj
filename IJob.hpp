/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include <vector>
#pragma once

using namespace std;

template<typename IOp, typename R>
class IJob {
    public:
        virtual vector<IJob<IOp, R>*>* getChildren() = 0;
        virtual R Value() = 0;
        virtual void Op() = 0;
};

class IOp {

};

class R {

};