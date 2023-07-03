/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IAccessor.hpp"

class CMemReadAccessor : public IAccessor {
    public:
        CMemReadAccessor();
        int getCols();
        Type getType();
};
