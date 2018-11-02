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
#include <fstream>
#include "sender.h"
#include "frame.h"

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
socklen_t len;

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
		buffersize = atoi(argv[3]);
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

int sumArrElmt(int e[]){
	int sum = 0;
	for(int i = 0; i < sizeof(e); i++){
		sum += e[i];
	}
	return sum;
}

int main(int argc, char* argv[]){
	char text[BUFFER_SIZE], buffer[BUFFER_SIZE], recvBuff[10 + BUFFER_SIZE];
	int counter;
	char c;
	char *tempFrame;
	initialize(argc, argv);
	if (bind(_socket, (struct sockaddr *) &socket_send, _socket_len) < 0){
		printf("Error, exit");
		exit(EXIT_FAILURE);
	}
	
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL){
		err("File::File Not Found");
	}
	
	while (true) {
		counter = 0;
		
		ifstream ifs(filename, ifstream::binary);
		ifs.read(buffer, buffersize * 1024);
		
		int seqnum = 0;
		int ack[windowsize];
		
		for (int i = 0; i < windowsize; i++)
			ack[i] = 0;
		
		int lastAckRecv = 0;
		int lastRecvFrame = 0;
		int datalen;
		while (sumArrElmt(ack) < windowsize){
			char *buff = new char[10 + BUFFER_SIZE];
			datalen = BUFFER_SIZE;
			memset(buff , 0x1, 1);
			memcpy(buff + 1, &seqnum, 4);
			memcpy(buff + 5, &datalen, 4);
			memcpy(buff + 9, buffer + (seqnum * 1024), BUFFER_SIZE);
			memset(buff + 9 + datalen, 0x0, 1);
			
			if (sendto(_socket, buff, sizeof(buffer), 0, (struct sockaddr *) &socket_recv, sizeof(socket_recv)) < 0) {
				err("Socket::Failed to Send Packet");
			}
			else {
				printf("Packet sent SeqNum %d on port %d\n", seqnum, destination_port);
			}
			
			if (recvfrom(_socket, &recvBuff, BUFFER_SIZE, 0, (struct sockaddr *) &socket_recv, &len) < 0) {
				err("Socket::Failed to Retrieve from Server");
			}
			else {
				//~ int acknum;
				//~ char ackrecv = recvBuff[0];
				//~ memcpy(&acknum, recvBuff + 1, 4);
				//~ char checksumRecv = recvBuff[5];
				//~ //acknum = *((int*)(recvBuff + 1));
				//~ ack[acknum] = 1;
				printf("%s\n", recvBuff);
			}
			
			
			free(buff);
			seqnum++;
		}
		
		// Packet framing
		//~ while ((c = fgetc(file)) != EOF){
			//~ ungetc(file);
			//~ int currsize = 0;
			//~ tempFrame = (char *) malloc(sizeof(char) * 1024);
			//~ while (currsize < BUFFER_SIZE && (c = fgetc(file)) != EOF){
				//~ tempFrame[currsize] = (char) c;
				//~ currsize++;
			//~ }
			//~ if (c == EOF) {
				//~ tempFrame[currsize-1] = '\0';
				//~ currsize--;
			//~ }
			//~ //Frame frame = createFrame(counter, currsize, tempFrame);
			//~ char *buffer = new char[10 + currsize];
			
			
			
			
			//~ if (sendto(_socket, 
			
			//~ counter++;
		//~ }
		
		// Iterate on window
		
			
		//~ printf("Input text to be sent: ");
		//~ fgets(text, BUFFER_SIZE, stdin);
		//~ if (sendto(_socket, text, sizeof(text), 0, (struct sockaddr *) &socket_recv, sizeof(socket_recv)) < 0){
			//~ err("Socket::Failed to Send");
		//~ }
		
		//~ if (recvfrom(_socket, &buffer, BUFFER_SIZE, 0, (struct sockaddr *) &socket_recv, &len) < 0){
			//~ err("Socket::Client Receive Failed");
		//~ }
		//~ else
			//~ printf("Server: %s\n", buffer);]
		
	}
	
}
