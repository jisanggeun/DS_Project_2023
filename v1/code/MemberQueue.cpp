#include "MemberQueue.h"

MemberQueue::MemberQueue() { // Initialized with constructor
	cur_num = 0;
	first = nullptr;
	new_node = nullptr;
	cur_node = nullptr;
}

MemberQueue::~MemberQueue() {
	
}

bool MemberQueue::empty() { // Function to determine whether q is empty or not
	if(cur_num == 0) return 1;
	else if(cur_num != 0) return 0;
}

bool MemberQueue::full() { // Function to determine whether q is full or not
	if(cur_num > 100) return 1; // You can receive up to 100, so starting from 101 is full
	else if(cur_num <= 100) return 0;
}

void MemberQueue::push(string name, int age, string date, string terms_type) {
	if(empty()) { // If empty, first = new_node
		new_node = new MemberQueueNode(); 
		new_node->set_qnode(name, age, date, terms_type); // set node 
		first = new_node;
		cur_num++; // To check the current count
	} else if(full()) { // In case of full, the program terminates when push comes in
		exit(-1);
	} else { // A state that is neither full nor empty
		new_node = new MemberQueueNode();
		new_node->set_qnode(name, age, date, terms_type);

		cur_node = first;
		while(cur_node->get_next() != nullptr) cur_node = cur_node->get_next(); // Since it is not first, it is sent backwards
		cur_node->set_next(new_node); // If next is null, set next	
		cur_num++;// To check the current count
	}
}

MemberQueueNode* MemberQueue::pop() {	
	if(empty()) exit(-1); // Pop it when empty and it ends.
	
	// Release them one by one and then reduce the number.
	cur_node = first;
	first = first->get_next();
	MemberQueueNode* return_node = cur_node;

	cur_node = nullptr;
	cur_num--;
	return return_node;	
}
MemberQueueNode* MemberQueue::front() {
	if (!empty()) return first; // first(head) node 
}
