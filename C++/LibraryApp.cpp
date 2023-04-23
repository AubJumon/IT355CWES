/**
 * Library app demonstrating CWE's of the C++ language.
 * @author Austen Tankersley and Braydon Hughes
 */

#include <iostream>

using namespace std;

void print_menu() {
    cout << endl;
    cout << "1. Add book to library" << endl;
    cout << "2. Add user to system" << endl;
    cout << "3. Borrow book" << endl;
    cout << "4. Return book" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
}

int main() {
    int choice = 0;

    while (choice != 5) {
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                add_user();
                break;
            case 3:
                borrow_book();
                break;
            case 4:
                return_book();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
            //CWE-484: omitted Break Statement in Switch
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

