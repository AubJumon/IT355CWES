/**
 * Class representing a collection or library of items.
 * @author Austen Tankersley & Braydon Hughes
 */
#include <string>
#include <vector>
#include "User.h"
#include "Book.h"
#include "Copy.h"
using namespace std;

class Collection
{
private:
    vector<User> users;
    vector<Copy> copies;
    vector<Book> books;
    int collectionID;
    string name;

public:
    string getName();
    int getID();
};