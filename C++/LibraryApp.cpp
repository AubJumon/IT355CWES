/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */
#include <iostream>
#include <vector>
#include <string.h>
#include "User.h"
#include "Book.h"

using namespace std;

vector<User> users;

void addUser();
void viewUser(int);

void print_menu()
{
    cout << endl;
    cout << "1. Add book to library" << endl;
    cout << "2. Add user to system" << endl;
    cout << "3. Borrow book" << endl;
    cout << "4. Return book" << endl;
    cout << "5. View user" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

int main()
{
    int choice = 0;

    while (choice != 6)
    {
        int uid_int = 0;
        signed char uid = 0;
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // addBook();
            break;
        case 2:
            addUser();
            break;
        case 3:
            // borrowBook();
            break;
        case 4:
            // returnBook();
            break;
        case 5:
            cout << "Enter User ID: ";
            cin >> uid;
            // CWE-194: Unexpected Sign Extension
            uid_int = static_cast<int>(uid);
            viewUser(uid_int);
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            // CWE-484: omitted Break Statement in Switch
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
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
}