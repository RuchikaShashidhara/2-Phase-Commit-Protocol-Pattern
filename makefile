Amazon_client: Amazon_clinet.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o
	g++ Amazon_clinet.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o -Wall -lpthread -o client.o

Amazon_testcase: Amazon_testcase.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o
	g++ Amazon_testcase.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o -Wall -lpthread -o check_testcase.o
	
Amazon_clinet.o: Amazon_client.cpp
	g++ -c -std=c++2a Amazon_client.cpp -o Amazon_clinet.o

Amazon_testcase.o: Amazon_testcase.cpp
	g++ -c -std=c++2a Amazon_testcase.cpp -o Amazon_testcase.o

Amazon.o: Amazon.cpp
	g++ -c -std=c++2a Amazon.cpp -o Amazon.o

DBSchema.o: src/DBSchema.cpp File.o
	g++ -c -std=c++2a src/DBSchema.cpp -o DBSchema.o

File.o: src/File.cpp
	g++ -c -std=c++2a src/File.cpp -Wall -o File.o
	
DBFile.o: src/DBFile.cpp 
	g++ -c -std=c++2a src/DBFile.cpp -Wall -lpthread -o DBFile.o
	
Mediator.o: src/Mediator.cpp
	g++ -c -std=c++2a src/Mediator.cpp -Wall -o Mediator.o
	
Worker.o: src/Worker.cpp
	g++ -c -std=c++2a src/Worker.cpp -Wall -o Worker.o
	
Coordinator.o: src/Coordinator.cpp
	g++ -c -std=c++2a src/Coordinator.cpp -Wall -lpthread -o Coordinator.o

clean:
	rm -rf *.o 
