#include "../include/Coordinator.h"

using namespace std;

#include <vector>
#include <semaphore.h>
#include <pthread.h>

typedef struct param
{
	Node *from;
	
	IMessageQueue *mq;
	Node *to;
	void *msg;
	int action_code;
	
} param;

void *send_function(void *arg)
{
	pthread_detach(pthread_self());
	
	param *p = (param *)arg;
	(p->from)->send(p->mq, p->to, p->msg, p->action_code);
	
	pthread_exit(NULL);	
}

Coordinator::Coordinator(int workerCount, vector <File&> fileList, IMessageQueue *mq)
{
	this->workerCount = workerCount;
	this->mq = mq;
	
	for(auto file : fileList)
	{
		workerList.append(Worker(file));
	}
	
	sem_init(&sNode_lock, 0, 1);
	sem_init(&fNode_lock, 0, 1);
}
	
int Coordinator::performTransaction(vector <Log_t*> operation)
{
	pthread_t pid[workerCount];
	
	/* prepare phase */	
	successNodes.clear();
	failedNodes.clear();
	
	for(int i = 0; i<workerCount; ++i)
	{
		if(operation[i] == NULL) break;
		param p = {this, this->mq, workerList[i], NULL, 10};
		pthread_create(&pid[i], NULL, send_function, (void*)p);		
	}
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] == NULL) break;
		pthread_join(&pid[i]);
	}
	
	if(!failedNodes.empty())
	{		
		for(int i = 0; i<workerCount; ++i)
		{
			if(operation[i] == NULL) break;
			param p = {this, this->mq, workerList[i], NULL, 11};
			pthread_create(&pid[i], NULL, send_function, (void*)p);		
		}
		
		for(int i = workerCount-1; i>=0; --i)
		{
			if(operation[i] == NULL) break;
			pthread_join(&pid[i]);
		}
		
		return 0;
	}
	
	/* commit phase */
	successNodes.clear();
	failedNodes.clear();
	
	for(int i = 0; i<workerCount; ++i)
	{
		if(operation[i] == NULL) break;
		param p = {this, this->mq, workerList[i], (void *)operation[i], 20};
		pthread_create(&pid[i], NULL, send_function, (void*)p);		
	}
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] == NULL) break;
		pthread_join(&pid[i]);
	}
	
	if(!failedNodes.empty())
	{		
		for(int i = 0; i<workerCount; ++i)
		{
			if(operation[i] == NULL) break;
			param p = {this, this->mq, workerList[i], NULL, 21};
			pthread_create(&pid[i], NULL, send_function, (void*)p);		
		}
		
		for(int i = workerCount-1; i>=0; --i)
		{
			if(operation[i] == NULL) break;
			pthread_join(&pid[i]);
		}
		
		return 0;
	}	
	
	
}

void Coordinator::send(IMessageQueue *mq, Node *to, void *msg, int action_code)
{	
	mq->send(to, msg, action_code);
}

void Coordinator::recv(IMessageQueue *mq, Node *from, void *msg, int reply_code)
{
	if(reply_code == 0)
	{
		sem_wait(&fNode_lock);
		failedNodes.push_back(from);
		sem_post(&fNode_lock);
	}
	
	else if(reply_code == 1)
	{
		sem_wait(&sNode_lock);
		successNodes.push_back(from);
		sem_post(&sNode_lock);
	}
}
