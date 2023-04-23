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
    bool availability;
    string currentUser;

public:
    int getID();

    bool getAvailability();
};