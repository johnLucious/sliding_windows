// Author	: 13516011 - Jansen
// File		: sender.cpp


// File Header
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define TIMEOUT 1000 // in ms

// Logging
time_t currentTime;
stringstream log_send;

// Variables
char* filename;
char* hostname;
unsigned int windowsize;
unsigned int buffersize;
int destination_port;

void initialize(int agrc, char* argv[]){
	// Check input validation
	if (argc < 6){
		printf("In::Input is not valid\n");
		printf("Format input: ./sendfile [filename] [windowsize] [buffersize] [hostname] [destination_port]\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 7){
		printf("In::Input is not valid\n");
		printf("In::Arguments found too much");
		exit(EXIT_FAILURE);
	}
	else {
		filename = argv[1];
		windowsize = atoi(argv[2]);
		buffersize = argv[3];
		hostname = argv[4];
		destination_port= atoi(argv[5]);
		
		// Create UDP Socket
	}
}

int main(int argc, char* argv[]){
	initialize(argc, argv);
	
	pthread_t recv_thread;
	if(pthread_create(&recv_thread, NULL, &receive_response, NULL) < 0) {
		error("Error creating thread");
	}

	FILE *files;
	files = fopen(filename, "r");

	if(files == NULL){
		error("File not found");
	}
	
	
}
