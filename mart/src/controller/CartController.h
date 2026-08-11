#pragma once
#include <drogon/HttpController.h>

class CartController : public drogon::HttpController<CartController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CartController::Add, "/api/v1/cart", drogon::Post);
    ADD_METHOD_TO(CartController::Get, "/api/v1/cart", drogon::Get);
    ADD_METHOD_TO(CartController::Remove, "/api/v1/cart", drogon::Delete);
    METHOD_LIST_END

    void Add(const drogon::HttpRequestPtr& req,
             std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void Get(const drogon::HttpRequestPtr& req,
             std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void Remove(const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
