/**
 * Implementation of class representing a user of the system.
 * @author Austen Tankersley and Braydon Hughes
 */

#include "User.h"

int User::getId() const
{
    return id;
}

const string User::getName() const
{
    return name;
}

vector<int> *User::getCheckedOutCopies()
{
    return &checkedOutCopies;
}

void User::checkOutCopy(int cid)
{
    checkedOutCopies.push_back(cid);
}

void User::returnCopy(int cid)
{
    checkedOutCopies.erase(remove(checkedOutCopies.begin(), checkedOutCopies.end(), cid));
}