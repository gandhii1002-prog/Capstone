# Gandhi's Mart

A full-stack campus marketplace using the supplied Gandhi's Mart frontend and the working C++/Drogon/SQLite backend architecture from CampusMart_Final.

## Included

- Gandhi's Mart frontend preserved exactly as supplied.
- Buyer/seller registration and login.
- Authenticated sessions with bearer tokens.
- Seller product management.
- Product search and category filtering.
- Buyer cart and checkout.
- SQLite database with foreign keys.
- Controller -> Service -> Repository backend structure.
- Drogon API + static frontend served on port 8080.

## API

- POST `/api/auth/register`
- POST `/api/auth/login`
- GET `/api/auth/me`
- GET `/api/products`
- POST `/api/products`
- PUT `/api/products/{id}`
- DELETE `/api/products/{id}`
- GET `/api/cart`
- POST `/api/cart`
- POST `/api/orders`

## Requirements

C++20, CMake 3.20+, vcpkg, Drogon and SQLite3.

The included `vcpkg.json` declares Drogon and SQLite3.

## macOS / Linux

Set `VCPKG_ROOT` to your vcpkg installation, then from this project folder:

```bash
cmake --preset default
cmake --build build
./build/GandhiMart
```

Open `http://localhost:8080`.

Without the preset:

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/GandhiMart
```

## Windows

Open Developer PowerShell for VS 2022:

```powershell
cmake --preset windows
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
