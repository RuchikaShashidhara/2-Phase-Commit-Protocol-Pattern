#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#include "../include/Worker.h"

Worker::Worker(File *fp) : fp(dynamic_cast<DBFile*>(fp)) {}

int Worker::prepare()
{
	if(fp->acquire_lock(4, 0) == true)
		return 1;
	return 0;
}

int Worker::releaseLock()
{
	fp->release_lock();
	return 1;
}

int Worker::commit(void *op)
{	
	Log_t *operation = (Log_t *)op;
	Log_t *oldLog = fp->write(operation);
	
	if(oldLog == NULL)
		return 0;
		/*
	cout << "Record operatoin: " << op->record_op << '\n';
	cout << "Read operatoin: " << op->read_op << '\n';
	cout << "Row value: " << op->row << '\n';
	cout << "Column value: " << op->col << '\n';
	for(auto it: op->value)
		cout << it << ' ';
	cout << '\n';*/
		
	logs.push_back(oldLog);	
	
	cout << "[Worker "<< this <<"] Current log: \n";
	cout << "\tRecord operation: " << oldLog->record_op << '\n';
	cout << "\tRead operation: " << oldLog->read_op << '\n';
	cout << "\tRow value: " << oldLog->row << '\n';
	cout << "\tColumn value: " << oldLog->col << '\n';
	
	for(auto it: oldLog->value)
		cout << it << ' ';
	cout << '\n';
	
	cout << "[Worker "<< this <<"] Update worked\n";
	return 1;
}

int Worker::commitRollback()
{
	Log_t *oldOperation = logs.back();
	logs.pop_back();
	cout << "[Worker "<< this <<"] Write rollback\n";
	fp->write(oldOperation);
	
	fp->release_lock();
	return 1;
}

void Worker::send(IMessageQueue *mq, Node *to, void *msg, int reply_code)
{	
	mq->send(this, to, msg, reply_code);
}

void Worker::recv(IMessageQueue *mq, Node *from, void *msg, int action_code)
{
	cout << "[Worker "<< this <<"] Received action code " << action_code << " from " << from << '\n';
	int response;
	if(action_code == 10)
		response = this->prepare();
	
	else if(action_code == 11)
		response = this->releaseLock();
		
	else if(action_code == 20)
		response = this->commit(msg);
	
	else if(action_code == 21)
		response = this->commitRollback();
	
	this->send(mq, from, msg, response);		
}		
