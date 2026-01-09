# 📤 Project 1: Data Structure Implementation (using Queue, BST, List)

## 📘 Overview
    This project involves implementing a queue, a list, a BST connected to the list, and an independent BST, along with their corresponding functions: LOAD, ADD, QPOP, SEARCH, PRINT, DELETE, and EXIT.

- **LOAD**
    - Applies to: `MemberQueue`
    - Reads all data from `data.txt`, creates a `MemberQueueNode` for each entry, and inserts them into the `MemberQueue`.
    
    - If the data structure already contains data or if `data.txt` does not exist
        - Error code `100` is printed.
 
- **ADD**
    - Applies to: `MemberQueue`
    - Creates a `MemberQueueNode` using the Name/Age/Join-date/Type values provided after the ADD command and inserts it into the `MemberQueue`.
    
    - If any argument is missing
        - Error code `200` is printed.
    - If the insertion is successful
        - The information is recorded in `log.txt` in the specified format.
 
- **QPOP**
    - Applies to: `MemberQueue` --> `TermsList`, `TermsBST`, `NameBST`
    - Pops all nodes from the `MemberQueue and uses them to construct the `TermsList`, the corresponding type-specific `TermsBST`, and the `NameBST`.
    - After popping all nodes, the queue size must be 0.
    
    - If a pop is attempted when the queue is empty
        - Error code `300` is printed.
    - If the queue is not empty
        - Pop operations are repeated until it becomes empty.
 
- **SEARCH**
    - Applies to: `NameBST`
    - Receives a name as an argument and searches for it in the `NameBST`.
    
    - If the root of the `NameBST` is nullptr
        - It means the tree has no data, so error code `400` is printed.
    - If the root exists
        - The search is performed.
    
    - If the name is not found 
        - The found flag remains 0 and error code `400` is printed.
    - If the name is found
        - The found flag is set to 1 and a success message is printed in the required format.
     
- **PRINT**
    - Applies to: `TermsList`, `TermsBST`, `NameBST`
    - Receives either Name or a type(A, B, C, or D) as its argument.
 
    - If the argument is Name
        - The root of `NameBST` is checked.
        - If the root is nullptr
            - Error code `500` is printed because no data exists.
        - Otherwise
            - An in-order traversal (left --> print --> right) is used to print all data.
    
    - If the argument is a type (A/B/C/D)
        - The program searches through the `TermsList` to find the corresponding `TermBST` for that type.
        - If a matching type is found
            - The nodes are printed following the required format.
        - If no matching type is found after traversing the entire list
            - Error code `500` is printed.
         
- **DELETE**
    - Applies to: `TermsList`, `TermsBST`, `NameBST`
    - Receives either Date or Name as an argument.
 
    1) When deleting by Date
         - Every `TermsBST`(A, B, C, D) is traversed, and all nodes with dates earlier than the given date are deleted.
         - Because multiple nodes may be deleted, all four BSTs are checked.
         - Deleted nodes names are stored in a vector so they can later be removed from the `NameBST`.
             - Names are stored instead of node pointers to avoid invalid pointers. (shallow copy issues)
         - After deletion, the corresponding `TermsList` Node count is reduced, and if the count becomes 0, that list entry is removed.
         - The stored names are then used to delete the matching nodes from the `NameBST`.
         - If the vector is empty (no nodes to delete)
             - Error code `600` is printed.
         - Otherwise
             - A success message is printed.
               
    2) When deleting by Name
         - The `NameBST` is searched first.
             - If the name does not exist
                 - An error code is printed.
             - If the name exists
                 - Deletion proceeds.
         - The deleted node's end date is stored in a vector (not the name), because:
             - Names are unique --> can be used as a key in `NameBST`
             - Dates may be duplicated --> date + name combination ensures correct deletion in `TermsBST`
         - Using the stored end date, the corresponding node is deleted from the `TermsBST`.
         - The related `TermsList` entry decreases its count by 1. (Names are unique, so exactly one node is removed.)
         - A success message is printed following the required format.

- **EXIT**
    - Applies to: `Manager`(BST, List, Queue Cleanup)
    - In the `Manager`, all dynamically allocated data structures are properly freed before program termination.
 
    - For each BST
        - A post-order traversal is performed to delete all nodes.
    - For each List
        - Starting from the head, the program moves through the list using next, deleting each previous node as it progresses.
    - For the Queue
        - Starting from the front, nodes are deleted one by one in the same manner.

    - After all nodes have been deleted, the BST, List, and Queue structures themselves are also deleted.
    - A success message is printed in the required format, and finally exit(0) is executed to terminate the program.
      
## 📦 Structure
- `Project 1: Data Structure Implementation (using Queue, BST, List)` 
<img width="2523" height="4513" alt="DS_1_Structure" src="https://github.com/user-attachments/assets/75ec2383-2e0b-408c-9bfc-add45452c0df" />
