#ifndef FTABLE
#define FTABLE

typedef struct processFileTable {
	unsigned char valid;
	char method;
	int offset;
	int first_cluster;
	int size;
	int current_cluster; /* 0 - 0xFFF */
	int current_pointer; /* 0 - 0x200 */
	int current_size;
	unsigned char cache[512];
};

typedef struct globalFileTable {
	unsigned char valid;
	char method;
	int first_cluster;
	int count;
};

#endif