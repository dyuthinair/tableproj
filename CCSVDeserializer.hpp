/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IAccessor.hpp"
#include "CMemWriteAccessor.hpp"
#include <string>
#include <unordered_map>
#pragma once

using namespace std;

class CCSVDeserializer {

    void initMap();
    void insert (Type type, Record* prow, string value);

    public:
        CCSVDeserializer();
        void deserialize(string path, IWriteAccessor &tableWriter);
};