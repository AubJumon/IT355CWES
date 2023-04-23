/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

#include "lib/nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <string.h>
#include "User.h"
#include "Book.h"

using namespace std;

void addUser();

void viewUser();

void collectionActionPrompt();

void addBook();

void addUser();

void checkoutCopy();

void returnCopy();

void printBooks();

void printCopies();

int main()
{

    collectionActionPrompt();

    return 0;
}

void collectionActionPrompt()
{
    int uid;
    int uid_int;
    /**
     * CWE-192: Integer coercion error. We do not coerce integers to another type in this program which avoids the common weakness.
     * If we had done int choice = a, that would have violated the CWE.
     * This also applies for CWE-704, Incorrect type conversion or cast.
     * */
    int choice = 0;
    while (choice != 7)
    {
        cout << endl;
        cout << "1. Add book to library" << endl;
        cout << "2. Add user to system" << endl;
        cout << "3. Borrow book" << endl;
        cout << "4. Return book" << endl;
        cout << "5. View copies" << endl;
        cout << "6. View books" << endl;
        cout << "7. View user" << endl;
        cout << "8. Exit" << endl;
        cout << endl;
        cout << "Enter choice: ";

        // CWE-242 Use of inherently dangerous function: We do not use strcpy() to copy a string because it is vulnerable to buffer overflows.
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            addUser();
            break;
        case 3:
            checkoutCopy();
            break;
        case 4:
            returnCopy();
            break;
        case 5:
            printCopies();
            break;
        case 6:
            printBooks();
            break;
        case 7:
            cout << "Enter User ID: ";
            cin >> uid;
            // CWE-194: Unexpected Sign Extension
            uid_int = static_cast<int>(uid);
            viewUser(uid_int);
            break;
        case 8:
            cout << "Exiting program." << endl;
            break;
        default:
            // CWE-484: omitted Break Statement in Switch
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

void addBook()
{
    return;
}

void addUser()
{
    static int next_id = 1;
    string name;
    cout << "Enter user name: ";
    getline(cin, name);
    User user(next_id++, name);
    users.push_back(user);
    cout << "User added to system." << endl;
}

void viewUser(int uid)
{
    static int next_id = 1;
    string name;
    cout << "Enter user name: ";
    getline(cin, name);
    User user(next_id++, name);
    users.push_back(user);
    cout << "User added to system." << endl;
}

void checkoutCopy()
{
    static int next_id = 1;
    string name;
    cout << "Enter user name: ";
    getline(cin, name);
    User user(next_id++, name);
    users.push_back(user);
    cout << "User added to system." << endl;
}

void borrowBook()
{
}

void returnCopy()
{
}

void printBooks()
{
}

void printCopies()
{
}