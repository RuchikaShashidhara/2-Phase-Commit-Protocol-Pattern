#ifndef WORKER_H
#define WORKER_H

#include <vector>

#include "Logs.h"
#include "Mediator.h"
#include "File.h"
#include "DBFile.h"

class Worker : public Node
{
	private:
		DBFile *fp;
		vector <Log_t *> logs;
		
		int prepare();
		int releaseLock();
		int commit(void* operation);
		int commitRollback();	
		
	public:
		Worker(File *fp);
		
		virtual void send(IMessageQueue *mq, Node *to, void *msg, int reply_code);
		virtual void recv(IMessageQueue *mq, Node *from, void *msg, int action_code);
};

#endif
