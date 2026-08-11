#include "OrderService.h"

OrderService::OrderService(OrderRepository& order_repository,
                           CartRepository& cart_repository,
                           ProductRepository& product_repository)
    : order_repository_(order_repository),
      cart_repository_(cart_repository),
      product_repository_(product_repository) {}

bool OrderService::Checkout(int buyer_id, int& order_id) {
    auto items = cart_repository_.FindByUser(buyer_id);
    if (items.empty()) return false;

    long long total = 0;
    for (const auto& item : items) {
        auto product = product_repository_.FindById(item.product_id);
        if (!product.has_value() || item.quantity > product->stock_qty) return false;
        total += product->price_cents * item.quantity;
    }

    // Mock payment confirmation for Review-1.
    if (!order_repository_.Create(buyer_id, total, order_id)) return false;

    for (const auto& item : items) {
        auto product = product_repository_.FindById(item.product_id);
        if (!product.has_value()) return false;
        if (!order_repository_.AddItem(order_id, item.product_id,
                                       item.quantity, product->price_cents))
            return false;
        if (!order_repository_.UpdateStock(item.product_id, item.quantity))
            return false;
    }

    return cart_repository_.Clear(buyer_id);
}
