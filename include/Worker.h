#ifndef WORKER
#define WORKER

#include <vector>

#include "Logs.h"
#include "Mediator.h"
#include "File.h"

class Worker : public Node
{
	private:
		File& fp;
		vector <Log_t *> logs;
		
	public:
		Worker(File& fp);
		int prepare();
		int releaseLock();
		int commit(void* operation);
		int commitRollback();	
		
		virtual void send(IMessageQueue *mq, Node *to, void *msg, int reply_code);
		virtual void recv(IMessageQueue *mq, Node *from, void *msg, int action_code);
};

#endif
