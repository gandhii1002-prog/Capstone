#include "AuthService.h"

AuthService::AuthService(UserRepository& repository) : repository_(repository) {}

std::string AuthService::DemoHash(const std::string& password) {
    // Review-1 placeholder only.
    // Replace with libsodium Argon2id before final security review.
    return "DEMO_HASH:" + password;
}

bool AuthService::Register(const std::string& name, const std::string& email,
                           const std::string& password, const std::string& role) {
    if (name.empty() || email.empty() || password.size() < 4) return false;
    if (role != "BUYER" && role != "SELLER") return false;
    if (repository_.FindByEmail(email).has_value()) return false;

    User user;
    user.name = name;
    user.email = email;
    user.password_hash = DemoHash(password);
    user.role = role;
    return repository_.Create(user);
}

std::optional<User> AuthService::Login(const std::string& email, const std::string& password) {
    auto user = repository_.FindByEmail(email);
    if (!user.has_value()) return std::nullopt;

    if (user->password_hash != DemoHash(password)) return std::nullopt;
    return user;
}
