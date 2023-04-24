/**
 * Implementation class for a library item copy.
 * @author Austen Tankersley & Braydon Hughes.
 */
#include "Copy.h"
using namespace std;

int Copy::getID()
{
    return copyID;
}
void Copy::setAvailability(bool avail)
{
    availability = avail;
}
bool Copy::getAvailability()
{
    return availability;
}

void Copy::setLastUserID(int id)
{
    lastUserID = id;
}

int Copy::getLastUserID()
{
    return lastUserID;
}

long long Copy::getISBN()
{
    return ISBN;
}

string Copy::toString()
{
    string copyString = "";
    copyString += "\nCopy ID: " + to_string(copyID) + "\n";
    return copyString;
}
