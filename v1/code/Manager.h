#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Manager
{
private:

	ifstream	fcmd;
	ofstream	flog;
	MemberQueue* Member_Q;
	TermsLIST* Terms_List;
	TermsBST* Terms_BST;
	NameBST* Name_BST;
	int load_able;

public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void LOAD(const char* cmd);
	// ADD
	void ADD(const char* cmd, string name, int age, string date, string terms_type);
	// QPOP
	void QPOP(const char* cmd);
	// SEARCH
	void SEARCH(const char* cmd, string name);
	// PRINT
	void PRINT(const char* cmd, string type);
	// DELETE
	void DELETE(const char* cmd, string type, string data);
	// EXIT
	void destruct_name(NameBSTNode* node);
	void destruct_term(TermsBSTNode* node);
	void destruct_list(TermsListNode* node);
	void destruct_q(MemberQueueNode* node);
};
