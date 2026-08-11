#include "CartRepository.h"
#include "../util/Database.h"
#include <sqlite3.h>

bool CartRepository::AddOrUpdate(int user_id, int product_id, int quantity) {
    const char* sql =
        "INSERT INTO cart_items(user_id,product_id,quantity) VALUES(?,?,?) "
        "ON CONFLICT(user_id,product_id) DO UPDATE SET quantity=excluded.quantity";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_int(stmt, 2, product_id);
    sqlite3_bind_int(stmt, 3, quantity);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool CartRepository::Remove(int user_id, int product_id) {
    const char* sql = "DELETE FROM cart_items WHERE user_id=? AND product_id=?";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_int(stmt, 2, product_id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

std::vector<CartItem> CartRepository::FindByUser(int user_id) {
    std::vector<CartItem> items;
    const char* sql = "SELECT product_id,quantity FROM cart_items WHERE user_id=?";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return items;

    sqlite3_bind_int(stmt, 1, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        items.push_back({sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1)});
    }

    sqlite3_finalize(stmt);
    return items;
}

bool CartRepository::Clear(int user_id) {
    const char* sql = "DELETE FROM cart_items WHERE user_id=?";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, user_id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}
