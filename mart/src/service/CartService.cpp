#include "CartService.h"

CartService::CartService(CartRepository& cart_repository,
                         ProductRepository& product_repository)
    : cart_repository_(cart_repository), product_repository_(product_repository) {}

bool CartService::Add(int user_id, int product_id, int quantity) {
    if (user_id <= 0 || quantity <= 0) return false;
    auto product = product_repository_.FindById(product_id);
    if (!product.has_value() || quantity > product->stock_qty) return false;
    return cart_repository_.AddOrUpdate(user_id, product_id, quantity);
}

bool CartService::Remove(int user_id, int product_id) {
    return cart_repository_.Remove(user_id, product_id);
}

std::vector<CartItem> CartService::Get(int user_id) {
    return cart_repository_.FindByUser(user_id);
}
