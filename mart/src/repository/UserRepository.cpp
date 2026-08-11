#include "UserRepository.h"
#include "../util/Database.h"
#include <sqlite3.h>

bool UserRepository::Create(const User& user) {
    const char* sql =
        "INSERT INTO users(name,email,password_hash,role) VALUES(?,?,?,?)";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, user.password_hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, user.role.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

std::optional<User> UserRepository::FindByEmail(const std::string& email) {
    const char* sql =
        "SELECT id,name,email,password_hash,role FROM users WHERE email=?";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(Database::Instance().Get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        return std::nullopt;

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<User> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        User user;
        user.id = sqlite3_column_int(stmt, 0);
        user.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        user.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        user.password_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        user.role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        result = user;
    }

    sqlite3_finalize(stmt);
    return result;
}
