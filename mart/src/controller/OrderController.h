#pragma once
#include <drogon/HttpController.h>

class OrderController : public drogon::HttpController<OrderController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(OrderController::Checkout, "/api/v1/orders/checkout", drogon::Post);
    METHOD_LIST_END

    void Checkout(const drogon::HttpRequestPtr& req,
                  std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
