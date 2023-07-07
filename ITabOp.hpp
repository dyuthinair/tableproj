/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "ITable.hpp"
#include "IScaOp.hpp"
#pragma once

class ITabOp {
    ITable virtual Op(ITable tab1, ITable tab2, string col) = 0;
    ITable virtual Op(ITable tab1, IScaOp op);
    ITable virtual Op(ITable tab1, vector<string> cols);
};