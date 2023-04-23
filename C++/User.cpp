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

const vector<Copy *> User::getCheckedOutCopies() const
{
    return checkedOutCopies;
}

void User::checkOutCopy(Copy *copy)
{
    checkedOutCopies.push_back(copy);
}
