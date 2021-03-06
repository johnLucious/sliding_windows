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
#include <fstream>

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
int port;

// Socket
struct sockaddr_in socket_send, socket_recv;
int _socket, _socket_len = sizeof(socket_recv);

// Window
SenderWindow window;

void err(std::string msg) {
	perror(msg.c_str());
	exit(-1);
}	

void initialize(int argc, char* argv[]){
	// Check input validation
	if (argc < 5){
		printf("In::Input is not valid\n");
		printf("Format input: ./sendfile [filename] [windowsize] [buffersize] [port]\n");
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
		port= atoi(argv[4]);
		
		// Config Window
		//~ char *buffer = (char *) malloc(sizeof(*buffer) * buffersize);
		//~ bool *ack = (bool *) malloc(sizeof(*ack) * buffersize);
		//~ clock_t *startTime = (clock_t *) malloc(sizeof(*startTime) * buffersize);
		//~ window = {0,0,0, windowsize, buffer, ack, startTime};
		
		// Create UDP Socket
		if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
			err("Socket::Error Creating Socket");
		}
		
		socket_recv.sin_family = AF_INET;
		socket_recv.sin_port = htons(port);
		socket_recv.sin_addr.s_addr = htonl(INADDR_ANY);
		memset(socket_recv.sin_zero, '\0', sizeof(socket_recv.sin_zero));
	}
}

int main(int argc, char* argv[]){
	int seqnum, datalen;
	initialize(argc, argv);
	cout << "Initialize success" << endl;
	char buffer[BUFFER_SIZE], recvBuff[BUFFER_SIZE];
	char checksum, soh;
	
	char *text = "Hello From Server";
	if (bind(_socket, (const struct sockaddr *) &socket_recv, _socket_len) < 0){
		printf("Error, exit");
		exit(EXIT_FAILURE);
	}
	
	//~ cout << "Bind success" << endl;
	socklen_t len = sizeof(socket_send);
	int recv, recv_len;
	ofstream ofs("testres.txt", ofstream::out);
	while (true){
		if (recvfrom(_socket, &buffer, BUFFER_SIZE, 0, (struct sockaddr *) &socket_send, &len) < 0){
			err("Socket::Receive Failed");
		}
		else {
			//~ buffer[strlen(buffer)] = '\0';
			//~ printf("Client: %s\n", buffer);
			soh = buffer[0];
			memcpy(&seqnum, buffer + 1, 4);
			memcpy(&datalen, buffer + 5, 4);
			memcpy(&recvBuff, buffer + 9, datalen);
			checksum = buffer[sizeof(buffer)];
			printf("Receive %d from port %d\n", seqnum, port);
		}
		
		ofs << recvBuff;
		
		char sendBuff[5];
		memset(sendBuff, seqnum, 1);
		int next = seqnum + 1;
		memcpy(sendBuff + 1, &next, 4);
		memset(sendBuff + 5, 0x0, 1);
		
		//Send Reply Status
		if (sendto(_socket, sendBuff, 5, 0,(struct sockaddr *) &socket_send, sizeof(socket_send)) < 0){
			err("Socket::Server Reply Failed");
		}
		else {
			printf("Send Ack SeqNum %d to Client\n", seqnum);
		}
		if (seqnum == 5){
			ofs.close();
			break;
		}
	}
	//~ FILE *file = fopen(filename, "r");
	//~ if (file == NULL){
		//~ err("File::File Not Found")
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
