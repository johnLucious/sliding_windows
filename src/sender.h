#ifndef _SENDER_H_
#define _SENDER_H_

typedef struct SenderWindow {
	unsigned int count;
	unsigned int lfr;
	unsigned int laf;
	unsigned int maxsize;

	char *data;
	bool *ack;

	clock_t *startTime;
} SenderWindow;

#endif
