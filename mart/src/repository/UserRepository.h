#pragma once
#include "../model/User.h"
#include <optional>
#include <string>

class UserRepository {
public:
    bool Create(const User& user);
    std::optional<User> FindByEmail(const std::string& email);
};
