#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#include "../include/Mediator.h"

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

void MessageQueue::send(Node *from, Node *to, void *msg, int action_code)
{
	//cout << "[MQ] Sending msg to worker " << action_code << '\n';
	to->recv(this, from, msg, action_code);
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
