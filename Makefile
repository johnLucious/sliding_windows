CC=g++

default: sender receiver

all: sender receiver

sender.o: src/sender.cpp src/sender.h
	$(CC) -c src/sender.cpp

receiver.o: src/receiver.cpp
	$(CC) -c src/receiver.cpp

sender: sender.o
	$(CC) -o sender sender.o

receiver: receiver.o
	$(CC) -o receiver receiver.o 

clean: 
	rm -f *.o