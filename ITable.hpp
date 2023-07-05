/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemWriteAccessor.hpp"
#include "CMemReadAccessor.hpp"
#pragma once

class ITable {
    virtual IAccessor& getAccessor() = 0;
    virtual IWriteAccessor& getWriteAccessor() = 0;
};
