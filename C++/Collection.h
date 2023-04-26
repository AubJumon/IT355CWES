/**
 * Class representing a collection or library of items.
 * @author Austen Tankersley & Braydon Hughes
 */
#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "User.h"
#include "Book.h"
#include "Copy.h"
using namespace std;

class Collection
{
private:
    vector<User> users;
    vector<Copy> copies;
    vector<Book> books;
    int collectionID;
    string name;

public:
    /**
     * Create empty collection.
     */
    Collection(int id, string name);

    /**
     * Create the collection by reading from a JSON file.
     */
    Collection(string filename);

    string getName();
    int getID();
    void addBook(long long ISBN, string title, string author, string genre, string shortDesc, int publishedYear, string publisher, string binding);

    void addUser(int id, string name);
    void addCopy();
    /**
     * Finds a user in the Collection's list of users.
     * @param id id of the user to search for.
     * @return null if user is not found, a pointer to the user if it is found.
     */
    User *getUser(int id);
    Book *getBook(long long id);
    Copy *getCopy(int id);
    string getBooksString();
    string getCopiesString();
    string getBasicUsersString();
    string getCopyTitle(int copyID);
    int getAvailableCopiesCount();
    int getMaxUserID();
    void checkOutCopy(int copyID, int userID);
};
#endif