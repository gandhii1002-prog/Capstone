# Review-1 explanation sheet

## Project
KishoreMart is a multi-seller e-commerce marketplace backend written in C++20 using Drogon.

## Module 1: Authentication
Registration:
Browser -> AuthController -> AuthService -> UserRepository -> Database

Login:
Browser -> AuthController -> AuthService -> UserRepository -> Database
-> session is created after successful login.

## Module 2: Core shopping flow
Browse:
Browser -> ProductController -> ProductService -> ProductRepository -> Database

Cart:
Browser -> CartController -> CartService -> CartRepository -> Database

Checkout:
Browser -> OrderController -> OrderService
-> validate cart and stock
-> mock payment
-> create order
-> create order items
-> reduce stock
-> clear cart

## Classes
Model classes represent data.
Controller classes handle HTTP requests.
Service classes contain business rules.
Repository classes handle database access.

## Important viva sentence
"Controller receives the request, Service applies business logic, Repository performs database operations, and the Database stores persistent data."

## Important warning
The current Review-1 starter uses a demonstration password hash so it can be kept small and easy to understand.
The capstone specification requires Argon2id through libsodium. Replace DemoHash with crypto_pwhash_str / crypto_pwhash_str_verify before treating the project as final.
