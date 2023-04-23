/**
 * Class representing a copy of an item in the library.
 * @author Austen Tankersley & Braydon Hughes.
 */
#include <string>
#include <chrono>
using namespace std;

class Copy
{
private:
    int copyID;
    bool availability;
    string lastUser;
    time_t dateCheckedOut;
    time_t dateCheckedIn;

public:
    int getID();

    bool getAvailability();

    void checkOut();

    string getLastUser();

    time_t getDateCheckedOut();

    time_t getDateCheckedIn();
};