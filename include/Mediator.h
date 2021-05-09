#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include <vector>

class Node;

class IMessageQueue
{
	public:
		virtual ~IMessageQueue() {}
		virtual void attach(Node *);
		virtual void detach(Node *);
		virtual void send(Node *to, void *msg, int action_code) = 0;
	
	protected:
		vector <Node *> participants;
};

class MessageQueue : public IMessageQueue
{
	private:
		string name;
		
	public:
		MessageQueue(const string& name);
		virtual void send(Node *to, void *msg, int action_code);
};

class Node
{
	public:
		virtual ~Node() {}
		virtual void join(IMessageQueue *mq);
		virtual void leave(IMessageQueue *mq);
		virtual void send(IMessageQueue *mq, Node *to, void *msg, int reply_code) = 0;
		virtual void recv(IMessageQueue *mq, Node *from, void *msg, int action_code) = 0;
};

#endif
