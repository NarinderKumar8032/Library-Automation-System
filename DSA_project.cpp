#include <iostream>
#include <string>
#include <cstdlib>   // for system("cls")
#include <conio.h>   // for getch()

using namespace std;

struct Book {
    string name;
    string author;
    int id;
    Book* next;
};

struct Student {
    string name;
    string email;
    string book;
    string author;
    int id;
    Student* next;
};

// Global pointers
Book* start_lib = nullptr;
Student* start = nullptr;

// Function declarations
Book* initialize_lib(Book*);
Student* book_issue(Student*);
Student* book_return(Student*);
void display(Student*);
Book* delete_book(int);
Book* add_book(string, string, int);
void greetings();
void main_menu();

// ---------------- MAIN ----------------
int main() {
    start_lib = initialize_lib(start_lib);
    greetings();
    main_menu();
    return 0;
}

// ---------------- GREETINGS ----------------
void greetings() {
    cout << "\n\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\t\t\t     *                                      *\n";
    cout << "\t\t\t     *     ----------------------------     *\n";
    cout << "\t\t\t     *      WELCOME TO STUDENT LIBRARY      *\n";
    cout << "\t\t\t     *     ----------------------------     *\n";
    cout << "\t\t\t     *       Faridabad,Haryana, India       *\n";
    cout << "\t\t\t     *       Email: narinder4869@gmail.com  *\n";
    cout << "\t\t\t     *       Contact: 9100000000            *\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\n\n\t\t\t           Press any key to continue: ";
    getch();
}

// ---------------- MAIN MENU ----------------
void main_menu() {
    int choice;
    do {
        cout << "\n\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\t      MAIN MENU:\n";
        cout << "\t\t\t\t     1. ISSUE BOOKS\n";
        cout << "\t\t\t\t     2. RETURN BOOKS\n";
        cout << "\t\t\t\t     3. DISPLAY STUDENT DETAILS\n";
        cout << "\t\t\t\t     4. EXIT\n";
        cout << "\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                start = book_issue(start);
                break;
            case 2:
                start = book_return(start);
                break;
            case 3:
                display(start);
                break;
            case 4:
                exit(0);
            default:
                cout << "\n\t\t\tInvalid Option! Press any key to try again...";
                getch();
        }
    } while (choice != 4);
}

// ---------------- INITIALIZE LIBRARY ----------------
Book* initialize_lib(Book* start) {
    Book* ptr = nullptr;

    Book* new_book1 = new Book{"The Kite Runner", "Khaled Hosseini", 101, nullptr};
    start_lib = new_book1;
    ptr = new_book1;

    Book* new_book2 = new Book{"To Kill A Mockingbird", "Harper Lee", 102, nullptr};
    ptr->next = new_book2;
    ptr = new_book2;

    Book* new_book3 = new Book{"The Alchemist", "Paulo Coelho", 103, nullptr};
    ptr->next = new_book3;
    ptr = new_book3;

    Book* new_book4 = new Book{"Pride And Prejudice", "Jane Austen", 104, nullptr};
    ptr->next = new_book4;
    ptr = new_book4;

    Book* new_book5 = new Book{"A Tale Of Two Cities", "Charles Dickens", 105, nullptr};
    ptr->next = new_book5;

    return start_lib;
}

// ---------------- ISSUE BOOK ----------------
Student* book_issue(Student* start) {
    Book* ptr = start_lib;
    Student* ptr2;
    Student* new_student;
    int id, i = 1, flag = 0;

    if (start_lib == nullptr) {
        cout << "\n\tNo books left in the library to issue!\n";
        return start;
    }

    system("cls");
    cout << "\n\t*************** Books Available: ****************\n";
    while (ptr != nullptr) {
        cout << "\n\tBook " << i++;
        cout << "\n\tTitle: " << ptr->name;
        cout << "\n\tAuthor: " << ptr->author;
        cout << "\n\tBook ID: " << ptr->id << "\n";
        ptr = ptr->next;
    }

    cout << "\nEnter the Book ID to issue: ";
    cin >> id;

    ptr = start_lib;
    while (ptr != nullptr) {
        if (ptr->id == id) {
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }

    if (flag == 1) {
        new_student = new Student;
        cout << "\nEnter Student Name: ";
        cin >> new_student->name;
        cout << "Enter Student Email: ";
        cin >> new_student->email;
        new_student->book = ptr->name;
        new_student->author = ptr->author;
        new_student->id = ptr->id;
        new_student->next = nullptr;

        cout << "\nBook ID " << new_student->id << " issued successfully!\n";

        if (start == nullptr) {
            start = new_student;
        } else {
            ptr2 = start;
            while (ptr2->next != nullptr)
                ptr2 = ptr2->next;
            ptr2->next = new_student;
        }

        start_lib = delete_book(new_student->id);
    } else {
        cout << "\nInvalid Book ID!";
    }

    cout << "\nPress any key to return to main menu...";
    getch();
    system("cls");
    return start;
}

// ---------------- RETURN BOOK ----------------
Student* book_return(Student* start) {
    if (start == nullptr) {
        cout << "\nNo books have been issued yet!\n";
        getch();
        return start;
    }

    int id, flag = 0;
    cout << "\nEnter your Book ID to return: ";
    cin >> id;

    Student* ptr = start;
    Student* preptr = nullptr;

    while (ptr != nullptr) {
        if (ptr->id == id) {
            flag = 1;
            break;
        }
        preptr = ptr;
        ptr = ptr->next;
    }

    if (flag == 1) {
        cout << "\nStudent Name: " << ptr->name;
        cout << "\nEmail: " << ptr->email;
        cout << "\nBook Returned: " << ptr->book;
        cout << "\nBook ID: " << ptr->id << "\n";

        add_book(ptr->book, ptr->author, ptr->id);

        if (ptr == start) {
            start = start->next;
        } else {
            preptr->next = ptr->next;
        }
        delete ptr;

        cout << "\nBook returned successfully!\n";
    } else {
        cout << "\nInvalid Book ID entered!";
    }

    cout << "\nPress any key to return to main menu...";
    getch();
    system("cls");
    return start;
}

// ---------------- DISPLAY STUDENT DETAILS ----------------
void display(Student* start) {
    if (start == nullptr) {
        cout << "\nNo student records available.\n";
    } else {
        Student* ptr = start;
        while (ptr != nullptr) {
            cout << "\n------------------------------------------\n";
            cout << "Student Name: " << ptr->name << endl;
            cout << "Email: " << ptr->email << endl;
            cout << "Book Issued: " << ptr->book << endl;
            cout << "Book ID: " << ptr->id << endl;
            cout << "------------------------------------------\n";
            ptr = ptr->next;
        }
    }
    cout << "\nPress any key to return to main menu...";
    getch();
    system("cls");
}

// ---------------- DELETE BOOK FROM LIB ----------------
Book* delete_book(int id) {
    Book* ptr = start_lib;
    Book* preptr = nullptr;

    if (start_lib == nullptr)
        return start_lib;

    if (start_lib->id == id) {
        start_lib = start_lib->next;
        delete ptr;
        return start_lib;
    }

    while (ptr != nullptr && ptr->id != id) {
        preptr = ptr;
        ptr = ptr->next;
    }

    if (ptr != nullptr) {
        preptr->next = ptr->next;
        delete ptr;
    }
    return start_lib;
}

// ---------------- ADD BOOK TO LIB ----------------
Book* add_book(string bookname, string authorname, int id) {
    Book* new_book = new Book{bookname, authorname, id, nullptr};

    if (start_lib == nullptr) {
        start_lib = new_book;
    } else {
        Book* ptr = start_lib;
        while (ptr->next != nullptr)
            ptr = ptr->next;
        ptr->next = new_book;
    }
    return start_lib;
}

