CC=g++ -Wall 


clientserveripc: main.o filehandler.o service.o server.o client.o 
	$(CC) -o clientserveripc main.o filehandler.o service.o server.o client.o $(CLIB)

clean:
	rm -f *.o core.* clientserveripc
clientserveripc.o:
	$(CC) -c main.cpp
filehandler.o:
	$(CC) -c filehandler.cpp
service.o:
	$(CC) -c service.cpp
server.o: 
	$(CC) -c server.cpp
client.o:
	$(CC) -c client.cpp
