#include <iostream>
#include <sqlite3.h>
#include "db_operations.h"

sqlite3* db;
char* errMsg = 0;

// Open/Create the database
bool openDatabase(const char* dbName) {
    if (sqlite3_open(dbName, &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

// Close the database
void closeDatabase() {
    sqlite3_close(db);
}

// Create the books table
void createTable() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            year INTEGER NOT NULL,/
            genre TEXT NOT NULL
        );
    )";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Insert a new book into the table
void insertBook(const char* title, const char* author, int year, const char* genre) {
    const char* sql = R"(
        INSERT INTO books (title, author, year, genre)
        VALUES (?, ?, ?, ?);
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, year);
    sqlite3_bind_text(stmt, 4, genre, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert book: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

// Query all books from the table
void queryBooks() {
    const char* sql = "SELECT * FROM books;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        const unsigned char* author = sqlite3_column_text(stmt, 2);
        int year = sqlite3_column_int(stmt, 3);
        const unsigned char* genre = sqlite3_column_text(stmt, 4);

        std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author
            << ", Year: " << year << ", Genre: " << genre << std::endl;
    }
    sqlite3_finalize(stmt);
}

// Update a book by ID
void updateBook(int id, const char* title, const char* author, int year, const char* genre) {
    const char* sql = R"(
        UPDATE books
        SET title = ?, author = ?, year = ?, genre = ?
        WHERE id = ?;
    )";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, year);
    sqlite3_bind_text(stmt, 4, genre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to update book: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

// Delete a book by ID
void deleteBook(int id) {
    const char* sql = "DELETE FROM books WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to delete book: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
