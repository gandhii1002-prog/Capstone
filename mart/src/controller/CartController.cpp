#include "CartController.h"
#include "../repository/CartRepository.h"
#include "../repository/ProductRepository.h"
#include "../service/CartService.h"

static int GetUserId(const drogon::HttpRequestPtr& req) {
    return req->session()->getOptional<int>("user_id").value_or(0);
}

void CartController::Add(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    int user_id = GetUserId(req);
    if (user_id == 0) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k401Unauthorized);
        callback(r);
        return;
    }

    auto json = req->getJsonObject();
    if (!json) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k400BadRequest);
        callback(r);
        return;
    }

    CartRepository cart_repo;
    ProductRepository product_repo;
    CartService service(cart_repo, product_repo);

    bool ok = service.Add(user_id, (*json)["product_id"].asInt(),
                          (*json)["quantity"].asInt());

    Json::Value response;
    response["success"] = ok;
    response["message"] = ok ? "Added to cart" : "Could not add to cart";
    callback(drogon::HttpResponse::newHttpJsonResponse(response));
}

void CartController::Get(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    int user_id = GetUserId(req);
    if (user_id == 0) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k401Unauthorized);
        callback(r);
        return;
    }

    CartRepository cart_repo;
    ProductRepository product_repo;
    CartService service(cart_repo, product_repo);
    auto items = service.Get(user_id);

    Json::Value array(Json::arrayValue);
    for (const auto& item : items) {
        Json::Value row;
        row["product_id"] = item.product_id;
        row["quantity"] = item.quantity;
        array.append(row);
    }

    callback(drogon::HttpResponse::newHttpJsonResponse(array));
}

void CartController::Remove(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    int user_id = GetUserId(req);
    if (user_id == 0) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k401Unauthorized);
        callback(r);
        return;
    }

    auto json = req->getJsonObject();
    if (!json) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k400BadRequest);
        callback(r);
        return;
    }

    CartRepository cart_repo;
    ProductRepository product_repo;
    CartService service(cart_repo, product_repo);

    bool ok = service.Remove(user_id, (*json)["product_id"].asInt());

    Json::Value response;
    response["success"] = ok;
    callback(drogon::HttpResponse::newHttpJsonResponse(response));
}
