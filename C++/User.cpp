/**
 * Implementation of class representing a user of the system.
 * @author Austen Tankersley and Braydon Hughes
 */

class User
{
public:
    User(int id, const string &name) : id(id), name(name) {}

    int get_id() const
    {
        return id;
    }

    const string &get_name() const
    {
        return name;
    }

    const vector<Book *> &get_checked_out_books() const
    {
        return checked_out_books;
    }

    void check_out_book(Book *book)
    {
        checked_out_books.push_back(book);
    }

private:
    int id;
    string name;
    vector<Book *> checked_out_books;
};
