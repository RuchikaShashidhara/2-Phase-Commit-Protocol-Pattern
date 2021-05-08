#ifndef COORDINATOR
#define COORDINATOR

#include <vector>
#include <semaphore.h>

#include "Mediator.h"
#include "Worker.h"
#include "Logs.h"

class Coordinator : public Node
{
	private:
		int workerCount;
		vector <Worker> workerList;	
		vector <Log_t> logs;	
		IMessageQueue *mq;
		
		sem_t sNode_lock;
		vector <Worker> successNodes;
		sem_t fNode_lock;
		vector <Worker> failedNodes;
		
	public:
		Coordinator(int workerCount, vector <File& fileList, IMessageQueue *mq);
		int performTransaction(vector <Log_t*> operation);		
		
		virtual void send(IMessageQueue *mq, Node *to, void *msg, int action_code);
		virtual void recv(IMessageQueue *mq, Node *from, void *msg, int reply_code);
}

#endif

