#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "CMemTable.hpp"
#include "CCSVDeserializer.hpp"
#include "CCSVSerializer.hpp"
#include "CScaOp.hpp"
#include "JobEval.hpp"
#include "IRelOp.hpp"

using namespace std;

void UnitTests(int argc, char* argv[]);
void testReadCsv();
void testWriteCsv();
void biggerTestWrite();
bool TestScaOpTree();
void TestScaOpTreeWithParams();
void projectTest();
void project2Test();
//bool TestBoolScaOpTree();

int main(int argc, char* argv[])
{
    UnitTests(argc, argv);
}

void UnitTests(int argc, char* argv[])
{
    //testReadCsv();
    //testWriteCsv();
    //biggerTestWrite();
    //std::cout << std::boolalpha << TestScaOpTree();
    //std::cout << std::boolalpha << TestBoolScaOpTree();
    //TestScaOpTreeWithParams();
    //projectTest();
    project2Test();
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

bool TestScaOpTree()
{
    ScaOpAdd *addNode = new ScaOpAdd(new ScaOpAdd(new IntValue(18), new IntValue(6)), new IntValue(5));
    //addNode->Op();
    ScaOpEq *eqNode = new ScaOpEq(addNode, new IntValue(29));
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output = tree->evalTree(eqNode, params);

    return output.booleans.at(0);
}

void TestScaOpTreeWithParams()
{
    ScaOpAdd *addNode = new ScaOpAdd(new ScaOpAdd(new IntValue(18), new IntValue(6)), new CVarRef(Int, "x"));
    //addNode->Op();
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output;
    for(int i = 0; i < 10; i++) {
        params.push_back(new CVarRuntime(Int, "x", new IntValue(i)));
        output = tree->evalTree(addNode, params);
        cout << output.nums.at(0) << "\n";
        params.pop_back();
    }
}

void projectTest()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    ScaOpAdd *addNode = new ScaOpAdd(new CVarRef(Float, "Age"), new FloatValue(1));
    CMemReadAccessor readAccessor = table->getAccessor();
    vector<string> colNames;
    colNames.push_back("Age + 1");
    vector<Type> colTypes;
    colTypes.push_back(Float);
    vector<IScalar*> trees;
    trees.push_back(addNode);
    CProject *projector = new CProject(readAccessor, colNames, colTypes, trees);
    vector<IVariable*>* params = new vector<IVariable*>();
    projector->Op(*params);

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(projector->Value()));
}

void project2Test()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    ScaOpAdd *addNode = new ScaOpAdd(new CVarRef(Float, "Age"), new FloatValue(1));
    ScaOpAdd *addNode2 = new ScaOpAdd(new CVarRef(Float, "Age"), new FloatValue(2));
    CMemReadAccessor readAccessor = table->getAccessor();
    vector<string> colNames;
    colNames.push_back("Age + 1");
    colNames.push_back("Age + 2");
    vector<Type> colTypes;
    colTypes.push_back(Float);
    colTypes.push_back(Float);
    vector<IScalar*> trees;
    trees.push_back(addNode);
    trees.push_back(addNode2);
    CProject *projector = new CProject(readAccessor, colNames, colTypes, trees);
    vector<IVariable*>* params = new vector<IVariable*>();
    projector->Op(*params);

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(projector->Value()));
}

/*
bool TestBoolScaOpTree()
{
    auto flsNode = new ScaOpAnd(new BoolValue(false), new BoolValue(true));
    flsNode->Op();
    auto truNode = new ScaOpAnd(new BoolValue(true), new BoolValue(true));
    truNode->Op();
    return flsNode->Value().booleans.at(0) == false && truNode->Value().booleans.at(0) == true;
}
*/