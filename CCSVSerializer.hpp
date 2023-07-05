/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "CMemReadAccessor.hpp"
#pragma once

class CCSVSerializer {

    public:         
        CCSVSerializer();
        void serialize(string path, IAccessor &tableReader);
};