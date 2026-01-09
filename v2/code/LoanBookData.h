#pragma once

#include <iostream>
#include <cstring>
using namespace std;

class LoanBookData
{
private:
    // Dataset
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    // Constructor
    LoanBookData() { this->loan_count = 0; }
    // Destructor
    ~LoanBookData() {};

    // Set book data
    void setBookData(string name, int code, string author, int year, int loan_count) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
        this->loan_count = loan_count;
    }

    // Set book data (setter)
    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    // Update loan count
    void updateCount() { this->loan_count += 1; }

    // Get book data (getter)
    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
};