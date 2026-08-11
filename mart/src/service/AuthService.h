#pragma once
#include "../repository/UserRepository.h"
#include <string>

class AuthService {
public:
    explicit AuthService(UserRepository& repository);
    bool Register(const std::string& name, const std::string& email,
                  const std::string& password, const std::string& role);
    std::optional<User> Login(const std::string& email, const std::string& password);

private:
    UserRepository& repository_;
    static std::string DemoHash(const std::string& password);
};
