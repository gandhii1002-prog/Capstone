#include "Database.h"
#include <stdexcept>

Database& Database::Instance() {
    static Database instance;
    return instance;
}

sqlite3* Database::Get() const {
    return db_;
}

void Database::Initialize(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("Could not open SQLite database");
    }

    const char* schema = R"SQL(
        PRAGMA foreign_keys = ON;

        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL,
            role TEXT NOT NULL CHECK(role IN ('BUYER','SELLER','ADMIN')),
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            seller_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            description TEXT NOT NULL,
            price_cents INTEGER NOT NULL,
            stock_qty INTEGER NOT NULL,
            category TEXT NOT NULL,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(seller_id) REFERENCES users(id)
        );

        CREATE TABLE IF NOT EXISTS cart_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            product_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL,
            UNIQUE(user_id, product_id),
            FOREIGN KEY(user_id) REFERENCES users(id),
            FOREIGN KEY(product_id) REFERENCES products(id)
        );

        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            buyer_id INTEGER NOT NULL,
            status TEXT NOT NULL DEFAULT 'PENDING',
            total_amount_cents INTEGER NOT NULL,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(buyer_id) REFERENCES users(id)
        );

        CREATE TABLE IF NOT EXISTS order_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id INTEGER NOT NULL,
            product_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL,
            unit_price_cents INTEGER NOT NULL,
            FOREIGN KEY(order_id) REFERENCES orders(id),
            FOREIGN KEY(product_id) REFERENCES products(id)
        );
    )SQL";

    char* error = nullptr;
    if (sqlite3_exec(db_, schema, nullptr, nullptr, &error) != SQLITE_OK) {
        std::string message = error ? error : "Schema creation failed";
        sqlite3_free(error);
        throw std::runtime_error(message);
    }

    const char* seed = R"SQL(
        INSERT OR IGNORE INTO users(id,name,email,password_hash,role)
        VALUES(1,'Demo Seller','seller@kishoremart.local','DEMO_PASSWORD','SELLER');

        INSERT OR IGNORE INTO products(id,seller_id,name,description,price_cents,stock_qty,category)
        VALUES
        (1,1,'Mechanical Keyboard','Entry-level mechanical keyboard',149900,10,'Keyboard'),
        (2,1,'Wireless Mouse','2.4GHz wireless mouse',79900,20,'Mouse'),
        (3,1,'USB Headset','USB headset with microphone',199900,8,'Audio');
    )SQL";

    if (sqlite3_exec(db_, seed, nullptr, nullptr, &error) != SQLITE_OK) {
        std::string message = error ? error : "Seed failed";
        sqlite3_free(error);
        throw std::runtime_error(message);
    }
}

Database::~Database() {
    if (db_) sqlite3_close(db_);
}
