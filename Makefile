main: main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp CProject.cpp CVarRuntimeUsingRecord.cpp CSelect.cpp AccessorRelOp.cpp CJoin.cpp CSort.cpp SortedVector.cpp CRecordColumn.cpp CMergeJoin.cpp LValue.cpp Tokenizer.cpp MultiLValue.cpp ValuePOD.cpp CHashTableAccessor.cpp TableHashMap.cpp
	g++ -std=c++17 -g main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp CProject.cpp CVarRuntimeUsingRecord.cpp CSelect.cpp AccessorRelOp.cpp CJoin.cpp CSort.cpp SortedVector.cpp CRecordColumn.cpp CMergeJoin.cpp LValue.cpp Tokenizer.cpp MultiLValue.cpp ValuePOD.cpp CHashTableAccessor.cpp TableHashMap.cpp -o main -g -Wall

