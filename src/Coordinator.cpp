#include <iostream>
#include <vector>
#include <semaphore.h>
#include <pthread.h>

#include <unistd.h>


using namespace std;

#include "../include/Coordinator.h"


typedef struct param
{
	Node *from;
	
	IMessageQueue *mq;
	Node *to;
	void *msg;
	int action_code;
	
} param;

param *get_param(Node *from, IMessageQueue *mq, Node *to, void *msg, int action_code)
{
	param *tmp = new param;
	
	tmp->from = from;
	tmp->mq = mq;
	tmp->to = to;
	tmp->msg = msg,
	tmp->action_code = action_code;
	
	return tmp;
}

void *send_function(void *arg)
{
	pthread_detach(pthread_self());
	
	param *p = (param *)arg;
	//cout << "[Coor] 2. Sending action code " << p->action_code <<  "[Coor] From: "<< p->from << " To: " << p->to << '\n';
	(p->from)->send(p->mq, p->to, p->msg, p->action_code);
	//if(p->msg)
		//cout << "[Coord] 3. Row number: " << ((Log_t *)p->msg)->row << '\n';
	
	pthread_exit(NULL);	
}

Coordinator::Coordinator(int workerCount, vector <Node*> workers, IMessageQueue *mq)
{
	this->workerCount = workerCount;
	this->mq = mq;
	
	cout << "\n\nCoordinator: " << this << "\nWorkers: ";
	for(auto node : workers)
	{
		workerList.push_back(node);
		cout << node << ' ';
	}
	cout << "\n";
	
	sem_init(&sNode_lock, 1, 1);
	sem_init(&fNode_lock, 1, 1);
}

Coordinator::~Coordinator()
{
	for(auto node : workerList)
		free(node);
	
	free(mq);
}
	
int Coordinator::performTransaction(vector <Log_t*> operation)
{
	//cout << "[Coor] Starting transaction\n";
	pthread_t pid[workerCount];
	
	/* prepare phase */	
	successNodes.clear();
	failedNodes.clear();
	
	param *p[workerCount];
	
	for(int i = 0; i<workerCount; ++i)
	{
		if(operation[i] != NULL)
		{
			p[i] = get_param(this, this->mq, workerList[i], NULL, 10);
			cout << "[Coor] 1. Sending action code " << p[i]->action_code << " to " << workerList[i] << '\n';
			pthread_create(&pid[i], NULL, send_function, (void*)p[i]);
			//cout << "[Coord] Created a thread\n";
		}		
	}
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] != NULL)
			pthread_join(pid[i], NULL);
	}
	
	if(!failedNodes.empty())
	{		
		/* prepare rollback */
		int i = 0;
		for(auto node : successNodes)
		{
			param *p = get_param(this, this->mq, node, NULL, 11);
			pthread_create(&pid[i++], NULL, send_function, (void*)p);		
		}
		
		while(--i >= 0)
		{
			pthread_join(pid[i], NULL);
		}
		
		/* prepare phase failed */
		return 0;
	}
	
	/* commit phase */
	successNodes.clear();
	failedNodes.clear();
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] != NULL)
		{
			param *p = get_param(this, this->mq, workerList[i], (void *)operation[i], 20);
			pthread_create(&pid[i], NULL, send_function, (void*)p);	
			sleep(1);
		}	
	}
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] != NULL)
			pthread_join(pid[i], NULL);
	}
	
	if(!failedNodes.empty())
	{		
		/* commit rollback */
		int i = 0;
		for(auto node : successNodes)
		{
			param *p = get_param(this, this->mq, node, NULL, 21);
			pthread_create(&pid[i++], NULL, send_function, (void*)p);		
		}
		
		while(--i >= 0)
		{
			pthread_join(pid[i], NULL);
		}
		
		/* prepare phase failed */
		return 0;
	}
	
	cout << "[Coord] Success nodes = ";
	for(auto it: successNodes)
		cout << it << ' ';
	cout << "\n\n";
	
	/* transaction complete, release all locks */
	for(int i = 0; i<workerCount; ++i)
	{
		if(operation[i] != NULL)
		{
			//cout << "\t[Coord] op row: "<< operation[i]->row << '\n';
			param *p = get_param(this, this->mq, workerList[i], NULL, 11);
			pthread_create(&pid[i], NULL, send_function, (void*)p);
		}		
	}
	
	for(int i = workerCount-1; i>=0; --i)
	{
		if(operation[i] != NULL)
			pthread_join(pid[i], NULL);
	}
	
	return 1;
}

void Coordinator::send(IMessageQueue *mq, Node *to, void *msg, int action_code)
{	
	mq->send(this, to, msg, action_code);
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
	
	else 
	{
		cout << "[Coord] Error in reply code\n";
	}	
}
