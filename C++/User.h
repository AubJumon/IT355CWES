/**
 * Class representing a user of the collection.
 * @author Austen Tankersley & Braydon Hughes
 */
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class User
{
private:
    int id;
    string name;
    vector<Book *> checked_out_books;

public:
    User(unsigned char id, const string &name);
    unsigned char get_id() const;
    const string &get_name() const;
    const vector<Book *> &get_checked_out_books() const;
    void check_out_book(Book *book);
};

#endif
