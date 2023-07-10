main: main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp CProject.cpp
	g++ -std=c++17 main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp ScaOpEq.cpp JobEval.cpp CVarVal.cpp CVarRuntime.cpp ctracer.cpp CProject.cpp -o main -g -Wall

