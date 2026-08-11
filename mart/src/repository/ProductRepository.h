#pragma once
#include "../model/Product.h"
#include <vector>

class ProductRepository {
public:
    std::vector<Product> FindAll();
    std::optional<Product> FindById(int id);
};
