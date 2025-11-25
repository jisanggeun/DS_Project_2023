# DS_Project_2023
KW Data Structure Project 2023

## 📡 DS_Project 

### 📘 Overview

---

### 📤 1. Project 1: Data Structure Implementation (using Queue, BST, List)
This project involves implementing a queue, a list, a BST connected to the list, and an independent BST, along with their corresponding functions: LOAD, ADD, QPOP, SEARCH, PRINT, DELETE, and EXIT.

- **LOAD**
    - Applies to: `MemberQueue`
    - Reads all data from `data.txt`, creates a `MemberQueueNode` for each entry, and inserts them into the `MemberQueue`.
    - If the data structure already contains data or if `data.txt` does not exist, error code 100 is printed.
 
- **ADD**
    - Applies to: `MemberQueue`
    - Creates a `MemberQueueNode` using the Name/Age/Join-date/Type values provided after the ADD command and inserts it into the `MemberQueue`.
    - If any argument is missing, error code 200 is printed.
    - If the insertion is successful, the information is recorded in `log.txt` in the specified format.
 
- **QPOP**
    - Applies to: `MemberQueue` --> `TermsList`, `TermsBST`, `NameBST`
    - Pops all nodes from the `MemberQueue and uses them to construct the `TermsList`, the corresponding type-specific `TermsBST`, and the `NameBST`.
    - After popping all nodes, the queue size must be 0.
    - If a pop is attempted when the queue is empty, error code 300 is printed.
    - If the queue is not empty, pop operations are repeated until it becomes empty.

---

### 📥 
    
---

### 📨 

---

## 📦 Structure
- `Project 1`
<img width="2523" height="4513" alt="DS_1_Structure" src="https://github.com/user-attachments/assets/75ec2383-2e0b-408c-9bfc-add45452c0df" />


- 

-




## 📊 Results
