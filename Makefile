main: main.cpp CMemWriteAccessor.cpp CMemDeserializer.cpp CMemReadAccessor.cpp CMemSerializer.cpp CMemTable.cpp 
	g++ -std=c++0x main.cpp CMemWriteAccessor.cpp CMemDeserializer.cpp CMemReadAccessor.cpp CMemSerializer.cpp CMemTable.cpp -o main -g -Wall

