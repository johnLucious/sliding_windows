// Author	: 13516011 - Jansen
// File		: sender.cpp


// File Header
#include <sys/syscall.h>
#include <sstream>
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
#include "sender.h"

using namespace std;

#define BUFFER_SIZE 1024
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

// Socket
struct sockaddr_in socket_send, socket_recv;
int _socket, _socket_len = sizeof(socket_send);

// Window
SenderWindow window;

void err(std::string msg) {
	perror(msg.c_str());
	exit(-1);
}	

void initialize(int argc, char* argv[]){
	// Check input validation
	if (argc < 6){
		printf("In::Input is not valid\n");
		printf("Format input: ./sendfile [filename] [windowsize] [buffersize] [hostname] [destination_port]\n");
		err("EXIT_FAILURE");
	}
	else if (argc > 7){
		printf("In::Input is not valid\n");
		printf("In::Arguments found too much");
		exit(EXIT_FAILURE);
	}
	else {
		filename = argv[1];
		windowsize = atoi(argv[2]);
		buffersize = BUFFER_SIZE;
		hostname = argv[4];
		destination_port= atoi(argv[5]);
		
		// Config Window
		//~ char *buffer = (char *) malloc(sizeof(*buffer) * buffersize);
		//~ bool *ack = (bool *) malloc(sizeof(*ack) * buffersize);
		//~ clock_t *startTime = (clock_t *) malloc(sizeof(*startTime) * buffersize);
		//~ window = {0,0,0, windowsize, buffer, ack, startTime};
		
		// Create UDP Socket
		if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
			err("Socket::Error Creating Socket");
		}
		
		socket_send.sin_family = AF_INET;
		//~ socket_send.sin_port = htons();
		socket_send.sin_addr.s_addr = htonl(INADDR_ANY);
		memset(socket_send.sin_zero, '\0', sizeof(socket_send.sin_zero));;
		
		socket_recv.sin_family = AF_INET;
		socket_recv.sin_port = htons(destination_port);
		socket_recv.sin_addr.s_addr = inet_addr(hostname);
		
		//~ if(inet_pton(AF_INET, hostname, &socket_send.sin_addr.s_addr) < 0){
			//~ err("Socket::Failed to Connect");
		//~ }
	}
}

int main(int argc, char* argv[]){
	char text[BUFFER_SIZE];
	initialize(argc, argv);
	if (bind(_socket, (struct sockaddr *) &socket_send, _socket_len) < 0){
		printf("Error, exit");
		exit(EXIT_FAILURE);
	}
	while (true) {
		printf("Input text to be sent: ");
		fgets(text, BUFFER_SIZE, stdin);
		if (sendto(_socket, text, sizeof(text), 0, (struct sockaddr *) &socket_recv, sizeof(socket_recv)) < 0){
			err("Socket::Failed to Send");
		}
		else {
			printf("Message Sent\n");
		}
	}
	//~ FILE *file = fopen(filename, "r");
	//~ if (file == NULL){
		//~ err("File::File Not Found");
	//~ }
	//~ Byte c;
	//~ bool endFile = false;
	
	//~ while(true){
		//~ while(window.count <= window.maxsize / 2 && !endfile){
			//~ if(lastReceivedChar != xOFF){
				//~ if(fscanf(file, "%c", &c) == EOF){
					//~ h = endfile;
					//~ endfile = true;
				//~ }
				//~ putBack(c, &window);
			//~ }
		//~ }
		
	//~ }
}
