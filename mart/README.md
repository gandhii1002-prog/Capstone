# KishoreMart — C++20 Marketplace Backend

A Review-1 starter implementation based on the capstone specification.

## Implemented for Review-1
1. User registration
2. User login
3. Session-backed authentication
4. Product browsing
5. Add/update/remove cart items
6. Mock checkout and order creation
7. Layered architecture:
   Controller -> Service -> Repository -> SQLite

## Technology
- C++20
- Drogon
- SQLite
- CMake
- vcpkg
- nlohmann/json

## Important
This is a Review-1 starter, not the complete Oct-10 capstone. Seller dashboard,
admin panel, reviews, deployment, tests, security hardening, and AI chatbot
must be completed later according to the specification.

## Build
Install vcpkg and make sure CMake can find it.

Example:

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<VCPKG_ROOT>/scripts/buildsystems/vcpkg.cmake
cmake --build build

## Run
./build/kishoremart

The server listens on http://localhost:8080

## API examples

Register:
POST /api/v1/auth/register
{
  "name": "Kishore",
  "email": "kishore@example.com",
  "password": "123456",
  "role": "BUYER"
}

Login:
POST /api/v1/auth/login
{
  "email": "kishore@example.com",
  "password": "123456"
}

Products:
GET /api/v1/products

Add to cart:
POST /api/v1/cart
{
  "product_id": 1,
  "quantity": 1
}

View cart:
GET /api/v1/cart

Checkout:
POST /api/v1/orders/checkout

Order history:
GET /api/v1/orders
