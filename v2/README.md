# 📤 Project 2: Data Structure Implementation (using B+Tree, Selection Tree, Min Heap)

## 📘 Overview
    This project implements a system based on B+ Tree, Selection Tree (Min Winner Tree), and Min Heap.
    Using these data structures, the system processes the following commands: LOAD, ADD, SEARCH_BP, PRINT_BP, PRINT_ST, DELETE, and EXIT.

    All commands are read from command.txt, and initial data is loaded from loan_book.txt.
    BookData does not allow duplicate entries, and data comparisons are case-insensitive.

- **LOAD**
    - Applies to: `B+ Tree`
    - Reads data from `loan_book.txt` and inserts it into the `B+ Tree`.
    Each record consists of the following fields: book title / classification code / author / year / loan count.
    
    - Execution Rules
        - Can only be executed when the B+ Tree is empty
        - The `loan_book.txt` file must exist
    
    - Error Handling
        - If the file does not exist, or
        - If the B+ Tree already contains data  
          → Error code `100` is printed.
    
    - Success Behavior
        - All data is stored in the B+ Tree in ascending order
 
- **ADD**
    - Applies to: `B+ Tree → Selection Tree → Min Heap`
    - Adds new book data to the B+ Tree.
    If the book already exists, the loan count is increased.
    
    - Arguments
        - Book Name
        - Classification Code
        - Author
        - Year

    - Execution Rules
        - All arguments must be provided correctly
        - If the book already exists, its `loan_count` is increased
        - When `loan_count` reaches the threshold for its classification code:
            - The data is deleted from the B+ Tree
            - It is passed through the Selection Tree
            - Then moved to the corresponding Min Heap

    - Error Handling
        - If the number of arguments is insufficient or excessive  
          → Error code `200` is printed.

    - Success Behavior
        - Data is successfully inserted or moved as required
 
- **SEARCH_BP**
    - Applies to: `B+ Tree`
    - Searches for data stored in the B+ Tree.

    - Execution Rules
        - One argument: search for a specific book name
        - Two arguments: range search from start keyword to end keyword

    - Error Handling
        - If the number of arguments is not 1 or 2
        - If no matching data is found  
          → Error code `300` is printed.

    - Success Behavior
        - Data that satisfies the search conditions is printed
 
- **PRINT_BP**
    - Applies to: `B+ Tree`
    - Prints all data stored in the B+ Tree in ascending order.

    - Execution Rules
        - Data is printed sequentially starting from the left-most data node

    - Error Handling
        - If there is no data to print  
          → Error code `400` is printed.

- **PRINT_ST**
    - Applies to: `Selection Tree → Min Heap`
    - Prints data from the Min Heap corresponding to the given classification code.

    - Execution Rules
        - Traverses the Selection Tree to locate the corresponding Min Heap
        - Data in the Min Heap is printed in ascending order based on book name

    - Error Handling
        - If the Min Heap for the given classification code is empty  
          → Error code `500` is printed.
         
- **DELETE**
    - Applies to: `Selection Tree → Min Heap`
    - Deletes the root of the Selection Tree (the minimum value).
      The root of the corresponding Min Heap is removed and the structures are reorganized.

    - Execution Rules
        - Follows Min Winner Tree properties to trace and delete down to the leaf
        - The Min Heap is reordered using heapify-down
        - The Selection Tree root is reconstructed afterward

    - Success Behavior
        - The data with the smallest value is removed from the system

- **EXIT**
    - Applies to: `Manager (B+ Tree, Selection Tree, Min Heap)`
    - Releases all dynamically allocated memory before program termination.

    - Cleanup Procedure
        - Calls destructors for the B+ Tree, Selection Tree, and Min Heap
        - Deletes all nodes and then deallocates the data structures themselves

    - Success Behavior
        - Prints a success message and terminates the program
      
## 🧾 Conclusion
    이번 프로젝트는 **B+ Tree**를 중심으로 **Selection Tree**와 **Min Heap**을 연계하여  
    데이터의 저장, 검색, 이동, 삭제를 효율적으로 수행하도록 설계되었다.  

    각 명령어는 명확한 조건과 에러 처리를 기반으로 구현되었으며,  
    복합 자료구조 간의 연동과 **메모리 관리**에 대한 이해를 심화할 수 있었다.
