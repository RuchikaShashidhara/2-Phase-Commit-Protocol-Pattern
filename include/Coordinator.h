#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <vector>
#include <semaphore.h>

#include "Mediator.h"
#include "Worker.h"
#include "Logs.h"

class Coordinator : public Node
{
	private:
		int workerCount;
		vector <Node *> workerList;	
		vector <Log_t *> logs;	
		IMessageQueue *mq;
		
		sem_t sNode_lock;
		vector <Node *> successNodes;
		
		sem_t fNode_lock;
		vector <Node *> failedNodes;
		
	public:
		Coordinator(int workerCount, vector <Node*> workers, IMessageQueue *mq);
		int performTransaction(vector <Log_t*> operation);		
		
		virtual void send(IMessageQueue *mq, Node *to, void *msg, int action_code);
		virtual void recv(IMessageQueue *mq, Node *from, void *msg, int reply_code);
};

#endif
