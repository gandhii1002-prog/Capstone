# Gandhi Mart

A small marketplace capstone demo.

## Required functionality
- Register / Login
- Buyer and Seller roles
- Seller adds products
- Buyer browses products
- Search/filter products
- Add to cart
- View cart
- Place order
- Mock payment
- SQLite database with foreign keys
- C++20 + Drogon
- Controller -> Service -> Repository structure

## Project structure

backend/
  controller/
  service/
  repository/
  model/
db/schema.sql
public/
src/
CMakeLists.txt
vcpkg.json

## Windows setup

Use **Developer PowerShell for VS 2022** (not a normal PowerShell) so MSVC is available.

From the project folder:

```powershell
cmake --build build --config Release
.\build\Release\GandhiMart.exe
```

Open `http://localhost:8080`.

## End-to-end test

1. Register a seller.
2. Add a product.
3. Log out.
4. Register/login as a buyer.
5. Search for the product.
6. Add it to the cart.
7. Place the order.

The first run creates `Gandhi Mart.db` and initializes it from `db/schema.sql`.

## Demo note

This backend matches the supplied CampusMart implementation. Passwords are stored as entered and sessions are held in memory, so this is suitable for a capstone/demo rather than production deployment.
