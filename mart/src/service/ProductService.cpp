#include "ProductService.h"

ProductService::ProductService(ProductRepository& repository) : repository_(repository) {}

std::vector<Product> ProductService::GetProducts() {
    return repository_.FindAll();
}
