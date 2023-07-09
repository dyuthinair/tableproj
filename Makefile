main: main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp
	g++ -std=c++0x main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp -o main -g -Wall

