#pragma once
#include "../repository/CartRepository.h"
#include "../repository/ProductRepository.h"
#include <string>

class CartService {
public:
    CartService(CartRepository& cart_repository, ProductRepository& product_repository);
    bool Add(int user_id, int product_id, int quantity);
    bool Remove(int user_id, int product_id);
    std::vector<CartItem> Get(int user_id);

private:
    CartRepository& cart_repository_;
    ProductRepository& product_repository_;
};
