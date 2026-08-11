#pragma once
#include <drogon/HttpController.h>

class ProductController : public drogon::HttpController<ProductController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProductController::List, "/api/v1/products", drogon::Get);
    METHOD_LIST_END

    void List(const drogon::HttpRequestPtr& req,
              std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
