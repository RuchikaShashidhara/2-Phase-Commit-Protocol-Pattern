#ifndef LOGS_H
#define LOGS_H

#include <string>

using namespace std;

struct Log
{
	int record_op;
		// 1 = true  => record operation
		// 0 = false => cell operation		
	int read_op;
		// 1 => read operation
		// 0 => write - update operation
		// 2 => write - add new record operation
		// 3 => write - delete record operation
	int row;// row number
	int col;// column number
	vector <string> value;	
		// record value that is being communicated between each line
};

typedef struct Log Log_t;

#endif