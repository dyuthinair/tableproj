/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "ITable.hpp"

using namespace std;

class CMemTable : public ITable {
    public:
        CMemTable();
        CMemReadAccessor getAccessor();
        CMemWriteAccessor getWriteAccessor();
};