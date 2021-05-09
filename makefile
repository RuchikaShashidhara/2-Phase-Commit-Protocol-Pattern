execute: client_file_test.o DBSchema.o File.o
	g++ client_file_test.o DBSchema.o File.o -Wall -pthread

client_file_test.o: client_file_test.cpp src/DBSchema.cpp src/File.cpp
	g++ -c client_file_test.cpp -Wall -pthread

DBSchema.o: src/DBSchema.cpp File.o
	g++ -c src/DBSchema.cpp

File.o: src/File.cpp
	g++ -c src/File.cpp -Wall -pthread

clean:
	rm -rf *.o a.out
