/**
 * Class representing a collection or library of items.
 * @author Austen Tankersley & Braydon Hughes
 */
#include <string>
using namespace std;

class Collection
{
private:
    int collectionID;
    string name;

public:
    string getName();
    int getID();
};