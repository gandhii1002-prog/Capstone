#pragma once
#include <string>

struct Product {
    int id{};
    int seller_id{};
    std::string name;
    std::string description;
    long long price_cents{};
    int stock_qty{};
    std::string category;
};
