#ifndef _FRAME_H_
#define _FRAME_H_

typedef struct Frame {
	char soh;
	unsigned int seqnum;
	int datalen;
	char *data;
	char checksum;
} Frame;

#endif
