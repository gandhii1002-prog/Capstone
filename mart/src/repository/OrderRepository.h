#pragma once
#include "../model/Order.h"

class OrderRepository {
public:
    bool Create(int buyer_id, long long total, int& new_order_id);
    bool AddItem(int order_id, int product_id, int quantity, long long unit_price);
    bool UpdateStock(int product_id, int quantity);
};
