#include "ProductController.h"
#include "../repository/ProductRepository.h"
#include "../service/ProductService.h"

void ProductController::List(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    ProductRepository repository;
    ProductService service(repository);
    auto products = service.GetProducts();

    Json::Value array(Json::arrayValue);
    for (const auto& p : products) {
        Json::Value item;
        item["id"] = p.id;
        item["name"] = p.name;
        item["description"] = p.description;
        item["price_cents"] = Json::Int64(p.price_cents);
        item["stock_qty"] = p.stock_qty;
        item["category"] = p.category;
        array.append(item);
    }

    callback(drogon::HttpResponse::newHttpJsonResponse(array));
}
