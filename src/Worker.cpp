#include "../include/Worker.h"

using namespace std;

#include <vector>

Worker::Worker(File& fp) : fp(fp) {}

int Worker::prepare()
{
	if(fp.acquire_lock(3000) == true)
		return 1;
	return 0;
}

int Worker::releaseLock()
{
	fp.release_lock();
	return 1;
}

int Worker::commit(void *op)
{
	Log_t *operation = (Log_t *)op;
	if(fp.write(operation) == true)
	{
		logs.append(operation);
		return 1;
	}
	return 0;
}

int Worker::commitRollback()
{
	logs.pop_back();
	Log_t oldOperation = *(logs.rbegin()+1);
	fp.write(oldOperation);
	fp.release_lock();
	return 1;
}

void Worker::send(IMessageQueue *mq, Node *to, void *msg, int reply_code)
{	
	mq->send(to, msg, reply_code);
}

void Worker::recv(IMessageQueue *mq, Node *from, void *msg, int action_code)
{
	int response;
	if(action_code == 10)
		response = this->prepare();
	
	else if(action_code == 11)
		response = this->prepareRollback();
		
	else if(action_code == 20)
		response = this->commit(msg);
	
	else if(action_code == 21)
		response = this->commitRollback();
	
	this->send(mq, from, msg, response);		
}
		
		
		
