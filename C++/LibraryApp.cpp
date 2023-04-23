/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

#include <iostream>

using namespace std;

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
    // CWE-457: Use of Uninitialized Variable
    int choice = 0;

    while (choice != 6)
    {
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_book();
            break;
        case 2:
            add_user();
            break;
        case 3:
            borrow_book();
            break;
        case 4:
            return_book();
            break;
        case 5:
            signed char uid = 0;
            cout << "Enter User ID: ";
            cin >> uid;
            //CWE-194: Unexpected Sign Extension
            int uid_int = static_cast<int>(uid);
            view_user(uid_int);
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

void add_user() {
    int id;
    string name;
    cout << "Enter user name: ";
    getline(cin, name);

    User user(id, name);
    users.push_back(user);

    cout << "User added to system." << endl;
}


