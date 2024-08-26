#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

// Open/Create the database
bool openDatabase(const char* dbName);

// Close the database
void closeDatabase();

// Create the books table
void createTable();

// Insert a new book into the table
void insertBook(const char* title, const char* author, int year, const char* genre);

// Query all books from the table
void queryBooks();

// Update a book by ID
void updateBook(int id, const char* title, const char* author, int year, const char* genre);

// Delete a book by ID
void deleteBook(int id);

#endif // DB_OPERATIONS_H

