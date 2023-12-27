#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Book
{
private:
    string ID;
    string title;
    string author;
    int quantity;

public:
    // Constructor to initialize a Book object
    Book(const string& myID, const string& myTitle, const string& myAuthor, int myQuantity)
        : ID(myID), title(myTitle), author(myAuthor), quantity(myQuantity){}

    // Getter method for ID
    const string& getID() const
    {
        return ID;
    }

    // Display book information
    void displayBook() const
    {   
        cout << "\t" << ID << "\t\t" << title << "\t\t" << author << "\t\t" << quantity << endl;
    }

    // Sell specified quantity of books
    void sell(int myQuantity)
    {
        if(myQuantity <= quantity)
        {
            quantity -= myQuantity;
            cout << "Sold " << myQuantity << " copies of <" << title << ">. Remaining quantity: " << quantity << endl;
        }
        else
            cout << "Insufficient quantity to sell.\n";
    }

    // Add specified quantity to the existing quantity of books
    void addQuantity(int amount)
    {
        quantity += amount;
        cout << "Added " << amount << " copies of <" << title << ">. Updated quantity: " << quantity << endl;
    }

    // Overloaded equality operator to compare books based on ID
    bool operator==(const Book& other) const
    {
        return ID == other.ID;
    }
};

class BookInventory
{
private:
    vector<Book> books;

    // Sort the books vector based on book ID
    void sortBookByID()
    {
        for(int i = 0; i < books.size(); i++)
        {
            for(int j = i + 1; j < books.size(); j++)
            {
                if(books[i].getID() > books[j].getID())
                    swap(books[i], books[j]);
            }
        }
    }

public:
    // Find a book in the inventory based on its ID
    Book* findBookByID(const string& bookID)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getID() == bookID)
                return &books[i];
        }
        return nullptr;
    }

    // Add a new book to the inventory
    void addBook(const string& myID, const string& myTitle, const string& myAuthor, int myQuantity)
    {
        Book newbook(myID, myTitle, myAuthor, myQuantity);
        books.push_back(newbook);

        // Sort the books after adding a new one
        sortBookByID();

        cout << "Book added!\n"; 
    }

    // Delete a book from the inventory based on its ID
    void deleteBook(const string& myID)
    {
        Book* deleted = findBookByID(myID);
        if (deleted != nullptr)
        {
            books.erase(remove(books.begin(), books.end(), *deleted), books.end());
            cout << "Book deleted!\n";
        }
        else
            cout << "Book not found!\n";
    }

    // Display information for all books in the inventory
    void displayAllBooks() const
    {
        if(books.empty())
            cout << "No books in inventory!\n";
        else
        {
            cout << "\t\t\t\tAll Books\n\n";
            cout << "\tID\t\tTitle\t\tAuthor\t\tQuantity\n\n";
            for(int i = 0; i < books.size(); i++)
                books[i].displayBook();
            cout << endl;
        }
    }

    // Sell a specified quantity of a book based on its ID
    void sellBook(const string& myID, int myQuantity)
    {
        Book* sold = findBookByID(myID);
        if (sold != nullptr)
            sold->sell(myQuantity);
        else
            cout << "Book not available.\n";
    }
};

int main()
{
    BookInventory inventory;
    int option;
    string id;
    int quantity;

    // Add some initial books to the inventory
    inventory.addBook("003", "Cat", "Tom", 5);
    inventory.addBook("002", "Dog", "Bob", 10);
    inventory.addBook("001", "Rat", "Andy", 3);

    do
    {
        // Display the menu and get user input
        cout << "================================================================================\n";
        cout << "\t\t\t1. Add a book\n";
        cout << "\t\t\t2. Sell a book\n";
        cout << "\t\t\t3. Delete a book\n";
        cout << "\t\t\t4. Show all books\n";
        cout << "\t\t\t5. Exit\n";
        cout << "================================================================================\n";
        cout << "Enter option: ";
        cin >> option;
        cout << "================================================================================\n";

        // Perform the selected operation based on user input
        switch (option)
        {
            case 1:
            {
                string title;
                string author;

                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                Book* existingBook = inventory.findBookByID(id);
                if(existingBook != nullptr)
                {
                    cout << "Enter book quantity: ";
                    cin >> quantity;
                    existingBook->addQuantity(quantity);
                    break;
                }

                cout << "Enter book title: ";
                getline(cin, title);

                cout << "Enter book author: ";
                getline(cin, author);

                cout << "Enter book quantity: ";
                cin >> quantity;

                inventory.addBook(id, title, author, quantity);
                break;
            }
            case 2:
            {
                cout << "Enter book ID to sell: ";
                cin >> id;
                cin.ignore();

                cout << "Enter book quantity: ";
                cin >> quantity;

                inventory.sellBook(id, quantity);
                break;
            }
            case 3:
            {
                cout << "Enter book ID to delete: ";
                cin >> id;

                inventory.deleteBook(id);
                break;
            }
            case 4:
            {
                inventory.displayAllBooks();
                break;
            }
            case 5:
            {
                cout << "Exit!\n";
                cout << "================================================================================\n";
                break;
            }
            default:
            {
                cout << "Invalid option! Please try again!\n";
                break;
            }
        }
    } while (option != 5);

    return 0;
}