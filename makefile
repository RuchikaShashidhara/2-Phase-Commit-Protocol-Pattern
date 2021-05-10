execute: client_2.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o
	g++ client_2.o Amazon.o DBSchema.o File.o DBFile.o Mediator.o Worker.o Coordinator.o -Wall -lpthread	
	
client_2.o: client_2.cpp
	g++ -c -std=c++2a client_2.cpp

Amazon.o: src/Amazon.cpp
	g++ -c -std=c++2a src/Amazon.cpp

DBSchema.o: src/DBSchema.cpp File.o
	g++ -c -std=c++2a src/DBSchema.cpp

File.o: src/File.cpp
	g++ -c -std=c++2a src/File.cpp -Wall
	
DBFile.o: src/DBFile.cpp 
	g++ -c -std=c++2a src/DBFile.cpp -Wall -lpthread
	
Mediator.o: src/Mediator.cpp
	g++ -c -std=c++2a src/Mediator.cpp -Wall
	
Worker.o: src/Worker.cpp
	g++ -c -std=c++2a src/Worker.cpp -Wall
	
Coordinator.o: src/Coordinator.cpp
	g++ -c -std=c++2a src/Coordinator.cpp -Wall -lpthread

clean:
	rm -rf *.o a.out
