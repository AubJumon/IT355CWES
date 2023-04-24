/**
 * Implementation of a class representing a book.
 * @author Austen Tankersley & Braydon Hughes
 */

#include "Book.h"

Book::Book(long long ISBN, string title, string author, string genre, string shortDesc, int publishedYear, string publisher, string binding)
{
    this->ISBN = ISBN;
    this->title = title;
    this->author = author;
    this->genre = genre;
    this->shortDesc = shortDesc;
    this->publishedYear = publishedYear;
    this->publisher = publisher;
    this->binding = binding;
}

long long Book::getISBN()
{
    return ISBN;
}

string Book::getTitle()
{
    return title;
}

string Book::getAuthor()
{
    return author;
}

string Book::getGenre()
{
    return genre;
}

string Book::getShortDesc()
{
    return shortDesc;
}

string Book::getPublisher()
{
    return publisher;
}

string Book::getBinding()
{
    return binding;
}

string Book::toString()
{
    return "\nISBN: " + to_string(ISBN) + "\nTitle: " + title + "\nAuthor: " + author + "\nGenre: " + genre + "\nShort Description: " + shortDesc + "\nPublished Year: " + to_string(publishedYear) + "\nPublisher: " + publisher + "\nBinding: " + binding + "\n";
}