/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

// CWE-195: Signed to Unsigned Conversion error - We don't use unsigned data types in the program, so we never convert from a signed int to an unsigned.
// CWE-467: Use of sizeof() on a pointer type - sizeof() function is avoided, and more efficient methods such as size() are used when needed.
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <filesystem>
#include <algorithm>
#include "Collection.h"

namespace fs = filesystem;
using namespace std;

void addBook(Collection *library);
void addUser(Collection *library);
void collectionActionPrompt(Collection *library);
void checkoutCopy(Collection *library);
void returnCopy(Collection *library);
void printBooks(Collection *library);
void printCopies(Collection *library);
void printUser(Collection *library);
void addCopy(Collection *library);

int main()
{
    string choice;
    string collectionName;
    string collectionFileName;
    int nextCollectionID = 0;
    Collection *library;

    cout << "Welcome to the library!" << endl;
    cout << "Read collection from a file? (y/n)" << endl;
    // CWE-125: Out-of-bounds Read - choice only accepted when a value is entered, does not accept empty string.
    while (choice.empty() || choice.substr(0, 1) != "y" && choice.substr(0, 1) != "n")
    {
        cout << "> ";
        cin >> choice;
        cin.ignore();
        if (choice.substr(0, 1) == "y")
        {
            cout << "Enter the filename:" << endl;
            cout << "> ";
            // CWE-676: Use of Potentially Dangerous Function - cin is a potentially dangerous function; using getLine() helps prevent buffer overflow
            getline(cin, collectionFileName);
            while (!fs::exists(collectionFileName))
            {
                cout << "That file doesn't exist. Please try again or enter -1 to exit." << endl;
                cout << "> ";
                getline(cin, collectionFileName);
                // CWE-482: Comparing Instead of Assigning - string is matched for equality instead of altering value
                if (collectionFileName == "-1")
                {
                    cout << "Goodbye." << endl;
                    exit(0);
                }
            }

            library = new Collection(collectionFileName);
            cout << "AFTER COLLECTION CREATED" << endl;
        }
        else if (choice.substr(0, 1) == "n")
        {
            cout << "Input the name of the collection." << endl;
            cout << "> ";
            cin >> collectionName;
            library = new Collection(nextCollectionID, collectionName);
            nextCollectionID++;
        }

        cout << "Collection " + library->getName() + " created successfully." << endl;
    }

    collectionActionPrompt(library);

    return 0;
}

void collectionActionPrompt(Collection *library)
{
    /**
     * CWE-192: Integer coercion error. We do not coerce integers to another type in this program which avoids the common weakness.
     * If we had done int choice = a, that would have violated the CWE.
     * This also applies for CWE-704, Incorrect type conversion or cast.
     * */
    int choice = 0;
    while (choice != 9)
    {
        cout << endl;
        cout << "1. Add book to system" << endl;
        cout << "2. Add copy to collection" << endl;
        cout << "3. Add user to system" << endl;
        cout << "4. Check out copy" << endl;
        cout << "5. Return copy" << endl;
        cout << "6. View available copies of a book" << endl; // we can move this to view books
        cout << "7. View books" << endl;
        cout << "8. View user" << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "Enter choice: ";

        // CWE-242 Use of inherently dangerous function: We do not use strcpy() to copy a string because it is vulnerable to buffer overflows.
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook(library);
            break;
        case 2:
            addCopy(library);
        case 3:
            addUser(library);
            break;
        case 4:
            checkoutCopy(library);
            break;
        case 5:
            returnCopy(library);
            break;
        case 6:
            printCopies(library);
            break;
        case 7:
            printBooks(library);
            break;
        case 8:
            printUser(library);
            break;
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            // CWE-484: omitted Break Statement in Switch
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

void addBook(Collection *library)
{
    long long isbn;
    int publishedYear;
    string title, author, genre, shortDesc, publisher, binding;

    // Get book information from user
    cout << "Enter ISBN: ";
    cin >> isbn;
    cin.ignore();
    // CWE-787: Out-of-bounds Write - ISBN should only ever be 13 digits, length checking prevents writing value beyond allotted long long length.
    // CWE-120: Buffer copy without checking size of Input (Classic Buffer Overflow) Checks if the input is legnth 13 ensuring an overflowed integer doesn't get used.
    // CWE-126: Buffer Over-read
    string isbn_str = to_string(isbn); // Convert to string for easier manipulation
    if (isbn_str.length() != 13 && isbn_str.substr(0, 3) != "978")
    {
        cout << "Invalid ISBN Entered. Adding book failed." << endl;
        return;
    }
    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    cout << "Enter genre: ";
    getline(cin, genre);

    cout << "Enter short description: ";
    getline(cin, shortDesc);

    cout << "Enter published year: ";
    cin >> publishedYear;
    // CWE-839: Numeric range comparison without minimum check
    if (publishedYear < 1600 || publishedYear > 2023 || cin.fail())
    {
        cout << "Invalid published year. Please enter a year greater than 1600 and less than 2023." << endl;
        return;
    }
    cin.ignore();

    cout << "Enter publisher: ";
    getline(cin, publisher);

    cout << "Enter binding (hardcover or paperback): ";
    getline(cin, binding);
    library->addBook(isbn, title, author, genre, shortDesc, publishedYear, publisher, binding);
    return;
}

void addUser(Collection *library)
{
    static int uid = 1;
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    library->addUser(uid, name);
    uid++;
    return;
}

void printUser(Collection *library)
{
    signed char uid;
    int uid_int;
    cout << "Enter User ID: ";
    cin >> uid;
    cin.ignore();
    // CWE-194: Unexpected Sign Extension - user ID is casted to integer from signed character to prevent potential issues with comparison later on.
    uid_int = static_cast<int>(uid);
    User *printed = library->getUser(uid_int);
    // CWE-476: NULL Pointer Dereference - pointer is checked for null before being dereferenced
    // CWE-129: Improper validation of array index- we don't use an out of bounds int for the array since the method will return null if something isn't found in the array.
    // we check if the thing is in the array before we use the array location, so this naturally works for out of bounds ints as well.
    if (printed == nullptr)
    {
        cout << "User not found" << endl;
        return;
    }
    cout << "\nName: " + printed->getName() << endl;
    vector<int> *copies = printed->getCheckedOutCopies();
    // CWE-690: Unchecked Return Value to NULL Pointer Dereference - copies is checked if null to prevent dereferencing errors with cid.
    if (copies == nullptr)
    {
        cout << "Checked out Books: None" << endl;
        return;
    }
    int cid;
    string bName;
    // CWE-469: Use of Pointer Subtraction to Determine Size - the vector's size() method is used instead of pointer subtraction to more accurately determine its size
    for (int i = 0; i < copies->size(); i++)
    {
        cid = (*copies)[i];
        bName = library->getBook(library->getCopy(cid)->getISBN())->getTitle();
        cout << "Checked out Books:\n"
             << "Copy ID: " << cid << " Title: " << bName + "\n";
    }
    return;
}

void checkoutCopy(Collection *library)
{
    cout << "Enter Copy ID: " << endl;
    int cid;
    cin >> cid;
    Copy *checked = library->getCopy(cid);
    if (!checked->getAvailability())
    {
        cout << "Cannot be checked out right now." << endl;
        return;
    }
    cout << "Enter User ID to check out: " << endl;
    int uid;
    User *used = library->getUser(uid);
    used->checkOutCopy(cid);
    checked->setAvailability(false);
    cout << "Checked out successfully." << endl;
    return;
}

void returnCopy(Collection *library)
{
    cout << "Enter Copy ID: " << endl;
    int cid;
    cin >> cid;
    Copy *checked = library->getCopy(cid);
    if (checked->getAvailability())
    {
        cout << "Already checked in." << endl;
        return;
    }
    User *user = library->getUser(checked->getLastUserID());
    user->returnCopy(cid);
    checked->setAvailability(true);
    cout << "Checked in successfully." << endl;
    return;
}

void printBooks(Collection *library)
{
    cout << endl;
    cout << library->getBooksString();
    return;
}

void printCopies(Collection *library)
{
    cout << endl;
    cout << "Available copies: "
         << to_string(library->getAvailableCopiesCount());
    return;
}

void addCopy(Collection *library)
{
}