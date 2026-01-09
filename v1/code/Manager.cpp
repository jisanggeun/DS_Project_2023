#include "Manager.h"
#include <iostream>

Manager::Manager() // constructor
{
	// Dynamically create an object and point the pointer to it
	Member_Q = new MemberQueue();
	Terms_List = new TermsLIST();
	Terms_BST = new TermsBST();
	Name_BST = new NameBST();
	load_able = true;
}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
	string line;

    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd) {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
	while(!fcmd.eof()) {
		getline(fcmd, line); 
		if (fcmd.fail()) {
			fcmd.clear(); // buffer clear
			continue;
		}
		if(line.find("LOAD") != string::npos) {
			if(load_able) {
				load_able = false; // Because it was loaded once
				const char* input_cmd = line.c_str();
				LOAD(input_cmd);
			} else if(!load_able) PrintErrorCode(100);
		} else if(line.find("ADD") != string::npos) {
			string input_cmd, input_name, input_age, input_date, input_type;
			string input_str;
			istringstream cmd(line);
			int i = 0, convert_age;

			// false because the value entered the queue
			load_able = false;

			// separation
			while(getline(cmd, input_str, ' ')) {
				if(i == 0) input_cmd = input_str;
				else if(i == 1) input_name = input_str;
				else if(i == 2) input_age = input_str;
				else if(i == 3) input_date = input_str;
				else if(i == 4) input_type = input_str;
				i++;
			}
			if (i <= 4) PrintErrorCode(200); // There are not 5 arguments
			else if(i > 4) { // There are 5 arguments => normal input
				stringstream StoI(input_age);
				const char* convert_cmd = input_cmd.c_str();
				StoI >> convert_age; // convert string to int
				ADD(convert_cmd, input_name, convert_age, input_date, input_type);
			}
		} else if(line.find("QPOP") != string::npos) {
			const char* input_cmd = line.c_str();
			load_able = true;
			QPOP(input_cmd);		
		} else if(line.find("SEARCH") != string::npos) {
			string input_cmd, input_name, input_str;
			istringstream cmd(line);
			int i = 0;

			// seperate
			while(getline(cmd, input_str, ' ')) {
				if(i == 0) input_cmd = input_str;
				else if(i == 1) input_name = input_str;
				i++;
			}

			const char* convert_cmd = input_cmd.c_str();
			SEARCH(convert_cmd, input_name); // search operation
		} else if(line.find("PRINT") != string::npos) {
			string input_cmd, input_type, input_str;
			istringstream cmd(line);
			int i = 0;

			// seperate
			while(getline(cmd, input_str, ' ')) {
				if(i == 0) input_cmd = input_str;
				else if(i == 1) input_type = input_str;
				i++;
			}

			const char* convert_cmd = input_cmd.c_str();
			PRINT(convert_cmd, input_type); // print operation
		} else if(line.find("DELETE") != string::npos) {
			string input_cmd, input_type, input_data, input_str;
			istringstream cmd(line);
			int i = 0;

			// seperate
			while(getline(cmd, input_str, ' ')) {
				if(i == 0) input_cmd = input_str;
				else if(i == 1) input_type = input_str;
				else if(i == 2) input_data = input_str;
				i++;
			}

			const char* convert_cmd = input_cmd.c_str();
			DELETE(convert_cmd, input_type, input_data); // delete operation
		} else if(line.find("EXIT") != string::npos) {
			const char* input_cmd = line.c_str();

			NameBSTNode* destruct_nameNode;
			destruct_nameNode = Name_BST->getRoot(); // get root
			destruct_name(destruct_nameNode); // desturct nameBST node;

			TermsBSTNode* destruct_termsNode;
			destruct_termsNode = Terms_BST->getRoot(); // get root
			destruct_term(destruct_termsNode); // desturct termBST node;

			TermsListNode* destruct_listNode;
			destruct_listNode = Terms_List->getHead(); // get root
			destruct_list(destruct_listNode); // desturct termlist node;

			MemberQueueNode* destruct_qNode;
			destruct_qNode = Member_Q->front(); // get root
			destruct_q(destruct_qNode); // desturct q node;

			// delete
			delete Member_Q; 
			delete Terms_List;
			delete Terms_BST;
			delete Name_BST;

			PrintSuccess(input_cmd); // function success
			exit(0); // end
		} else { // other strange operation
			PrintErrorCode(1000); 
		}
	}	

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd) // operation complete log function
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;

}
void Manager::PrintErrorCode(int num) // File error function
{ 
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD(const char* cmd) {
	ifstream Load_Data;
	string name, date, terms_type;
	int age;	
	Load_Data.open("data.txt"); // data.txt open

	if(!Load_Data) PrintErrorCode(100); // data.txt not exist
	else if(Load_Data) { // exist 
		flog << "=====" << cmd << "=====" << endl; // flog
		while(Load_Data >> name >> age >> date >> terms_type) {	// Repeat until done
			Member_Q->push(name, age, date, terms_type); // push to Queue
			flog << name << "/" << age << "/" << date << "/" << terms_type << endl;		
		}
		Load_Data.close(); // data.txt close
		flog << "==============" << endl << endl;
	}
}

// ADD o
void Manager::ADD(const char* cmd, string name, int age, string date, string terms_type) {
	Member_Q->push(name, age, date, terms_type); // push to Queue 
	flog << "=====" << cmd << "=====" << endl; // flog
	flog << name << "/" << age << "/" << date << "/" << terms_type << endl;
	flog << "==============" << endl << endl;
}

// QPOP o
void Manager::QPOP(const char* cmd) {
	while(1) {
		if(Member_Q->empty() == 1) { // if queue is empty  
			exit(-1);
			break; // escape
		} else if(Member_Q->empty() == 0) { // queue is not empty  
			MemberQueueNode* Q_node = Member_Q->pop(); 
			if(Q_node->get_next() != nullptr) { // q_node is not last node in queue
				Terms_List->insert(Q_node); // insert termsList
				if(Name_BST->getRoot() == nullptr) Name_BST->setRoot(Q_node); // nameBST is empty, so Determine root with qnode
				else if(Name_BST->getRoot() != nullptr) Name_BST->insert(Name_BST->getRoot(), Q_node); // nameBST is not empty, so insert
			} else if(Q_node->get_next() == nullptr) { // q_node is last node in queue
				Terms_List->insert(Q_node); // insert termsList
				if(Name_BST->getRoot() == nullptr) Name_BST->setRoot(Q_node); // nameBST is empty, so Determine root with qnode
				else if(Name_BST->getRoot() != nullptr) Name_BST->insert(Name_BST->getRoot(), Q_node); // nameBST is not empty, so insert
				PrintSuccess(cmd); // flog
				break; // escape
			}
		}
	}
}
	
// SEARCH o
void Manager::SEARCH(const char* cmd, string name) {
	NameBSTNode* Name_cur_node = Name_BST->getRoot(); // get Root node

	if(Name_cur_node != nullptr) { // NameBST is not empty
		int found = Name_BST->search(Name_cur_node, name); // if found = 1 set, name is exist
		
		if(found == 1) {
			flog << "=====" << cmd << "=====" << endl; // flog
			Name_BST->search_print(Name_cur_node, name, flog);
			flog << "==============" << endl << endl;
		} else if(found == 0) PrintErrorCode(400); // name is not exists
	} else if(Name_cur_node == nullptr) PrintErrorCode(400); // empty NameBST
	
} 

// PRINT o
void Manager::PRINT(const char* cmd, string type) {
	int found = 0; // if found is set, exist
	TermsListNode* Terms_cur_node = Terms_List->getHead(); // get head node
	NameBSTNode* Name_cur_node = Name_BST->getRoot(); // get root node

	if(type == "NAME") {
		if(Name_cur_node != nullptr) { // Name_BST is not empty
			flog << "=====" << cmd << "=====" << endl; // flog
			flog << "Name_BST" << endl;
			Name_BST->print(Name_cur_node, flog);
			flog << "==============" << endl << endl;
		}
		else if(Name_cur_node == nullptr) PrintErrorCode(500); // Name is empty 
	} else if(type != "NAME") {	// type
		while(Terms_cur_node != nullptr) { // not empty
			if(Terms_cur_node->getListType() == type) {
				found = 1;
				TermsBSTNode* BST_node = Terms_cur_node->getBSTNode(); // flog
				flog << "=====" << cmd << "=====" << endl;
				flog << "Terms_BST " << type << endl;
				Terms_BST->print(BST_node, flog);
				flog << "==============" << endl << endl;
			}
			Terms_cur_node = Terms_cur_node->getNext(); // get next node
		}
		if(found == 0) PrintErrorCode(500); // empty term_type BST
	}
}

// DELETE o
void Manager::DELETE(const char* cmd, string type, string data) {
	if(type == "DATE") { // Terms delete -> Name_BST delete
		vector<string> remove_node;
		remove_node = Terms_List->remove_date(data); // terms delete
		if(remove_node.size() == 0) PrintErrorCode(600); // no member in vector
		else if(remove_node.size() != 0) { // member in vector
			for(string node: remove_node) Name_BST->remove_name(node); // nameBST delete
			PrintSuccess(cmd);
		}
	} else if(type == "NAME") { // Name_BST delete -> Terms delete
		NameBSTNode* Name_cur_node = Name_BST->getRoot(); // get root
		int found = Name_BST->search(Name_cur_node, data); // if found == 1, exist
		if(found == 0) PrintErrorCode(600); // Name not found
		else if(found != 0) { // Name found
			vector<string> remove_node;
			remove_node = Name_BST->remove(data); // nameBST delete
			for(string node: remove_node) Terms_List->remove_name(data, node); // terms delete
			PrintSuccess(cmd);
		}
	}
}

// EXIT
void Manager::destruct_name(NameBSTNode* node) {
	if(node == nullptr) return; // if node is null return

	// postorder traverse
	destruct_name(node->getLeft()); // left destruct
	destruct_name(node->getRight()); // right destruct
	delete node;
}
void Manager::destruct_term(TermsBSTNode* node) {
	if(node == nullptr) return; // if node is null return

	// postorder traverse
	destruct_term(node->getLeft()); // left destruct
	destruct_term(node->getRight()); // right destruct
	delete node;
}
void Manager::destruct_list(TermsListNode* node) {
	if(node == nullptr) return; // if node is null return

	destruct_list(node->getNext()); // traverse
	delete node;
}
void Manager::destruct_q(MemberQueueNode* node) {
	if(node == nullptr) return; // if node is null return

	destruct_q(node->get_next()); // traverse 
	delete node;
}