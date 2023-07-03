#include <vector>
#include <string>
#include "CMemTable.hpp"
#include "CMemDeserializer.hpp"

using namespace std;

void testReadCsv();

int main(int argc, char* argv[])
{
    testReadCsv();
}

void testReadCsv()
{
    string filePath = "..\\testdata\\UserNames.csv";

    CMemTable *table = new CMemTable();
    CMemDeserializer *deserializer = new CMemDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(filePath, writeAccessor);
}