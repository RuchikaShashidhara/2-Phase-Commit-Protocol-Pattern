#include <string>
#include <vector>
#include <algorithm>

#include "../include/Mediator.h"

using namespace std;

/* IMessageQueue */

void IMessageQueue::attach(Node *nd)
{
	participants.push_back(nd);
}

void IMessageQueue::detach(Node *nd)
{
	erase(participants, nd);
}


/* MessageQueue */

MessageQueue::MessageQueue(const string& name) : name(name) {}

void MessageQueue::send(Node *to, void *msg, int action_code)
{
	to->recv(this, to, msg, action_code);
}


/* Node */

void Node::join(IMessageQueue *mq)
{
	mq->attach(this);
}

void Node::leave(IMessageQueue *mq)
{
	mq->detach(this);
}
