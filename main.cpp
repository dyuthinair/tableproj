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
#include <memory>

using namespace std;

void UnitTests(int argc, char* argv[]);
void testReadCsv();
void testWriteCsv();
void biggerTestWrite();
bool TestScaOpTree();
void TestScaOpTreeWithParams();
void projectTest();
void project2Test();
void subTest();
void selectTest();
bool TestGt();
void ftoiTest();
void selectThenProject();
void joinTest();
void sortTest();
void TestComp();
void mergeJoinTest();
void mergeJoinTestLarge();
void countTest();
void sumTest();

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
    //TestScaOpTreeWithParams();
    //projectTest();
    //project2Test();
    //subTest();
    //selectTest();
    //std::cout << std::boolalpha << TestGt();
    //ftoiTest();
    //selectThenProject();
    //joinTest();
    //sortTest();
    //TestComp();
    //mergeJoinTest();
    //mergeJoinTestLarge(); //alter deserialize to fix
    //countTest();
    sumTest();

    //std::cout << std::boolalpha << TestBoolScaOpTree();
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
    ScaOpEq *eqNode = new ScaOpEq(addNode, new IntValue(29));
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output = tree->evalTree(eqNode, params);

    return output.booleans.at(0);
}

void TestScaOpTreeWithParams()
{
    ScaOpAdd *addNode = new ScaOpAdd(new ScaOpAdd(new IntValue(18), new IntValue(6)), new CVarRef(Int, "x"));
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output;
    for(unsigned int i = 0; i < 10; i++) {
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
    CProject *projector = new CProject(*new AccessorRelOp(readAccessor), colNames, colTypes, trees, false);
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
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
    CVarRef *nameNode = new CVarRef(String, "Name");
    CMemReadAccessor readAccessor = table->getAccessor();
    vector<string> colNames;
    colNames.push_back("Name");
    colNames.push_back("Age + 1");
    colNames.push_back("Age + 2");
    vector<Type> colTypes;
    colTypes.push_back(String);
    colTypes.push_back(Float);
    colTypes.push_back(Float);
    vector<IScalar*> trees;
    trees.push_back(nameNode);
    trees.push_back(addNode);
    trees.push_back(addNode2);
    CProject *projector = new CProject(*new AccessorRelOp(readAccessor), colNames, colTypes, trees, false);
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
}

void subTest()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output_birthyear.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    ScaOpSub *subNode = new ScaOpSub(new FloatValue(2023), new CVarRef(Float, "Age"));
    CVarRef *nameNode = new CVarRef(String, "Name");
    CMemReadAccessor readAccessor = table->getAccessor();
    vector<string> colNames;
    colNames.push_back("Name");
    colNames.push_back("Birthyear");
    vector<Type> colTypes;
    colTypes.push_back(String);
    colTypes.push_back(Float);
    vector<IScalar*> trees;
    trees.push_back(nameNode);
    trees.push_back(subNode);
    CProject *projector = new CProject(*new AccessorRelOp(readAccessor), colNames, colTypes, trees, false);
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
}


void selectTest()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output_donachie.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    ScaOpGt *gtNode = new ScaOpGt(new CVarRef(Float, "Age"), new FloatValue(25));
    CMemReadAccessor readAccessor = table->getAccessor();
    CSelect *selecter = new CSelect(*new AccessorRelOp(readAccessor), gtNode);
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(selecter, params)));
}

bool TestGt()
{
    ScaOpAdd *addNode = new ScaOpAdd(new ScaOpAdd(new IntValue(19), new IntValue(6)), new IntValue(5));
    //addNode->Op();
    ScaOpGt *gtNode = new ScaOpGt(addNode, new IntValue(29));
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output = tree->evalTree(gtNode, params);

    return output.booleans.at(0);
}

void ftoiTest()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output_birthyear.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    ScaOpSub *subNode = new ScaOpSub(new FloatValue(2023), new CVarRef(Float, "Age"));
    ScaOpFtoI *ftoi = new ScaOpFtoI(subNode);
    CVarRef *nameNode = new CVarRef(String, "Name");
    CMemReadAccessor readAccessor = table->getAccessor();
    vector<string> colNames;
    colNames.push_back("Name");
    colNames.push_back("Birthyear");
    vector<Type> colTypes;
    colTypes.push_back(String);
    colTypes.push_back(Int);
    vector<IScalar*> trees;
    trees.push_back(nameNode);
    trees.push_back(ftoi);
    CProject *projector = new CProject(*new AccessorRelOp(readAccessor), colNames, colTypes, trees, false);
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
}

void selectThenProject() {
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output_birth_1900s.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    IScaOp *gtNode = new ScaOpEq(new ScaOpFtoI(new CVarRef(Float, "Age")), new IntValue(24));
    CMemReadAccessor readAccessor = table->getAccessor();
    AccessorRelOp* accessorRelOp = new AccessorRelOp(readAccessor);
    CSelect *selecter = new CSelect(*accessorRelOp, gtNode);

    ScaOpSub *subNode = new ScaOpSub(new FloatValue(2007), new CVarRef(Float, "Age"));
    ScaOpFtoI *ftoi = new ScaOpFtoI(subNode);
    CVarRef *nameNode = new CVarRef(String, "Name");
    vector<string> colNames;
    colNames.push_back("Name");
    colNames.push_back("Birthyear");
    vector<Type> colTypes;
    colTypes.push_back(String);
    colTypes.push_back(Int);
    vector<IScalar*> trees;
    trees.push_back(nameNode);
    trees.push_back(ftoi);
    CProject *projector = new CProject(*selecter, colNames, colTypes, trees, false);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
}


void joinTest()
{
    string readFilePath1 = "..\\testdata\\oscar_age_female.csv";
    string readFilePath2 = "..\\testdata\\oscar_age_male.csv";
    string writeFilePath = "..\\testdata\\oscars_per_year.csv";

    unique_ptr<CMemTable> tableW(new CMemTable("Women"));
    CCSVDeserializer *deserializerW = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorW = tableW->getWriteAccessor();
    deserializerW->deserialize(readFilePath1, writeAccessorW);

    unique_ptr<CMemTable> tableM(new CMemTable("Men"));
    CCSVDeserializer *deserializerM = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorM = tableM->getWriteAccessor();
    deserializerM->deserialize(readFilePath2, writeAccessorM);

    ScaOpEq *eqNode = new ScaOpEq(new CVarRef(Int, "Year", "Women"), new CVarRef(Int, "Year", "Men"));
    CMemReadAccessor readAccessorW = tableW->getAccessor();
    CMemReadAccessor readAccessorM = tableM->getAccessor();
    AccessorRelOp* accessorRelOpW = new AccessorRelOp(readAccessorW);
    AccessorRelOp* accessorRelOpM = new AccessorRelOp(readAccessorM);

    vector<IVariable*> params;
    CInnerJoin* joiner = new CInnerJoin(*accessorRelOpW, *accessorRelOpM, eqNode);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(joiner, params)));
}

void sortTest()
{
    string readFilePath = "..\\testdata\\mlb_players.csv";
    string writeFilePath = "..\\testdata\\baseball_output_sorted.csv";

    CMemTable *table = new CMemTable();
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    CMemReadAccessor readAccessor = table->getAccessor();
    AccessorRelOp* accessorRelOp = new AccessorRelOp(readAccessor);
    vector<IVariable*> params;

    CSortOp* sorter = new CSortOp(*accessorRelOp, "Name");
    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(sorter, params)));
}

void TestComp()
{
    ScaOpComp *addNode1 = new ScaOpComp(new IntValue(6), new IntValue(7));
    //addNode->Op();
    JobEval<IScalar, Record, vector<IVariable*>>* tree = new JobEval<IScalar, Record, vector<IVariable*>>();
    vector<IVariable*> params;
    Record output = tree->evalTree(addNode1, params);

    cout << output.nums.at(0) << "\n";

    ScaOpComp *addNode2 = new ScaOpComp(new IntValue(6), new IntValue(6));
    //addNode->Op();
    Record output2 = tree->evalTree(addNode2, params);

    cout << output2.nums.at(0) << "\n";

    ScaOpComp *addNode3 = new ScaOpComp(new IntValue(6), new IntValue(5));
    //addNode->Op();
    Record output3 = tree->evalTree(addNode3, params);

    cout << output3.nums.at(0) << "\n";
}

void mergeJoinTest()
{
    string readFilePath1 = "..\\testdata\\oscar_age_female.csv";
    string readFilePath2 = "..\\testdata\\oscar_age_male.csv";
    string writeFilePath = "..\\testdata\\oscars_per_year.csv";

    unique_ptr<CMemTable> tableW(new CMemTable("Women"));
    CCSVDeserializer *deserializerW = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorW = tableW->getWriteAccessor();
    deserializerW->deserialize(readFilePath1, writeAccessorW);

    unique_ptr<CMemTable> tableM(new CMemTable("Men"));
    CCSVDeserializer *deserializerM = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorM = tableM->getWriteAccessor();
    deserializerM->deserialize(readFilePath2, writeAccessorM);

    ScaOpComp *compNode = new ScaOpComp(new CVarRef(String, "Movie", "Women"), new CVarRef(String, "Movie", "Men"));
    CMemReadAccessor readAccessorW = tableW->getAccessor();
    CMemReadAccessor readAccessorM = tableM->getAccessor();
    AccessorRelOp* accessorRelOpW = new AccessorRelOp(readAccessorW);
    AccessorRelOp* accessorRelOpM = new AccessorRelOp(readAccessorM);

    vector<IVariable*> params;

    CSortOp* sorterW = new CSortOp(*accessorRelOpW, "Movie");
    CSortOp* sorterM = new CSortOp(*accessorRelOpM, "Movie");

    CMergeJoin* joiner = new CMergeJoin(*sorterW, *sorterM, compNode);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(joiner, params)));
}


void mergeJoinTestLarge()
{
    string readFilePath1 = "..\\testdata\\annual-enterprise-survey-2021-financial-year-provisional-csv.csv";
    string readFilePath2 = "..\\testdata\\annual-enterprise-survey-2021-financial-year-provisional-size-bands-csv.csv";
    string writeFilePath = "..\\testdata\\info_by_industry.csv";

    unique_ptr<CMemTable> tableS(new CMemTable("Without Size Bands"));
    CCSVDeserializer *deserializerS = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorS = tableS->getWriteAccessor();
    deserializerS->deserialize(readFilePath1, writeAccessorS);

    unique_ptr<CMemTable> tableN(new CMemTable("Size Bands"));
    CCSVDeserializer *deserializerN = new CCSVDeserializer();
    CMemWriteAccessor writeAccessorN = tableN->getWriteAccessor();
    deserializerN->deserialize(readFilePath2, writeAccessorN);

    ScaOpComp *compNode = new ScaOpComp(new CVarRef(String, "Without Size Bands", "Industry_name_NZSIOC"), new CVarRef(String, "Size Bands", "industry_code_ANZSIC"));
    CMemReadAccessor readAccessorS = tableS->getAccessor();
    CMemReadAccessor readAccessorN = tableN->getAccessor();
    AccessorRelOp* accessorRelOpS = new AccessorRelOp(readAccessorS);
    AccessorRelOp* accessorRelOpN = new AccessorRelOp(readAccessorN);

    vector<IVariable*> params;

    CSortOp* sorterS = new CSortOp(*accessorRelOpS, "Without Size Bands");
    CSortOp* sorterN = new CSortOp(*accessorRelOpN, "Size Bands");

    CMergeJoin* joiner = new CMergeJoin(*sorterS, *sorterN, compNode);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();

    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(joiner, params)));
}

void countTest() {
    string readFilePath = "..\\testdata\\annual-enterprise-survey-2021-financial-year-provisional-csv.csv";
    string writeFilePath = "..\\testdata\\info_by_industry.csv";

    unique_ptr<CMemTable> table(new CMemTable("Without Size Bands"));
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    LValue *count = new LValue(Int, "Count", new IntValue(0));
    ScaOpAdd *adder = new ScaOpAdd(count, new IntValue(1));
    ScaOpAssign *assigner = new ScaOpAssign(count, adder);

    CMemReadAccessor readAccessor = table->getAccessor();
    AccessorRelOp* accessorRelOp = new AccessorRelOp(readAccessor);

    vector<string> colNames;
    colNames.push_back("Count");
    vector<Type> colTypes;
    colTypes.push_back(Int);
    vector<IScalar*> trees;
    trees.push_back(assigner);

    CProject *projector = new CProject(*accessorRelOp, colNames, colTypes, trees, true);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
}

void sumTest() {
    string readFilePath = "..\\testdata\\annual-enterprise-survey-2021-financial-year-provisional-csv.csv";
    string writeFilePath = "..\\testdata\\info_by_industry.csv";

    unique_ptr<CMemTable> table(new CMemTable("Without Size Bands"));
    CCSVDeserializer *deserializer = new CCSVDeserializer();
    CMemWriteAccessor writeAccessor = table->getWriteAccessor();
    deserializer->deserialize(readFilePath, writeAccessor);

    LValue *count = new LValue(Int, "Value", new IntValue(0));
    CVarRef *val = new CVarRef(Int, "Value"); 
    ScaOpAdd *adder = new ScaOpAdd(count, val);
    ScaOpAssign *assigner = new ScaOpAssign(count, adder);

    CMemReadAccessor readAccessor = table->getAccessor();
    AccessorRelOp* accessorRelOp = new AccessorRelOp(readAccessor);

    vector<string> colNames;
    colNames.push_back("Sum");
    vector<Type> colTypes;
    colTypes.push_back(Int);
    vector<IScalar*> trees;
    trees.push_back(assigner);

    CProject *projector = new CProject(*accessorRelOp, colNames, colTypes, trees, true);

    JobEval<IRelOp, IAccessor*, vector<IVariable*>>* tree = new JobEval<IRelOp, IAccessor*, vector<IVariable*>>();
    vector<IVariable*> params;
    CCSVSerializer *serializer = new CCSVSerializer();
    serializer->serialize(writeFilePath, *(tree->evalTree(projector, params)));
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