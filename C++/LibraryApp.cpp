/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

// CWE-194: Unexpected Sign Extension - user ID is casted to integer from signed character to prevent potential issues with comparison later on.

// CWE-195: Signed to Unsigned Conversion error - We don't use unsigned data types in the program, so we never convert from a signed int to an unsigned.
// The mitigation for this CWE is to simply not do it. A short example of code that would have this CWE is this:
// unsigned int returndata(){
// return -1;
//}
// because the above code returns an unsigned int it is implicitly cast and the value of the returned int is 4,294,967,295.

// CWE-467: Use of sizeof() on a pointer type - sizeof() function is avoided, and more efficient methods such as size() are used when needed.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
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
void printAllUsers(Collection *library);

// use to validate input, returns valid string depending on regex and prints error message
string validateInput(regex reg, string errorMessage);
// use to validate integer IDs. Returns a valid ID and prompts for user input using idReg and validateInput functions.
int validateID();
// regex for strings, ensures they are under 255 characters.
regex strReg();

int main()
{

    string choice;
    char choiceChar;
    string collectionName;
    string collectionFileName;
    int nextCollectionID = 0;
    Collection *library;

    cout << "Welcome to the library!" << endl;
    cout << "Read collection from a file? (y/n)\n> ";
    // CWE-125: Out-of-bounds Read - choice only accepted when a value is entered, does not accept empty string.
    choice = validateInput(regex("^(yes|no|y|n)$"), "Invalid input. Please enter yes, no, y, or n.");
    choiceChar = tolower(choice.at(0));
    if (choiceChar == 'y')
    {
        cout << "Enter the filename:" << endl;
        cout << "> ";
        collectionFileName = validateInput(strReg(), "Invalid input. Collection file name must be 255 characters or less.");
        while (!fs::exists(collectionFileName))
        {
            cout << "That file doesn't exist. Please try again or enter -1 to exit." << endl;
            cout << "> ";
            collectionFileName = validateInput(strReg(), "Invalid input. Collection file name must be 255 characters or less.");
            // CWE-482: Comparing Instead of Assigning - string is matched for equality instead of altering value
            if (collectionFileName == "-1")
            {
                cout << "Goodbye." << endl;
                exit(0);
            }
        }

        library = new Collection(collectionFileName);
        cout << endl;
    }
    else if (choiceChar == 'n')
    {
        cout << "Input the name of the collection." << endl;
        cout << "> ";
        collectionName = validateInput(strReg(), "Invalid input Collection name must be 255 or less characters.");
        library = new Collection(nextCollectionID, collectionName);
        nextCollectionID++;
    }

    cout << "Collection " + library->getName() + " created successfully." << endl;

    collectionActionPrompt(library);

    return 0;
}

void collectionActionPrompt(Collection *library)
{
    /**
     * CWE-192: Integer coercion error. We do not coerce integers to another type in this program which avoids the common weakness.
     * If we had done int choice = a, that would have violated the CWE.
     * We use a regex-validated string for the choice variable instead of an integer to avoid this issue with input.
     * This also applies for CWE-704, Incorrect type conversion or cast.
     * */

    int choice = 0;
    const int exitChoice = 10;
    while (choice != exitChoice)
    {
        std::cout << endl;
        cout << "1. Add book to system" << endl;
        cout << "2. Add copy to collection" << endl;
        cout << "3. Add user to system" << endl;
        cout << "4. Check out copy" << endl;
        cout << "5. Return copy" << endl;
        cout << "6. View copies" << endl;
        cout << "7. View books" << endl;
        cout << "8. View user" << endl;
        cout << "9. View all users" << endl;
        cout << "10. Exit" << endl;
        cout << endl;
        cout << "Enter choice: ";

        // this regex also ensures that the integer overflow does not occur.
        choice = stoi(validateInput(regex("^\\d\\d{0,3}"), "Invalid input."));

        switch (choice)
        {
        case 1:
            addBook(library);
            break;
        case 2:
            addCopy(library);
            break;
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
            printAllUsers(library);
            break;
        case exitChoice:
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
    const int STRING_BUFFER_SIZE = 256;
    long long isbn;
    int publishedYear;
    string author, genre, shortDesc, publisher, binding;
    string titleBuf = new char[STRING_BUFFER_SIZE];

    // Get book information from user
    cout << "Enter ISBN: ";
    // CWE-787: Out-of-bounds Write - ISBN should only ever be 13 digits, length checking prevents writing value beyond allotted long long length.
    isbn = stoll(validateInput(regex("^978\\d{10}$"), "Invalid input. ISBN must begin with 978 and be 13 digits long."));

    cout << "Enter title: ";
    // CWE-120: Buffer copy without checking size of Input (Classic Buffer Overflow).
    // we make sure that the input is 255 characters or less so that the 256-length buffer is not overflowed. :)
    // CWE-242 Use of inherently dangerous function: We do not use strcpy() to copy a string to the buffer because it is vulnerable to buffer overflows.
    // using regex validation like this is a lot more effective to prevent buffer overflow, and we do so for all input strings.
    titleBuf = validateInput(strReg(), "Invalid input. Title must be 255 or less characters.").c_str();

    cout << "Enter author: ";
    author = validateInput(regex("^.{1,55}$"), "Invalid input. Author must be 55 or less characters.");

    cout << "Enter genre: ";
    genre = validateInput(strReg(), "Invalid input. Genre must be 255 or less characters.");

    cout << "Enter short description: ";
    shortDesc = validateInput(strReg(), "Invalid input. Short desc must be 255 or less characters.");

    cout << "Enter published year: ";

    // CWE-839: Numeric range comparison without minimum check
    // We use regex to perform the minimum check.
    publishedYear = stoi(validateInput(regex("^-?[0-9]{1,4}$"), "Invalid input. Year must be between -9999 and 9999."));

    cout << "Enter publisher: ";
    publisher = validateInput(strReg(), "Invalid input. Publisher must be 255 or less characters.");

    cout << "Enter binding (Hardcover, Paperback, or Other.): ";
    binding = validateInput(regex("^(Hardcover|Paperback|Other|hardcover|paperback|other)$"), "Invalid input. Please enter hardcover, paperback, or other.");
    binding[0] = toupper(binding[0]); // capitalize
    library->addBook(isbn, titleBuf, author, genre, shortDesc, publishedYear, publisher, binding);
    return;
}

void addUser(Collection *library)
{
    string name;
    cout << "Enter name: ";
    name = validateInput(regex("^.{0,55}$"), "Invalid input. Name must be 55 or less characters.");
    library->addUser(name);
    return;
}

void printUser(Collection *library)
{
    cout << "Enter User ID: ";
    int uid = validateID();

    User *printed = library->getUser(uid);
    // CWE-476: NULL Pointer Dereference - pointer is checked for null before being dereferenced
    // CWE-129: Improper validation of array index- we don't use an out of bounds int for the array
    // since the method will return null if something isn't found in the array.
    // We check if the thing is in the array before we use the array location, so this naturally works for out of bounds ints as well.
    if (printed == nullptr)
    {
        cout << "User not found" << endl;
    }
    else
    {
        cout << "\nName: " + printed->getName() << endl;
        cout << "----------------\n";
        vector<int> *copies = printed->getCheckedOutCopies();
        // CWE-690: Unchecked Return Value to NULL Pointer Dereference - copies is checked if null to prevent dereferencing errors with cid.
        if (copies == nullptr)
        {
            cout << "Nothing checked out." << endl;
        }
        else
        {
            int cid;
            string bName;
            cout << "Checked out Copies:" << endl;
            // CWE-469: Use of Pointer Subtraction to Determine Size - the vector's size() method is used instead of pointer subtraction to more accurately determine its size
            for (int i = 0; i < copies->size(); i++)
            {
                cid = (*copies)[i];
                bName = library->getCopyTitle(cid);
                cout << "Copy ID: " << cid << " Title: " << bName + "\n";
            }
        }
    }

    return;
}

void checkoutCopy(Collection *library)
{
    int cid;
    int uid;
    cout << "Enter Copy ID: ";
    cid = validateID();
    Copy *checked = library->getCopy(cid);
    if (checked == nullptr || !checked->getAvailability()) // avoid nullptr use
    {
        cout << "Copy is out of stock or does not exist." << endl;
        return;
    }
    cout << "Enter User ID to check out: ";
    uid = validateID();
    if (library->getUser(uid) == nullptr)
    {
        cout << "User not found." << endl;
    }
    else
    {
        library->checkOutCopy(cid, uid);
        cout << library->getUser(uid)->getName() << " checked out " << library->getCopyTitle(cid) << "." << endl;
    }
    return;
}

void returnCopy(Collection *library)
{
    cout << "Enter Copy ID: " << endl;
    int cid;
    cin >> cid;
    Copy *checked = library->getCopy(cid);
    if (checked == nullptr)
    {
        cout << "Copy does not exist." << endl;
    }
    else if (checked->getAvailability())
    {
        cout << "Already checked in." << endl;
        return;
    }
    else
    {
        User *user = library->getUser(checked->getLastUserID());
        user->returnCopy(cid);
        checked->setAvailability(true);
        cout << "Checked in successfully." << endl;
    }

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
    cout << library->getCopiesString();
    return;
}

void addCopy(Collection *library)
{
    long long ISBN;
    cout << "Enter ISBN: ";
    ISBN = stoll(validateInput(regex("^978\\d{10}$"), "Invalid input. ISBN must begin with 978 and be 13 digits long."));
    if (library->getBook(ISBN) == nullptr)
    {
        cout << "That book was not found in the collection." << endl;
    }
    else
    {

        library->addCopy(ISBN);
    }
    return;
}

string validateInput(regex reg, string errorMessage)
{
    string input;
    // CWE-676: Use of Potentially Dangerous Function - cin is a potentially dangerous function; using getLine() helps prevent buffer overflow
    getline(cin, input);
    while (!regex_match(input, reg))
    {
        cout << errorMessage;
        cout << " Please try again." << endl;
        cout << "> ";
        input = "";
        getline(cin, input);
    }
    return input;
}

regex strReg()
{
    return regex("^.{1,255}$");
}

int validateID()
{
    return stoi(validateInput(regex("^[1-9]\\d{0,5}$"), "Invalid input. ID must be between 1 and 999999."));
}
void printAllUsers(Collection *library)
{
    cout << endl;
    cout << library->getBasicUsersString();
    return;
}