main: main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp 
	g++ -std=c++0x main.cpp CMemWriteAccessor.cpp CCSVDeserializer.cpp CMemReadAccessor.cpp CCSVSerializer.cpp CMemTable.cpp -o main -g -Wall

