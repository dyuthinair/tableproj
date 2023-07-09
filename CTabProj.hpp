/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#pragma once

#include "ITabProj.hpp"


class CTabProj : public ITabProj {
    ITable Op(ITable &tab1, vector<string> cols);
};