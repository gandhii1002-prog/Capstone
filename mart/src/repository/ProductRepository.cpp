#include "ProductRepository.h"
#include "../util/Database.h"
#include <sqlite3.h>
#include <optional>

std::vector<Product> ProductRepository::FindAll() {
    std::vector<Product> products;
    const char* sql =
        "SELECT id,seller_id,name,description,price_cents,stock_qty,category FROM products";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return products;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Product p;
        p.id = sqlite3_column_int(stmt, 0);
        p.seller_id = sqlite3_column_int(stmt, 1);
        p.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        p.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        p.price_cents = sqlite3_column_int64(stmt, 4);
        p.stock_qty = sqlite3_column_int(stmt, 5);
        p.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        products.push_back(p);
    }

    sqlite3_finalize(stmt);
    return products;
}

std::optional<Product> ProductRepository::FindById(int id) {
    const char* sql =
        "SELECT id,seller_id,name,description,price_cents,stock_qty,category "
        "FROM products WHERE id=?";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return std::nullopt;

    sqlite3_bind_int(stmt, 1, id);

    std::optional<Product> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Product p;
        p.id = sqlite3_column_int(stmt, 0);
        p.seller_id = sqlite3_column_int(stmt, 1);
        p.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        p.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        p.price_cents = sqlite3_column_int64(stmt, 4);
        p.stock_qty = sqlite3_column_int(stmt, 5);
        p.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        result = p;
    }

    sqlite3_finalize(stmt);
    return result;
}
