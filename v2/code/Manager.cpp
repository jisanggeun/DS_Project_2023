#include "Manager.h"

void Manager::run(const char* command) {
	string line;

	fin.open(command);
	flog.open("log.txt", ios::app);

	if (!fin) {
		flog << "File Open Error" << endl;
		return;
	}
	while (getline(fin, line)) {
		// Carriage return processing
		if (!line.empty() && line.back() == '\r') line.pop_back();
		if(fin.fail()) {
			fin.clear(); // buffer clear
			continue;
		}
		if (line.find("LOAD") != string::npos) { // Load instruction
			fdata.open("loan_book.txt");
			if (!fdata) { // loan_book.txt is not exist
				load_able = false;
				fdata.close();
			}

			if (load_able) { // load_able is true
				load_able = false; // Because the data is already in
				const char* input_cmd = line.c_str();
				LOAD(input_cmd); 
			}
			else if (!load_able) printErrorCode(100); // Error code
		}
		else if (line.find("ADD") != string::npos) { // Add instruction
			int i = 0;
			string input_str, input_cmd, input_name, input_code, input_author, input_year;
			istringstream cmd(line);

			while (getline(cmd, input_str, '\t')) {
				// Split string based on tab
				if (i == 0) input_cmd = input_str;
				else if (i == 1) input_name = input_str;
				else if (i == 2) input_code = input_str;
				else if (i == 3) input_author = input_str;
				else if (i == 4) input_year = input_str;
				i++; // Increase number of arguments
			}

			if (i == 5) {
				load_able = false; // load_able = false because the data has already been transferred to the data structure.
				int code = stoi(input_code); // convert string to int
				int year = stoi(input_year); // convert string to int
				ADD(input_name, code, input_author, year); // Passing arguments to add
			}
			else printErrorCode(200); // Error Code
		}
		else if (line.find("SEARCH_BP") != string::npos) { // Search BpTree instruction
			int i = 0;
			string input_str, input_cmd, input_name, input_name2;
			istringstream cmd(line);

			while (getline(cmd, input_str, '\t')) {
				// Split string based on tab
				if (i == 0) input_cmd = input_str;
				else if (i == 1) input_name = input_str;
				else if (i == 2) input_name2 = input_str;
				i++; // Increase number of arguments
			}

			if (i < 2) printErrorCode(300); // Error code output due to lack of arguments
			else if (i == 2) SEARCH_BP_BOOK(input_name); // Single search
			else if (i == 3) SEARCH_BP_RANGE(input_name, input_name2); // Range search
			else if (i > 3) printErrorCode(300); // Error code output due to too many parameters
		}
		else if (line.find("PRINT_BP") != string::npos) { // Print BpTree instruction
			PRINT_BP(); // Print BpTree
		}
		else if (line.find("PRINT_ST") != string::npos) { // Print Selection Tree instruction
			int i = 0;
			string input_str, input_cmd, input_code;
			istringstream cmd(line);
			while (getline(cmd, input_str, '\t')) {
				// Split string based on tab
				if (i == 0) input_cmd = input_str;
				else if (i == 1) input_code = input_str;
				i++; // Increase number of arguments
			}
			if (i == 2) {
				int code = stoi(input_code); // convert string to int
				PRINT_ST(code); // Execute PRINT command with code value as argument
			}
		}
		else if (line.find("DELETE") != string::npos) { // Delete instruction
			DELETE(); // Delete selection tree's root and corresponding min heap root
		}
		else if (line.find("EXIT") != string::npos) { // Exit instruction
			EXIT(); // EXIT instruction
		}
		else printErrorCode(700); // Else Instruction
	}
	fin.close(); // command file close
	flog.close(); // log file close
	return;
}

bool Manager::LOAD(const char* cmd) {
	// load instruction
	int index = 0;
	string line;
	while (getline(fdata, line)) { // Read line by line from file
		// Carriage return processing
		if (!line.empty() && line.back() == '\r') line.pop_back();
    
		stringstream ss(line);
		string split_line;

		string book_name;
		int book_code;
		string book_author;
		int book_year;
		int book_loan_count;

		while (getline(ss, split_line, '\t')) { // Output data separated by tabs ('\t')
			// Split string based on tab
			if (index % 5 == 0) book_name = split_line;
			else if (index % 5 == 1) book_code = stoi(split_line); // convert string to int
			else if (index % 5 == 2) book_author = split_line;
			else if (index % 5 == 3) book_year = stoi(split_line); // convert string to int
			else if (index % 5 == 4) {
				book_loan_count = stoi(split_line); // convert string to int
				LoanBookData* new_data = new LoanBookData();
				int threshold;
				if(book_code == 0 || book_code == 100 || book_code == 200) threshold = 3;
				else if(book_code == 300 || book_code == 400) threshold = 4;
				else if(book_code == 500 || book_code == 600 || book_code == 700) threshold = 2;

				new_data->setBookData(book_name, book_code, book_author, book_year, book_loan_count); // Set data information in new_data
				if(book_loan_count > threshold) {
					index++;
					continue;
				} else if(book_loan_count == threshold) {
					index++;
					stree->Insert(new_data);
					continue;
				}
				bptree->Insert(new_data); // Add data to Bptree 
			}
			index++; // increase index
		}
	}

	fdata.close(); // loan_book.txt close
	printSuccessCode(cmd); // Since load was successful, success text is output.
	return true;
}

bool Manager::ADD(string name, int code, string author, int year) {
	// add instruction
	LoanBookData* cur_data = searchBook_return(name); // Search for data to see if the data to be entered exists.
	if (cur_data) { // cur_data is exist
		if (cur_data->getCode() == 000 || cur_data->getCode() == 100 || cur_data->getCode() == 200) { // code == 000, 100, 200
			cur_data->updateCount(); // update loan count
			if (cur_data->getLoanCount() == 3) { // When threshold loan_count is reached
				// After deleting data from Bptree, move it to selection tree.
				bptree->Delete(cur_data);
				stree->Insert(cur_data); 
			}
		}
		else if (cur_data->getCode() == 300 || cur_data->getCode() == 400) { // code == 300, 400
			cur_data->updateCount(); // update loan count
			if (cur_data->getLoanCount() == 4) { // When threshold loan_count is reached
				// After deleting data from Bptree, move it to selection tree.
				bptree->Delete(cur_data);
				stree->Insert(cur_data);
			}
		}
		else if (cur_data->getCode() == 500 || cur_data->getCode() == 600 || cur_data->getCode() == 700) { // code == 500, 600, 700
			cur_data->updateCount(); // update loan count
			if (cur_data->getLoanCount() == 2) { // When threshold loan_count is reached
				// After deleting data from Bptree, move it to selection tree.
				bptree->Delete(cur_data);
				stree->Insert(cur_data);
			}
		}
	}
	else { // cur_data is not exist
		LoanBookData* new_data = new LoanBookData(); // generate new_data
		new_data->setBookData(name, code, author, year, 0); // Data information set to be added to new_data
		bptree->Insert(new_data); // Insert data into Bptree
	}
	// Write to log file 
	flog << "========" << "ADD" << "========" << endl;
	string str_code;
	if(code == 0) str_code = "000";
	else str_code = to_string(code);
	flog << name << "/" << str_code << "/" << author << "/" << year << endl;
	flog << "===================" << endl << endl;
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) {
	// Search in single target BpTree
	bool state = bptree->searchBook(book); // True if found after book search in BpTree, false if not
	if(state == false) printErrorCode(300); // if false Print Error code
	return true; 
}

bool Manager::SEARCH_BP_RANGE(string s, string e) {
	// Doing range search in BpTree
	bool state = bptree->searchRange(s, e); // True if found after searching range in BpTree, False otherwise.
	if(state == false) printErrorCode(300); // if false Print Error code
	return true;
}

bool Manager::PRINT_BP() {
	// Print all datanodes in BpTree
	bool state = bptree->printBook(); // All data nodes print true on success, false on failure
	if(state == false) printErrorCode(400); // if state == false -> Print Error code
	return true;
}

bool Manager::PRINT_ST(int bookCode) {
	// Find the node corresponding to the bookCode through the selection tree and output it from the min heap.
	bool state = stree->printBookData(bookCode); // True if there is a min heap corresponding to bookCode, false if not.
	if (state == false) printErrorCode(500); // if state == false -> Print Error code
	return true;
}

bool Manager::DELETE() {
	// Delete instruction
	bool state = stree->Delete(); // true if delete succeeds, false if delete
	if (state == true) printSuccessCode("DELETE"); // If state is true, success message
	else if (state == false) printErrorCode(600); // If state is false, error code
	return true;
}

bool Manager::EXIT() {
	// EXIT instruction
	printSuccessCode("EXIT"); 
	return 0; // destructor execution
}

void Manager::printErrorCode(int n) { // ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) { // SUCCESS CODE PRINT 
	flog << "========" << cmd << "========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

LoanBookData* Manager::searchBook_return(string name) {
	// Logic for finding a book in the B+ tree
	// If the book exists, return information about the book
	// If the book is not found, return nullptr
	if (bptree->getBookData(name)) return bptree->getBookData(name); // 가정: B+ 트리에서 책 데이터를 가져오는 함수
	else return nullptr;
}