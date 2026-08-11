#pragma once
#include "../repository/ProductRepository.h"

class ProductService {
public:
    explicit ProductService(ProductRepository& repository);
    std::vector<Product> GetProducts();

private:
    ProductRepository& repository_;
};
