/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include "CMemWriteAccessor.hpp"
#include "CMemReadAccessor.hpp"


class ITable {
    virtual IAccessor& getAccessor() = 0;
    virtual IWriteAccessor& getWriteAccessor() = 0;
};
