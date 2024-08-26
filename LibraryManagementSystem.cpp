#include <iostream>
#include "db_operations.h"

int main() {
    // Open/Create the database
    if (!openDatabase("library.db")) {
        return 1; // Exit with error
    }

    // Create table
    createTable();

    // Insert a new book
    insertBook("The Great Gatsby", "F. Scott Fitzgerald", 1925, "Novel");

    // Query all books
    std::cout << "Books in the database:" << std::endl;
    queryBooks();

    // Update a book (for example, updating the first book)
    updateBook(1, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "Classic");

    // Query all books again to see the update
    std::cout << "Books in the database after update:" << std::endl;
    queryBooks();

    // Delete a book (for example, deleting the first book)
    deleteBook(1);

    // Query all books again to see the deletion
    std::cout << "Books in the database after deletion:" << std::endl;
    queryBooks();

    // Close the database
    closeDatabase();

    return 0;
}
