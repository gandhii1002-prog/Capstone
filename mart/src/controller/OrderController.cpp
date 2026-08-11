#include "OrderController.h"
#include "../repository/OrderRepository.h"
#include "../repository/CartRepository.h"
#include "../repository/ProductRepository.h"
#include "../service/OrderService.h"

void OrderController::Checkout(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    int buyer_id = req->session()->getOptional<int>("user_id").value_or(0);
    if (buyer_id == 0) {
        auto r = drogon::HttpResponse::newHttpResponse();
        r->setStatusCode(drogon::k401Unauthorized);
        callback(r);
        return;
    }

    OrderRepository order_repo;
    CartRepository cart_repo;
    ProductRepository product_repo;
    OrderService service(order_repo, cart_repo, product_repo);

    int order_id = 0;
    bool ok = service.Checkout(buyer_id, order_id);

    Json::Value response;
    response["success"] = ok;
    response["message"] = ok ? "Mock payment confirmed and order created"
                             : "Checkout failed";
    if (ok) response["order_id"] = order_id;

    callback(drogon::HttpResponse::newHttpJsonResponse(response));
}
