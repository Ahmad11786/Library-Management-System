
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ============================================================
// LIBRARY MANAGEMENT SYSTEM
// C++ OOP PROJECT - BSCS 3RD SEMESTER
//
// Concepts:
// Classes, Objects, Encapsulation, Constructors,
// Inheritance, Abstraction, Virtual Functions,
// Runtime Polymorphism, Function Overloading,
// Composition, Arrays and File Handling
// ============================================================

const int MAX_BOOKS = 200;
const int MAX_STUDENTS = 200;
const int MAX_ISSUES = 500;
const int LOAN_DAYS = 14;
const int FINE_PER_DAY = 10;

// ============================================================
// INPUT FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

int getInteger(string message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            clearInput();
            return value;
        }

        cout << "\nInvalid input! Please enter a number.\n";
        clearInput();
    }
}

string getText(string message)
{
    string value;

    cout << message;
    getline(cin, value);

    while (value.empty())
    {
        cout << "This field cannot be empty. Try again: ";
        getline(cin, value);
    }

    return value;
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

void heading(string title)
{
    cout << "\n";
    cout << "============================================================\n";
    cout << "                  " << title << "\n";
    cout << "============================================================\n";
}

// ============================================================
// BOOK CLASS
// ============================================================

class Book
{
private:

    int bookID;
    string title;
    string author;
    string category;
    int totalCopies;
    int availableCopies;

public:

    Book()
    {
        bookID = 0;
        totalCopies = 0;
        availableCopies = 0;
    }

    Book(int id, string t, string a, string c, int copies)
    {
        bookID = id;
        title = t;
        author = a;
        category = c;
        totalCopies = copies;
        availableCopies = copies;
    }

    int getID()
    {
        return bookID;
    }

    string getTitle()
    {
        return title;
    }

    int getAvailable()
    {
        return availableCopies;
    }

    int getTotal()
    {
        return totalCopies;
    }

    void updateBook(string t, string a, string c, int copies)
    {
        int issuedCopies = totalCopies - availableCopies;

        title = t;
        author = a;
        category = c;

        totalCopies = copies;
        availableCopies = copies - issuedCopies;
    }

    bool issueBook()
    {
        if (availableCopies > 0)
        {
            availableCopies--;
            return true;
        }

        return false;
    }

    void returnBook()
    {
        if (availableCopies < totalCopies)
        {
            availableCopies++;
        }
    }

    void display()
    {
        cout << left
             << setw(8) << bookID
             << setw(25) << title.substr(0, 23)
             << setw(20) << author.substr(0, 18)
             << setw(16) << category.substr(0, 14)
             << setw(10) << totalCopies
             << setw(10) << availableCopies
             << "\n";
    }

    void save(ofstream &file)
    {
        file << bookID << "|"
             << title << "|"
             << author << "|"
             << category << "|"
             << totalCopies << "|"
             << availableCopies << "\n";
    }

    void load(string line)
    {
        stringstream ss(line);
        string value;

        getline(ss, value, '|');
        bookID = stoi(value);

        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');

        getline(ss, value, '|');
        totalCopies = stoi(value);

        getline(ss, value, '|');
        availableCopies = stoi(value);
    }
};

// ============================================================
// ABSTRACT PERSON CLASS
// ============================================================

class Person
{
protected:

    string name;
    string phone;

public:

    Person()
    {
        name = "";
        phone = "";
    }

    Person(string n, string p)
    {
        name = n;
        phone = p;
    }

    virtual void display() = 0;

    virtual ~Person()
    {
    }
};

// ============================================================
// STUDENT CLASS - INHERITANCE
// ============================================================

class Student : public Person
{
private:

    int studentID;
    string department;

public:

    Student() : Person()
    {
        studentID = 0;
        department = "";
    }

    Student(int id, string n, string d, string p)
        : Person(n, p)
    {
        studentID = id;
        department = d;
    }

    int getID()
    {
        return studentID;
    }

    string getName()
    {
        return name;
    }

    void display() override
    {
        cout << left
             << setw(12) << studentID
             << setw(25) << name.substr(0, 23)
             << setw(20) << department.substr(0, 18)
             << setw(16) << phone.substr(0, 14)
             << "\n";
    }

    void save(ofstream &file)
    {
        file << studentID << "|"
             << name << "|"
             << department << "|"
             << phone << "\n";
    }

    void load(string line)
    {
        stringstream ss(line);
        string value;

        getline(ss, value, '|');
        studentID = stoi(value);

        getline(ss, name, '|');
        getline(ss, department, '|');
        getline(ss, phone, '|');
    }
};

// ============================================================
// ISSUE RECORD CLASS
// ============================================================

class IssueRecord
{
private:

    int issueID;
    int bookID;
    int studentID;
    int issueDay;
    int dueDay;
    int returnDay;
    int fine;

public:

    IssueRecord()
    {
        issueID = 0;
        bookID = 0;
        studentID = 0;
        issueDay = 0;
        dueDay = 0;
        returnDay = 0;
        fine = 0;
    }

    IssueRecord(int iid, int bid, int sid, int day)
    {
        issueID = iid;
        bookID = bid;
        studentID = sid;
        issueDay = day;
        dueDay = day + LOAN_DAYS;
        returnDay = 0;
        fine = 0;
    }

    int getIssueID()
    {
        return issueID;
    }

    int getBookID()
    {
        return bookID;
    }

    int getStudentID()
    {
        return studentID;
    }

    int getDueDay()
    {
        return dueDay;
    }

    int getReturnDay()
    {
        return returnDay;
    }

    int getFine()
    {
        return fine;
    }

    bool isActive()
    {
        return returnDay == 0;
    }

    void completeReturn(int day)
    {
        returnDay = day;

        int overdueDays = day - dueDay;

        if (overdueDays > 0)
        {
            fine = overdueDays * FINE_PER_DAY;
        }
    }

    void display()
    {
        cout << left
             << setw(10) << issueID
             << setw(10) << bookID
             << setw(12) << studentID
             << setw(12) << issueDay
             << setw(12) << dueDay;

        if (returnDay == 0)
        {
            cout << setw(14) << "Not Returned";
        }
        else
        {
            cout << setw(14) << returnDay;
        }

        cout << setw(10) << fine << "\n";
    }

    void save(ofstream &file)
    {
        file << issueID << "|"
             << bookID << "|"
             << studentID << "|"
             << issueDay << "|"
             << dueDay << "|"
             << returnDay << "|"
             << fine << "\n";
    }

    void load(string line)
    {
        stringstream ss(line);
        string value;

        getline(ss, value, '|');
        issueID = stoi(value);

        getline(ss, value, '|');
        bookID = stoi(value);

        getline(ss, value, '|');
        studentID = stoi(value);

        getline(ss, value, '|');
        issueDay = stoi(value);

        getline(ss, value, '|');
        dueDay = stoi(value);

        getline(ss, value, '|');
        returnDay = stoi(value);

        getline(ss, value, '|');
        fine = stoi(value);
    }
};

// ============================================================
// LIBRARY CLASS - COMPOSITION
// ============================================================

class Library
{
private:

    Book books[MAX_BOOKS];
    Student students[MAX_STUDENTS];
    IssueRecord issues[MAX_ISSUES];

    int bookCount;
    int studentCount;
    int issueCount;

    // --------------------------------------------------------
    // SEARCH FUNCTIONS
    // --------------------------------------------------------

    int findBook(int id)
    {
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].getID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    int findStudent(int id)
    {
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].getID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    int findIssue(int id)
    {
        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].getIssueID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    bool hasActiveIssueForBook(int id)
    {
        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].getBookID() == id && issues[i].isActive())
            {
                return true;
            }
        }

        return false;
    }

    bool hasActiveIssueForStudent(int id)
    {
        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].getStudentID() == id && issues[i].isActive())
            {
                return true;
            }
        }

        return false;
    }

    // --------------------------------------------------------
    // FILE HANDLING
    // --------------------------------------------------------

    void saveBooks()
    {
        ofstream file("books.txt");

        for (int i = 0; i < bookCount; i++)
        {
            books[i].save(file);
        }

        file.close();
    }

    void saveStudents()
    {
        ofstream file("students.txt");

        for (int i = 0; i < studentCount; i++)
        {
            students[i].save(file);
        }

        file.close();
    }

    void saveIssues()
    {
        ofstream file("issues.txt");

        for (int i = 0; i < issueCount; i++)
        {
            issues[i].save(file);
        }

        file.close();
    }

    void saveAll()
    {
        saveBooks();
        saveStudents();
        saveIssues();
    }

    void loadBooks()
    {
        ifstream file("books.txt");
        string line;

        while (getline(file, line))
        {
            if (bookCount < MAX_BOOKS && !line.empty())
            {
                books[bookCount].load(line);
                bookCount++;
            }
        }

        file.close();
    }

    void loadStudents()
    {
        ifstream file("students.txt");
        string line;

        while (getline(file, line))
        {
            if (studentCount < MAX_STUDENTS && !line.empty())
            {
                students[studentCount].load(line);
                studentCount++;
            }
        }

        file.close();
    }

    void loadIssues()
    {
        ifstream file("issues.txt");
        string line;

        while (getline(file, line))
        {
            if (issueCount < MAX_ISSUES && !line.empty())
            {
                issues[issueCount].load(line);
                issueCount++;
            }
        }

        file.close();
    }

    int nextBookID()
    {
        int maximum = 1000;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].getID() > maximum)
            {
                maximum = books[i].getID();
            }
        }

        return maximum + 1;
    }

    int nextStudentID()
    {
        int maximum = 100;

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].getID() > maximum)
            {
                maximum = students[i].getID();
            }
        }

        return maximum + 1;
    }

    int nextIssueID()
    {
        int maximum = 0;

        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].getIssueID() > maximum)
            {
                maximum = issues[i].getIssueID();
            }
        }

        return maximum + 1;
    }

    // --------------------------------------------------------
    // BOOK MANAGEMENT
    // --------------------------------------------------------

    void addBook()
    {
        heading("ADD NEW BOOK");

        if (bookCount >= MAX_BOOKS)
        {
            cout << "Book storage is full!\n";
            return;
        }

        int id = nextBookID();

        string title = getText("Enter Book Title: ");
        string author = getText("Enter Author Name: ");
        string category = getText("Enter Category: ");

        int copies = getInteger("Enter Number of Copies: ");

        if (copies <= 0)
        {
            cout << "\nInvalid number of copies!\n";
            return;
        }

        books[bookCount] = Book(id, title, author, category, copies);
        bookCount++;

        saveBooks();

        cout << "\nBook added successfully!\n";
        cout << "Generated Book ID: " << id << "\n";
    }

    void viewBooks()
    {
        heading("ALL LIBRARY BOOKS");

        if (bookCount == 0)
        {
            cout << "No books available.\n";
            return;
        }

        cout << left
             << setw(8) << "ID"
             << setw(25) << "TITLE"
             << setw(20) << "AUTHOR"
             << setw(16) << "CATEGORY"
             << setw(10) << "TOTAL"
             << setw(10) << "AVAILABLE"
             << "\n";

        cout << string(89, '-') << "\n";

        for (int i = 0; i < bookCount; i++)
        {
            books[i].display();
        }
    }

    void updateBook()
    {
        heading("UPDATE BOOK");

        int id = getInteger("Enter Book ID: ");

        int index = findBook(id);

        if (index == -1)
        {
            cout << "\nBook not found!\n";
            return;
        }

        cout << "\nEnter New Book Information\n";

        string title = getText("New Title: ");
        string author = getText("New Author: ");
        string category = getText("New Category: ");

        int copies = getInteger("New Total Copies: ");

        if (copies <= 0 || copies < books[index].getTotal() - books[index].getAvailable())
        {
            cout << "\nInvalid copies! Total cannot be less than issued copies.\n";
            return;
        }

        books[index].updateBook(title, author, category, copies);

        saveBooks();

        cout << "\nBook updated successfully!\n";
    }

    void deleteBook()
    {
        heading("DELETE BOOK");

        int id = getInteger("Enter Book ID: ");

        int index = findBook(id);

        if (index == -1)
        {
            cout << "\nBook not found!\n";
            return;
        }

        if (hasActiveIssueForBook(id))
        {
            cout << "\nCannot delete! This book has active issue records.\n";
            return;
        }

        cout << "\nBook: " << books[index].getTitle() << "\n";

        string confirm = getText("Type YES to confirm deletion: ");

        if (confirm != "YES")
        {
            cout << "\nDeletion cancelled.\n";
            return;
        }

        for (int i = index; i < bookCount - 1; i++)
        {
            books[i] = books[i + 1];
        }

        bookCount--;

        saveBooks();

        cout << "\nBook deleted successfully!\n";
    }

    // --------------------------------------------------------
    // SEARCH BOOK - FUNCTION OVERLOADING
    // --------------------------------------------------------

    void searchBook(int id)
    {
        int index = findBook(id);

        if (index == -1)
        {
            cout << "\nBook not found!\n";
            return;
        }

        heading("BOOK SEARCH RESULT");

        cout << left
             << setw(8) << "ID"
             << setw(25) << "TITLE"
             << setw(20) << "AUTHOR"
             << setw(16) << "CATEGORY"
             << setw(10) << "TOTAL"
             << setw(10) << "AVAILABLE"
             << "\n";

        cout << string(89, '-') << "\n";

        books[index].display();
    }

    void searchBook(string title)
    {
        bool found = false;

        heading("BOOK SEARCH RESULTS");

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].getTitle().find(title) != string::npos)
            {
                if (!found)
                {
                    cout << left
                         << setw(8) << "ID"
                         << setw(25) << "TITLE"
                         << setw(20) << "AUTHOR"
                         << setw(16) << "CATEGORY"
                         << setw(10) << "TOTAL"
                         << setw(10) << "AVAILABLE"
                         << "\n";

                    cout << string(89, '-') << "\n";
                }

                books[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No matching books found.\n";
        }
    }

    void searchBooksMenu()
    {
        heading("SEARCH BOOKS");

        cout << "1. Search by Book ID\n";
        cout << "2. Search by Book Title\n";

        int choice = getInteger("\nEnter Choice: ");

        if (choice == 1)
        {
            int id = getInteger("Enter Book ID: ");
            searchBook(id);
        }
        else if (choice == 2)
        {
            string title = getText("Enter Book Title or Keyword: ");
            searchBook(title);
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }

    // --------------------------------------------------------
    // STUDENT MANAGEMENT
    // --------------------------------------------------------

    void addStudent()
    {
        heading("REGISTER NEW STUDENT");

        if (studentCount >= MAX_STUDENTS)
        {
            cout << "Student storage is full!\n";
            return;
        }

        int id = nextStudentID();

        string name = getText("Enter Student Name: ");
        string department = getText("Enter Department: ");
        string phone = getText("Enter Phone Number: ");

        students[studentCount] = Student(id, name, department, phone);

        studentCount++;

        saveStudents();

        cout << "\nStudent registered successfully!\n";
        cout << "Generated Student ID: " << id << "\n";
    }

    void viewStudents()
    {
        heading("REGISTERED STUDENTS");

        if (studentCount == 0)
        {
            cout << "No students registered.\n";
            return;
        }

        cout << left
             << setw(12) << "STUDENT ID"
             << setw(25) << "NAME"
             << setw(20) << "DEPARTMENT"
             << setw(16) << "PHONE"
             << "\n";

        cout << string(73, '-') << "\n";

        for (int i = 0; i < studentCount; i++)
        {
            students[i].display();
        }
    }

    void searchStudent()
    {
        heading("SEARCH STUDENT");

        int id = getInteger("Enter Student ID: ");

        int index = findStudent(id);

        if (index == -1)
        {
            cout << "\nStudent not found!\n";
            return;
        }

        cout << "\nStudent Record Found:\n";

        cout << left
             << setw(12) << "STUDENT ID"
             << setw(25) << "NAME"
             << setw(20) << "DEPARTMENT"
             << setw(16) << "PHONE"
             << "\n";

        cout << string(73, '-') << "\n";

        // Runtime polymorphism through the base class pointer
        Person* person = &students[index];
        person->display();
    }

    // --------------------------------------------------------
    // ISSUE BOOK
    // --------------------------------------------------------

    void issueBook()
    {
        heading("ISSUE BOOK");

        if (issueCount >= MAX_ISSUES)
        {
            cout << "Issue record storage is full!\n";
            return;
        }

        if (bookCount == 0 || studentCount == 0)
        {
            cout << "You need at least one book and one registered student.\n";
            return;
        }

        int studentID = getInteger("Enter Student ID: ");

        int studentIndex = findStudent(studentID);

        if (studentIndex == -1)
        {
            cout << "\nStudent not registered!\n";
            return;
        }

        int bookID = getInteger("Enter Book ID: ");

        int bookIndex = findBook(bookID);

        if (bookIndex == -1)
        {
            cout << "\nBook not found!\n";
            return;
        }

        if (books[bookIndex].getAvailable() <= 0)
        {
            cout << "\nSorry! This book is currently unavailable.\n";
            return;
        }

        int issueDay = getInteger("Enter Today's Day Number: ");

        if (issueDay <= 0)
        {
            cout << "\nInvalid day number!\n";
            return;
        }

        books[bookIndex].issueBook();

        int id = nextIssueID();

        issues[issueCount] = IssueRecord(id, bookID, studentID, issueDay);

        issueCount++;

        saveAll();

        cout << "\n";
        cout << "============================================================\n";
        cout << "                  BOOK ISSUED SUCCESSFULLY\n";
        cout << "============================================================\n";

        cout << "Issue ID       : " << id << "\n";
        cout << "Student Name   : " << students[studentIndex].getName() << "\n";
        cout << "Book Name      : " << books[bookIndex].getTitle() << "\n";
        cout << "Issue Day      : " << issueDay << "\n";
        cout << "Due Day        : " << issueDay + LOAN_DAYS << "\n";

        cout << "============================================================\n";
    }

    // --------------------------------------------------------
    // RETURN BOOK
    // --------------------------------------------------------

    void returnBook()
    {
        heading("RETURN BOOK");

        int id = getInteger("Enter Issue ID: ");

        int index = findIssue(id);

        if (index == -1)
        {
            cout << "\nIssue record not found!\n";
            return;
        }

        if (!issues[index].isActive())
        {
            cout << "\nThis book has already been returned.\n";
            return;
        }

        int returnDay = getInteger("Enter Today's Day Number: ");

        if (returnDay < issues[index].getDueDay() - LOAN_DAYS)
        {
            cout << "\nInvalid return date!\n";
            return;
        }

        if (returnDay <= 0)
        {
            cout << "\nInvalid day number!\n";
            return;
        }

        int bookIndex = findBook(issues[index].getBookID());

        if (bookIndex == -1)
        {
            cout << "\nBook record is missing! Contact administrator.\n";
            return;
        }

        issues[index].completeReturn(returnDay);

        books[bookIndex].returnBook();

        saveAll();

        cout << "\n";
        cout << "============================================================\n";
        cout << "                  BOOK RETURNED SUCCESSFULLY\n";
        cout << "============================================================\n";

        cout << "Issue ID       : " << id << "\n";
        cout << "Book Name      : " << books[bookIndex].getTitle() << "\n";
        cout << "Due Day        : " << issues[index].getDueDay() << "\n";
        cout << "Return Day     : " << returnDay << "\n";

        cout << "Fine Amount    : Rs. "
             << issues[index].getFine() << "\n";

        if (issues[index].getFine() > 0)
        {
            cout << "\nPlease collect the overdue fine.\n";
        }
        else
        {
            cout << "\nNo fine! Book returned on time.\n";
        }

        cout << "============================================================\n";
    }

    // --------------------------------------------------------
    // ISSUE RECORDS
    // --------------------------------------------------------

    void viewIssuedBooks()
    {
        heading("ALL ISSUE RECORDS");

        if (issueCount == 0)
        {
            cout << "No issue records found.\n";
            return;
        }

        cout << left
             << setw(10) << "ISSUE ID"
             << setw(10) << "BOOK ID"
             << setw(12) << "STUDENT ID"
             << setw(12) << "ISSUE DAY"
             << setw(12) << "DUE DAY"
             << setw(14) << "RETURN DAY"
             << setw(10) << "FINE"
             << "\n";

        cout << string(80, '-') << "\n";

        for (int i = 0; i < issueCount; i++)
        {
            issues[i].display();
        }
    }

    void viewActiveIssues()
    {
        heading("CURRENTLY ISSUED BOOKS");

        bool found = false;

        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].isActive())
            {
                if (!found)
                {
                    cout << left
                         << setw(10) << "ISSUE ID"
                         << setw(10) << "BOOK ID"
                         << setw(12) << "STUDENT ID"
                         << setw(12) << "ISSUE DAY"
                         << setw(12) << "DUE DAY"
                         << setw(14) << "RETURN DAY"
                         << setw(10) << "FINE"
                         << "\n";

                    cout << string(80, '-') << "\n";
                }

                issues[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books are currently issued.\n";
        }
    }

    // --------------------------------------------------------
    // DASHBOARD
    // --------------------------------------------------------

    void dashboard()
    {
        heading("LIBRARY DASHBOARD");

        int totalCopies = 0;
        int availableCopies = 0;
        int issuedBooks = 0;
        int returnedBooks = 0;
        int totalFines = 0;

        for (int i = 0; i < bookCount; i++)
        {
            totalCopies += books[i].getTotal();
            availableCopies += books[i].getAvailable();
        }

        for (int i = 0; i < issueCount; i++)
        {
            if (issues[i].isActive())
            {
                issuedBooks++;
            }
            else
            {
                returnedBooks++;
                totalFines += issues[i].getFine();
            }
        }

        cout << "\n";
        cout << "                 LIBRARY STATISTICS\n";
        cout << "------------------------------------------------------------\n";

        cout << left << setw(35) << "Total Book Titles:"
             << bookCount << "\n";

        cout << left << setw(35) << "Total Book Copies:"
             << totalCopies << "\n";

        cout << left << setw(35) << "Available Book Copies:"
             << availableCopies << "\n";

        cout << left << setw(35) << "Registered Students:"
             << studentCount << "\n";

        cout << left << setw(35) << "Currently Issued Books:"
             << issuedBooks << "\n";

        cout << left << setw(35) << "Returned Books:"
             << returnedBooks << "\n";

        cout << left << setw(35) << "Total Issue Transactions:"
             << issueCount << "\n";

        cout << left << setw(35) << "Total Recorded Fines:"
             << "Rs. " << totalFines << "\n";

        cout << "------------------------------------------------------------\n";
    }

public:

    // --------------------------------------------------------
    // LIBRARY CONSTRUCTOR
    // --------------------------------------------------------

    Library()
    {
        bookCount = 0;
        studentCount = 0;
        issueCount = 0;

        loadBooks();
        loadStudents();
        loadIssues();
    }

    // --------------------------------------------------------
    // BOOK MENU
    // --------------------------------------------------------

    void bookMenu()
    {
        int choice;

        do
        {
            heading("BOOK MANAGEMENT");

            cout << "1. Add New Book\n";
            cout << "2. View All Books\n";
            cout << "3. Update Book\n";
            cout << "4. Delete Book\n";
            cout << "5. Search Book\n";
            cout << "0. Back to Main Menu\n";

            cout << "\n------------------------------------------------------------\n";

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1:
                    addBook();
                    break;

                case 2:
                    viewBooks();
                    break;

                case 3:
                    updateBook();
                    break;

                case 4:
                    deleteBook();
                    break;

                case 5:
                    searchBooksMenu();
                    break;

                case 0:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice! Try again.\n";
            }

            if (choice != 0)
            {
                pauseScreen();
            }

        } while (choice != 0);
    }

    // --------------------------------------------------------
    // STUDENT MENU
    // --------------------------------------------------------

    void studentMenu()
    {
        int choice;

        do
        {
            heading("STUDENT MANAGEMENT");

            cout << "1. Register New Student\n";
            cout << "2. View All Students\n";
            cout << "3. Search Student\n";
            cout << "0. Back to Main Menu\n";

            cout << "\n------------------------------------------------------------\n";

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1:
                    addStudent();
                    break;

                case 2:
                    viewStudents();
                    break;

                case 3:
                    searchStudent();
                    break;

                case 0:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice! Try again.\n";
            }

            if (choice != 0)
            {
                pauseScreen();
            }

        } while (choice != 0);
    }

    // --------------------------------------------------------
    // MAIN APPLICATION
    // --------------------------------------------------------

    void run()
    {
        int choice;

        do
        {
            cout << "\n\n";
            cout << "============================================================\n";
            cout << "                 LIBRARY MANAGEMENT SYSTEM\n";
            cout << "============================================================\n";

            cout << "                   Welcome, Administrator!\n";

            cout << "\n";
            cout << "                       MAIN MENU\n";
            cout << "------------------------------------------------------------\n";

            cout << "  1. Book Management\n";
            cout << "  2. Student Management\n";
            cout << "  3. Issue Book\n";
            cout << "  4. Return Book\n";
            cout << "  5. View Currently Issued Books\n";
            cout << "  6. View All Issue Records\n";
            cout << "  7. View All Books\n";
            cout << "  8. Library Dashboard\n";
            cout << "  0. Exit Application\n";

            cout << "------------------------------------------------------------\n";

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1:
                    bookMenu();
                    break;

                case 2:
                    studentMenu();
                    break;

                case 3:
                    issueBook();
                    break;

                case 4:
                    returnBook();
                    break;

                case 5:
                    viewActiveIssues();
                    break;

                case 6:
                    viewIssuedBooks();
                    break;

                case 7:
                    viewBooks();
                    break;

                case 8:
                    dashboard();
                    break;

                case 0:
                    saveAll();

                    cout << "\n";
                    cout << "============================================================\n";
                    cout << "        Thank you for using Library Management System!\n";
                    cout << "                  All records saved successfully.\n";
                    cout << "============================================================\n";

                    break;

                default:
                    cout << "\nInvalid choice! Please select from the menu.\n";
            }

            if (choice != 0)
            {
                pauseScreen();
            }

        } while (choice != 0);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    Library library;

    library.run();

    return 0;
}
