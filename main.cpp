#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "CMemTable.hpp"
#include "CCSVDeserializer.hpp"
#include "CCSVSerializer.hpp"
#include "IScaOp.hpp"
#include "CScaOp.hpp"

using namespace std;

//void testReadCsv();
//void testWriteCsv();
//void biggerTestWrite();
bool TestScaOpTree();
//bool TestBoolScaOpTree();

int main(int argc, char* argv[])
{
    //testReadCsv();
    //testWriteCsv();
    //biggerTestWrite();
    std::cout << std::boolalpha << TestScaOpTree();
    //std::cout << std::boolalpha << TestBoolScaOpTree();
}

/*
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
*/
bool TestScaOpTree()
{
    auto addNode = new ScaOpAdd(new IntValue(18), new IntValue(6));
    //addNode->Op();
    auto tree = new ScaOpEq(addNode, new IntValue(2));
    
    return tree->Value().booleans.at(0);
}

/*
bool TestBoolScaOpTree()
{
    auto flsNode = new ScaOpAnd(new BoolValue(false), new BoolValue(true));
    flsNode->Op();
    auto truNode = new ScaOpAnd(new BoolValue(true), new BoolValue(true));
    truNode->Op();
    return flsNode->Value().booleans.at(0) == false && truNode->Value().booleans.at(0) == true;
}*/