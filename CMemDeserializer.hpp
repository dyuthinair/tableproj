/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "IAccessor.hpp"
#include "IWriteAccessor.hpp"
#include <string>
#include <unordered_map>

using namespace std;

class CMemDeserializer {

    void initMap();
    void printTable(vector<Record*> *database);

    public:
        std::unordered_map<std::string, Type> enumMap;
        CMemDeserializer();
        void deserialize(string path, IWriteAccessor &tableWriter);
};