#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    static Database& Instance();

    sqlite3* Get() const;
    void Initialize(const std::string& filename);

private:
    Database() = default;
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    sqlite3* db_{nullptr};
};
