#pragma once
#include <string>
using namespace std;

class TermsBSTNode
{
private:
	string name, start_date, end_date;
	int age;

	TermsBSTNode*	left;
	TermsBSTNode*	right;

public:
	TermsBSTNode() {
		age = 0;
		left = nullptr;
		right = nullptr;
	}
	~TermsBSTNode() {}

	void setTermsBSTNode(string name, int age, string start_date, string end_date) {
		this->name = name;
		this->age = age;
		this->start_date = start_date;
		this->end_date = end_date;
	}

	string getTermsBST_name() {
		return name;
	}

	int getTermsBST_age() {
		return age;
	}
	
	string getTermsBST_StartDate() {
		return start_date;
	}

	string getTermsBST_EndDate() {
		return end_date;
	}

	TermsBSTNode*	getLeft()			{ return left; }
	TermsBSTNode*	getRight()			{ return right; }

	void setLeft (TermsBSTNode* left)	{ this->left = left; }
	void setRight(TermsBSTNode* right)	{ this->right = right; }
};