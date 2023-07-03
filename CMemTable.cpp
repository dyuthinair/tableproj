/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemTable.hpp"

using namespace std;

CMemTable::CMemTable() {

}

CMemReadAccessor CMemTable::getAccessor() {
    CMemReadAccessor *reader = new CMemReadAccessor();
    return *reader;
}

CMemWriteAccessor CMemTable::getWriteAccessor() {
    CMemWriteAccessor *writer = new CMemWriteAccessor();
    return *writer;
}