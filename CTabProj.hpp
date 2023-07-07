/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "ITabProj.hpp"
#pragma once

class CTabProj : public ITabProj {
    ITable Op(ITable &tab1, vector<string> cols);
};