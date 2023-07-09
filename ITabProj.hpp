/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once
#include "ITabOp.hpp"

class ITabProj : public ITabOp {
    ITable virtual Op(ITable &tab1, vector<string> cols) = 0;
};