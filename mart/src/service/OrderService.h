#pragma once
#include "../repository/OrderRepository.h"
#include "../repository/CartRepository.h"
#include "../repository/ProductRepository.h"

class OrderService {
public:
    OrderService(OrderRepository& order_repository,
                 CartRepository& cart_repository,
                 ProductRepository& product_repository);

    bool Checkout(int buyer_id, int& order_id);

private:
    OrderRepository& order_repository_;
    CartRepository& cart_repository_;
    ProductRepository& product_repository_;
};
