/**
 * Class representing a copy of an item in the library.
 * @author Austen Tankersley & Braydon Hughes.
 */
#include <string>
using namespace std;

class Copy
{
private:
    int copyID;
    long long ISBN;
    bool availability;
    int lastUserID;

public:
    Copy(int copyID, long long ISBN, bool availability, int lastUserID) : copyID(copyID), ISBN(ISBN), availability(availability), lastUserID(lastUserID) {}
    int getID();
    long long getISBN();

    bool getAvailability();

    void setAvailability(bool avail);
    void setLastUserID(int id);

    void checkOut();

    int getLastUserID();
    string toString();
};