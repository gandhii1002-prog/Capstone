#include "AuthController.h"
#include "../service/AuthService.h"
#include "../repository/UserRepository.h"

void AuthController::Register(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    auto json = req->getJsonObject();
    if (!json) {
        callback(drogon::HttpResponse::newHttpJsonResponse(Json::Value("Invalid JSON")));
        return;
    }

    UserRepository repository;
    AuthService service(repository);

    const std::string name = (*json)["name"].asString();
    const std::string email = (*json)["email"].asString();
    const std::string password = (*json)["password"].asString();
    const std::string role = (*json)["role"].asString();

    bool ok = service.Register(name, email, password, role);

    Json::Value response;
    response["success"] = ok;
    response["message"] = ok ? "Registration successful" : "Registration failed";
    callback(drogon::HttpResponse::newHttpJsonResponse(response));
}

void AuthController::Login(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

    auto json = req->getJsonObject();
    if (!json) {
        callback(drogon::HttpResponse::newHttpJsonResponse(Json::Value("Invalid JSON")));
        return;
    }

    UserRepository repository;
    AuthService service(repository);

    auto user = service.Login((*json)["email"].asString(),
                              (*json)["password"].asString());

    Json::Value response;
    response["success"] = user.has_value();

    if (user.has_value()) {
        response["message"] = "Login successful";
        response["user_id"] = user->id;
        response["role"] = user->role;
        req->session()->insert("user_id", user->id);
        req->session()->insert("role", user->role);
    } else {
        response["message"] = "Invalid email or password";
    }

    callback(drogon::HttpResponse::newHttpJsonResponse(response));
}
