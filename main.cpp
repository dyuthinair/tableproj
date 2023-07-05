#include <vector>
#include <string>
#include <fstream>
#include "CMemTable.hpp"
#include "CCSVDeserializer.hpp"
#include "CCSVSerializer.hpp"

using namespace std;

void testReadCsv();
void testWriteCsv();
void biggerTestWrite();

int main(int argc, char* argv[])
{
    //testReadCsv();
    //testWriteCsv();
    biggerTestWrite();
}

void testReadCsv()
{
    string filePath = "..\\testdata\\UserNames.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(filePath, writeAccessor);
}

void testWriteCsv()
{
    string readFilePath = "..\\testdata\\UserNames.csv";
    string writeFilePath = "..\\testdata\\Output.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, table->getAccessor());
}

void biggerTestWrite()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, table->getAccessor());
}