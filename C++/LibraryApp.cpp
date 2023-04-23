/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

#include "lib/nlohmann/json.hpp"
#include <iostream>

using namespace std;

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
        cout << "7. Exit" << endl;
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
            printBooks();
            break;
        case 6:
            printCopies();
            break;
        case 7:
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
}

void checkoutCopy()
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