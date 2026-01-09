#pragma once
#include <string>
using namespace std;

class MemberQueueNode
{
private:
	string name, date, terms_type;
	int age;
	MemberQueueNode *next;

public:
	MemberQueueNode() { // initialize
		age = 0;
		next = nullptr;
	}
	~MemberQueueNode() {}

	// set node function
	void set_qnode(string name, int age, string date, string terms_type) {
		this->name = name;
		this->age = age;
		this->date = date;
		this->terms_type = terms_type;
	}  

	// get name
	string get_qnode_name() {
		return name;
	}

	// get date
	string get_qnode_date() {
        return date;
    }
	
	// get type
	string get_qnode_terms_type() {
        return terms_type;
    }

	// get age
	int get_qnode_age() {
		return age;
	}

	// set next function
	void set_next(MemberQueueNode *cur_node) {
		this->next = cur_node;
	}

	// get next
	MemberQueueNode* get_next() {
		return next; // return next node
	}
};