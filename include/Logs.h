#ifndef LOGS_H
#define LOGS_H

#include <string>

using namespace std;

struct Log
{
	int record_op;
		// 1 = true
		// 0 = false => cell operation
		
	int read_op;
		//1 = true
		//0 = false => write(update) operation
		//2 => add new record operation
	int row;
	int col;
	vector <string> value;
};

typedef struct Log Log_t;

#endif
