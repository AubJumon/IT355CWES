/**
 * Implementation for Collection of items
 * @author Austen Tankersley & Braydon Hughes
 */
#include "Collection.h"
#include "lib/nlohmann/json.hpp"
Collection::Collection(int id, string name)
{
    this->collectionID = id;
    this->name = name;
}

Collection::Collection(string filename)
{
    ifstream fileStream(filename);
    nlohmann::json jsonFile;
    fileStream >> jsonFile;

    name = jsonFile["name"];
    collectionID = jsonFile["collectionID"];

    for (const auto &user : jsonFile["users"])
    {
        this->users.push_back(User(user["id"], user["name"], user["checkedOutCopies"]));
    }

    for (const auto &copy : jsonFile["copies"])
    {
        this->copies.push_back(Copy(copy["copyID"], copy["ISBN"], copy["availability"], copy["lastUserID"]));
    }
    cout << "EEE" << endl;

    for (const auto &book : jsonFile["books"])
    {
        this->books.push_back(Book(book["ISBN"], book["title"], book["author"], book["genre"], book["shortDesc"], book["publishedYear"], book["publisher"], book["binding"]));
    }
    cout << "EEE" << endl;
}

void Collection::addBook(long long ISBN, string title, string author, string genre, string shortDesc, int publishedYear, string publisher, string binding)
{
    // CWE - 131 : Incorrect Calculation of Buffer Size - avoided by using vector instead of fixed-size array.
    //  CWE-121: Stack- based buffer overflow.
    //  We avoid buffer overflow by using vectors instead of dynamic arrays and by using the push_back function
    //  instead of using arrays and directly accessing a location that is potentially out of buffer bounds.
    books.push_back(Book(ISBN, title, author, genre, shortDesc, publishedYear, publisher, binding));
}

void Collection::addUser(int id, string name)
{
    users.push_back(User(id, name));
}

User *Collection::getUser(int id)
{
    User *userPtr = nullptr;
    for (User &user : users)
    {
        if (user.getId() == id)
        {
            // Found the user
            userPtr = &user;
        }
    }

    return userPtr; // if not found return a null user
}

Book *Collection::getBook(long long id)
{
    Book *bookPtr = nullptr;
    for (Book &book : books)
    {
        if (book.getISBN() == id)
        {
            // Found the book.
            bookPtr = &book;
        }
    }

    return bookPtr;
}

Copy *Collection::getCopy(int id)
{
    Copy *copyPtr = nullptr;
    for (Copy &copy : copies)
    {
        if (copy.getID() == id)
        {
            // Found the book.
            copyPtr = &copy;
        }
    }

    return copyPtr;
}

string Collection::getBooksString()
{
    string booksString = "";
    for (int i = 0; i < books.size(); i++)
    {
        booksString += books[i].toString();
    }
    // CWE-170: Improper Null Termination - appends a null character to booksString to prevent buffer overflow
    booksString.push_back('\0');
    return booksString;
}

string Collection::getName()
{
    return name;
}

int Collection::getAvailableCopiesCount()
{
    int copiesCount;
    for (int i = 0; i < copies.size(); i++)
    {
        // CWE-123: Write-what-where Condition: i is never less than copies.size() because of the for loop condition.
        if (copies[i].getAvailability())
        {
            copiesCount++;
        }
    }
    return copiesCount;
}