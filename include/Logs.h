#ifndef LOGS_H
#define LOGS_H

#include <string>

using namespace std;

struct Log
{
	int op_code;
		// 0  - add record
		// 1  - delete record
		// 2  - read record
		// 20 - read cell
		// 3  - update record
		// 30 - update cell
	int row;
	int col;
	vector <string> value;
};

typedef struct Log Log_t;

#endif
