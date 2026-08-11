#pragma once
#include "../model/CartItem.h"
#include <vector>

class CartRepository {
public:
    bool AddOrUpdate(int user_id, int product_id, int quantity);
    bool Remove(int user_id, int product_id);
    std::vector<CartItem> FindByUser(int user_id);
    bool Clear(int user_id);
};
