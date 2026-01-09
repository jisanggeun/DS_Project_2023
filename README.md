# DS_Project_2023
This repository contains **Data Structure course projects (Project 1, 2, and 3)** organized by version. Each project focuses on different core data structures and algorithms, while sharing a common **command-based execution model** and **specification-driven design**.

---

## 📁 Repository Structure

```text
DS_Project_2023
├─ v1
│  ├─ README.md   # Project 1 specification and overview
│  └─ code        # Project 1 source code
├─ v2
│  ├─ README.md   # Project 2 specification and overview
│  └─ code        # Project 2 source code
└─ v3
   ├─ README.md   # Project 3 specification and overview
   └─ code        # Project 3 source code
```

Each version represents an **independent project**, and its README describes the overall design, supported commands, and specifications rather than low-level code details.

---

## 📌 Project Overview

### Project 1 (v1)
**Data Structure Implementation (Queue, List, BST)**

Project 1 implements fundamental data structures—**Queue, List, and Binary Search Tree (BST)**—and integrates them to manage member data through a command-driven manager.

**Key Features**
- Temporary data storage using `MemberQueue`
- `TermsList` connected to multiple type-specific `TermsBST` structures (A/B/C/D)
- Name-based search using `NameBST`
- Safe deletion logic and explicit dynamic memory management

**Main Commands**
- LOAD / ADD / QPOP
- SEARCH / PRINT / DELETE
- EXIT (full memory cleanup)

This project emphasizes **data structure interaction**, **safe deletion**, and **consistency across linked structures**.

---

### Project 2 (v2)
**Advanced Tree Structures (B+ Tree, Selection Tree, Min Heap)**

Project 2 focuses on scalable data handling using **advanced tree-based data structures** and multi-stage data migration.

**Key Features**
- B+ Tree for efficient storage and range search
- Selection Tree (Min Winner Tree) for global minimum management
- Category-based Min Heaps for prioritized data handling
- Automatic data movement when specific conditions are met

**Main Commands**
- LOAD / ADD
- SEARCH_BP / PRINT_BP / PRINT_ST
- DELETE
- EXIT

This project highlights **performance considerations**, **hierarchical data flow**, and **coordinated operation of multiple tree structures**.

---

### Project 3 (v3)
**Graph Algorithm Implementation**

Project 3 implements various **graph algorithms** using both **List Graph** and **Matrix Graph** representations, managed through a unified command interface.

**Key Features**
- Support for Directed and Undirected graphs
- Comparison of adjacency list and adjacency matrix representations
- Graph traversal, minimum spanning tree, and shortest path algorithms
- Custom traversal algorithm (`KWANGWOON`)

**Main Commands**
- LOAD / PRINT
- BFS / DFS
- KRUSKAL
- DIJKSTRA / BELLMAN-FORD / FLOYD
- KWANGWOON
- EXIT

This project focuses on **algorithm applicability based on graph representation** and **centralized management via a GraphManager**.

---

## 🧩 Design Philosophy

- All projects follow a **command-based execution model**.
- Each command has clearly defined execution rules and error-handling conditions.
- Dynamically allocated memory is safely released during the EXIT phase.
- Documentation is written from a **specification-oriented perspective**, not as code walkthroughs.

---

## ✅ How to Use

1. Navigate to the desired version directory (`v1`, `v2`, or `v3`).
2. Read the `README.md` file to understand the project specification.
3. Compile and run the source code in the `code` directory.
4. Test functionality using the provided command input files.

---

## 📚 Summary

This repository demonstrates a **progressive learning path in data structures and algorithms**, starting from fundamental structures (Project 1), advancing to complex tree-based systems (Project 2), and culminating in comprehensive graph algorithm implementations (Project 3).