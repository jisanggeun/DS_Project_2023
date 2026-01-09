#pragma once
#include "MemberQueueNode.h"
using namespace std;

class MemberQueue
{	
private:
	MemberQueueNode *first;
	MemberQueueNode *new_node;
	MemberQueueNode *cur_node;

	int cur_num;
public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string name, int age, string date, string terms_type);
	MemberQueueNode* pop();
	MemberQueueNode* front();
};

