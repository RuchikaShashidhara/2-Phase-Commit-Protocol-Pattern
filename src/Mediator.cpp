#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "../include/Mediator.h"

/* IMessageQueue */

virtual void IMessageQueue::attach(Node *nd)
{
	participants.push_back(nd);
}

virtual void IMessageQueue::detach(Node *nd)
{
	erase(participants, nd);
}


/* MessageQueue */

MessageQueue::MessageQueue(const string& name) : name(name) {}

virtual void MessageQueue::send(Node *to, void *msg, int action_code)
{
	to->recv(this, to, msg, action_code);
}


/* Node */

virtual void Node::join(IMessageQueue *mq)
{
	mq->attach(this);
}

virtual void Node::leave(IMessageQueue *mq)
{
	mq->detach(this);
}
