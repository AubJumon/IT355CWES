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
    long long ISBN;
    string title;
    string author;
    string genre;
    string shortDesc;
    int publishedYear;
    string publisher;
    string binding; // hardcover or paperback

public:
    Book(long long ISBN, string title, string author, string genre, string shortDesc, int publishedYear, string publisher, string binding);
    string getTitle();
    string getAuthor();
    string getGenre();
    string getShortDesc();
    string getPublisher();
    string getBinding();
    long long getISBN();
    string toString();
};
#endif