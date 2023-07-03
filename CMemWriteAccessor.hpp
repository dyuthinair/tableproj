/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/

#include "IWriteAccessor.hpp"

using namespace std;

class CMemWriteAccessor : public IWriteAccessor {
    public:
        CMemWriteAccessor();
        void setColTypes(int rows, std::vector<Type>, std::vector<std::string>);
        void pushRow(Record record);
};
