#ifndef LOGS_H
#define LOGS_H

#include <string>

using namespace std;

struct Log
{
	int opCode;
		// 0 - add record
		// 1 - update record
		// 2 - delete record
		// 3 - read record
	int row;
	int col;
	string oldValue;
	string newValue;
};

typedef struct Log Log_t;

#endif