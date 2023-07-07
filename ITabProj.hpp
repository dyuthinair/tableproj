/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "ITabOp.hpp"
#pragma once

class ITabProj : public ITabOp {
    ITable virtual Op(ITable &tab1, vector<string> cols) = 0;
};