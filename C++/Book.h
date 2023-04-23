/**
 * Class representing a book in the colleciton.
 * @author Austen Tankersley & Braydon Hughes.
 */
#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;
class Book
{
private:
    int ISBN;
    string title;
    string author;
    string genre;
    string shortDesc;
    string publishedYear;
    string publisher;
    string binding; // hardcover or paperback

public:
    string getTitle();
    string getAuthor();
    string getGenre();
    string getShortDesc();
    string getPublisher();
    string getBinding();
    int getISBN();
};
#endif