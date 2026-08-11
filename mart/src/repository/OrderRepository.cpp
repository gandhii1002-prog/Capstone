#include "OrderRepository.h"
#include "../util/Database.h"
#include <sqlite3.h>

bool OrderRepository::Create(int buyer_id, long long total, int& new_order_id) {
    const char* sql =
        "INSERT INTO orders(buyer_id,status,total_amount_cents) VALUES(?,'PENDING',?)";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, buyer_id);
    sqlite3_bind_int64(stmt, 2, total);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    new_order_id = static_cast<int>(sqlite3_last_insert_rowid(Database::Instance().Get()));
    sqlite3_finalize(stmt);
    return ok;
}

bool OrderRepository::AddItem(int order_id, int product_id, int quantity, long long unit_price) {
    const char* sql =
        "INSERT INTO order_items(order_id,product_id,quantity,unit_price_cents) VALUES(?,?,?,?)";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, order_id);
    sqlite3_bind_int(stmt, 2, product_id);
    sqlite3_bind_int(stmt, 3, quantity);
    sqlite3_bind_int64(stmt, 4, unit_price);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool OrderRepository::UpdateStock(int product_id, int quantity) {
    const char* sql =
        "UPDATE products SET stock_qty=stock_qty-? WHERE id=? AND stock_qty>=?";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, quantity);
    sqlite3_bind_int(stmt, 2, product_id);
    sqlite3_bind_int(stmt, 3, quantity);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(Database::Instance().Get()) == 1;
    sqlite3_finalize(stmt);
    return ok;
}
