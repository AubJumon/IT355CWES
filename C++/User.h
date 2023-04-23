/**
 * Class representing a user of the collection.
 * @author Austen Tankersley & Braydon Hughes
 */
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Book.h"
#include "Copy.h"

using namespace std;

class User
{
private:
    int id;
    string name;
    vector<Copy *> checkedOutCopies;

public:
    User(int id, string name) : id(id), name(name) {}
    int getId() const;
    const string getName() const;
    const vector<Copy *> getCheckedOutCopies() const;
    void checkOutCopy(Copy *copy);
};

#endif
