/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemWriteAccessor.hpp"
#include "CMemReadAccessor.hpp"

using namespace std;

class ITable {
    CMemReadAccessor virtual getAccessor() = 0;
    CMemWriteAccessor virtual getWriteAccessor() = 0;
};
