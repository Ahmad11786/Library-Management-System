# 📚 Library Management System

A console-based **Library Management System** developed using C++ and Object-Oriented Programming (OOP). This project provides an organized way to manage library books, student records, book issuing, returns, and overdue fines.

## 🚀 Features

- **Book Management:** Add, view, update, delete, and search books.
- **Student Management:** Register students, view records, and search students.
- **Book Issuing:** Issue available books to registered students.
- **Book Returns:** Process book returns and update availability.
- **Fine Calculation:** Automatically calculate overdue fines.
- **Issue Records:** View active and completed borrowing transactions.
- **Library Dashboard:** Display library statistics and records.
- **File Handling:** Save and load records automatically.
- **Input Validation:** Handle invalid menu inputs and incorrect entries.

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming
- File Handling
- Arrays
- Functions
- Standard C++ Libraries

## 🧠 OOP Concepts Implemented

- Classes and Objects
- Encapsulation
- Inheritance
- Abstraction
- Polymorphism
- Virtual Functions
- Function Overloading
- Constructors
- Composition

## ⚙️ How to Run

**1. Clone the repository**

```bash
git clone https://github.com/Ahmad11786/Library-Management-System.git
```

**2. Open the project folder**

```bash
cd Library-Management-System
```

**3. Compile the program**

```bash
g++ -std=c++17 LibraryManagementSystem.cpp -o LibraryManagementSystem
```

**4. Run the application**

On Windows:

```bash
LibraryManagementSystem.exe
```

## 💾 Data Storage

The application uses text files to maintain records:

| File | Purpose |
|---|---|
| books.txt | Book records |
| students.txt | Student records |
| issues.txt | Issue and return history |

Records are saved automatically and loaded when the application starts.

## 📋 Library Rules

- Only registered students can borrow books.
- Only available books can be issued.
- Each issue transaction receives a unique ID.
- The borrowing period is 14 days.
- Overdue returns are charged Rs. 10 per day.
- Returned books become available again.

## 🎯 Project Objective

The objective of this project is to apply fundamental C++ programming and Object-Oriented Programming concepts to develop a practical management system with organized workflows and persistent data storage.

## 👨‍💻 Developer

**Muhammad Ahmad**

BS Computer Science Student | 3rd Semester

Interested in C++, Object-Oriented Programming, Software Development, and AI.

---

⭐ If you find this project useful, consider giving the repository a star.

**Developed as an academic C++ OOP project.**
