/*************************************************/
/*   (C) 2023 Dyuthi Nair                        */
/*                                               */
/*                                               */
/*************************************************/
#include "SortedVector.hpp"
#include "IScaOp.hpp"


using namespace std;

SortedVector::SortedVector(IAccessor& inputStream, string colName, bool ascending)
    : input(inputStream)
 {
    ITracer::GetTracer()->Trace("SortedVector Constructor Called\n");

    this->colName = colName;
    this->ascending = ascending;

    vector<int> indices (EnumCount, 0);
    for(unsigned int i = 0; i < input.getCols(); i++) {
        Type curType = input.getColType(i);
        string curColName = input.getColName(i);
        colNames.push_back(curColName);
        colTypes.push_back(curType);

        if(colName.compare(curColName) == 0) {
            sortType = curType;
            sortIndex = indices[curType];
        }
        indices[curType]++;
    }
    
    entries = new vector<Record*>();

    Sort();
}

CMemReadAccessor& SortedVector::getAccessor() {
    CMemReadAccessor *reader = new CMemReadAccessor(input.getName(), &colNames, &colTypes, entries);
    return *reader;
}

void SortedVector::Sort() {
    ITracer::GetTracer()->Trace("SortedVector::Sort Called\n");

    while(true) {
        Record *curRecord = input.getNextRecord();
        if(curRecord == nullptr) {
            break;
        }
        AddRecord(curRecord);
    }    
}

void SortedVector::AddRecord(Record* curRecord) {

    ITracer::GetTracer()->Trace("SortedVector::AddRecord Called\n");

    int lowIndex = 0;
    int highIndex = entries->size() - 1;
    int mid = 0;
    CRecordColumn lhs(sortIndex, sortType, curRecord);
    while(true) {    
        if(lowIndex > highIndex) {
            entries->insert(entries->begin() + lowIndex, curRecord);
            ITracer::GetTracer()->Trace("Added a record to the sorted vector\n");
            break;
        }

        mid = (lowIndex + highIndex) / 2;  
        Record *midRecord = entries->at(mid);
        CRecordColumn rhs(sortIndex, sortType, midRecord);
        int compOutput = lhs.Comp(rhs);

        if(compOutput == 0) {
            entries->insert(entries->begin() + mid, curRecord);
            ITracer::GetTracer()->Trace("Added a record to the sorted vector\n");
            break;
        } else if(compOutput == 1) {
            lowIndex = mid + 1;
        } else if(compOutput == -1) {
            highIndex = mid - 1;
        } else {
            throw("Issue with scalar comparator");
        }
    }
}