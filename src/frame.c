// File		: frame.c

#include "frame.h"

Frame createFrame(int seqnum, int datalen, char *data){
	Frame frame;
	frame.soh = 0x1;
	frame.seqnum = seqnum;
	frame.datalen = datalen;
	frame.data = data;
	frame.checksum = 0x0;
	
	return frame;
}

