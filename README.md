# 🗂️ Complaint Management System

Designed and developed a **Complaint Management System** to handle and organize user complaints efficiently. The project showcases two implementations, each leveraging a different data structure to optimize performance for various operations like insertions, deletions, and searches.

---

## 📁 Project Structure

- `Complaint System Data Structures using AVL.cpp`
  Implements the system using **AVL Trees** for balanced and efficient data access.

- `Complaint System Data Structures Modification using Hash Maps.cpp`
  A **modified version** using **Hash Maps** for faster direct access and simpler data handling.

---

## 🧠 Key Concepts

- **AVL Trees (Balanced Binary Search Tree)**
  Ensures O(log n) time complexity for insertion, deletion, and lookup by maintaining a balanced structure after every operation.

- **Hash Maps (Unordered Map / Hash Table)**
  Enables average-case O(1) access time for complaint lookups using unique identifiers (e.g., complaint ID).

---

## 🚀 Features

- Submit new complaints with user details and description
- Search for complaints by ID or user
- Edit or delete existing complaints
- Display all complaints in sorted order (AVL) or by insertion order (HashMap)
- Efficient memory and time management for large datasets

---

## ⚙️ Tech Stack

- **Language:** C++
- **Data Structures:** AVL Tree, Hash Map (Unordered Map)
- **Paradigm:** Object-Oriented Programming
- **Interface:** Console-based

---

## 🚀 Setup & Build

```bash
# Compile AVL version
g++ -o complaint_avl "Complaint System Data Structures using AVL.cpp" -std=c++11

# Compile HashMap version
g++ -o complaint_hashmap "Complaint System Data Structures Modification using Hash Maps.cpp" -std=c++11
```

```bash
# Run
./complaint_avl
./complaint_hashmap
```

---

## 📊 Performance Comparison

| Operation | AVL Tree | Hash Map |
|---|---|---|
| Insert | O(log n) | O(1) avg |
| Delete | O(log n) | O(1) avg |
| Search | O(log n) | O(1) avg |
| Sorted Display | O(n) | O(n log n) |
| Memory | Higher | Lower |

---

## 🎯 Learning Outcomes

This project helped reinforce:
- Implementation and comparison of advanced data structures
- Balancing performance trade-offs between trees and hash-based maps
- Practical use of insert, delete, and search operations
- Structuring a real-world console application in C++

---

## 👤 Author

**Roll No:** 23L-0527
**Course:** Data Structures — FAST-NUCES
