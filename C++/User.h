/**
 * Class representing a user of the collection.
 * @author Austen Tankersley & Braydon Hughes
 */
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"

using namespace std;

class User
{
private:
    int id;
    string name;
    vector<int> checkedOutCopies;

public:
    User(int id, string name) : id(id), name(name) {}
    User(int id, string name, vector<int> checkedOutCopies) : id(id), name(name), checkedOutCopies(checkedOutCopies) {}
    int getId() const;
    const string getName() const;
    vector<int> *getCheckedOutCopies();
    void checkOutCopy(int cid);
    void returnCopy(int cid);
};

#endif
