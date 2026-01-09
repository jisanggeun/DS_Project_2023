#pragma once
#include <string>
using namespace std;

class NameBSTNode
{
private:
	string name, start_date, end_date, terms_type;
	int age;
	NameBSTNode*	left;
	NameBSTNode*	right;
	
public:
	NameBSTNode() {
		age = 0;
		left = nullptr;
		right = nullptr;
	}
	~NameBSTNode() {}

	void setNameBSTnode(string name, int age, string start_date, string end_date, string terms_type) {
		this->name = name;
		this->age = age;
		this->start_date = start_date;
		this->end_date = end_date;
		this->terms_type = terms_type;
	}

	string getNameBST_name() {
		return name;
	};

	int getNameBST_age() {
		return age;
	}

	string getNameBST_StartDate() {
		return start_date;
	}

	string getNameBST_EndDate() {
		return end_date;
	}

	string getNameBST_Terms_type() {
		return terms_type;
	}

	NameBSTNode*	getLeft()			{ return left; }
	NameBSTNode*	getRight()			{ return right; }

	void setLeft(NameBSTNode* left)						{ this->left = left; }
	void setRight(NameBSTNode* right)					{ this->right = right; }
};