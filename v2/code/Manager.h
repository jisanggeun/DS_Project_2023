#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
#include <sstream>

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
	bool load_able;

public:
	// constructor
	Manager(int bpOrder) {
		load_able = true;
		bptree = new BpTree(&flog, 3); // bpOrder always 3
		stree = new SelectionTree(&flog);
	}

	// destructor
	~Manager() {
		flog.close();
	}

	ifstream fin;
	ifstream fdata;
	ofstream flog;

	void run(const char* command);
	// Load Instruction
	bool LOAD(const char* command);
	// Add Instruction
	bool ADD(string name, int code, string author, int year);

	// Single Search Instruction
	bool SEARCH_BP_BOOK(string book);
	// Range Search Instruction
	bool SEARCH_BP_RANGE(string start, string end);

	// Print BpTree Instruction
	bool PRINT_BP();
	// Print Selection Tree Instruction
	bool PRINT_ST(int bookCode);

	// Delete Instruction
	bool DELETE();

	// EXIT Instruction
	bool EXIT();

	// Error code print
	void printErrorCode(int n);
	// Success code print
	void printSuccessCode(const char* command);

	// Logic for finding a book in the BpTree
	LoanBookData* searchBook_return(string name);
};

