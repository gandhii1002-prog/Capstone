cmake_minimum_required(VERSION 3.25)
project(KishoreMart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(kishoremart
    src/main.cpp
    src/model/User.h
    src/model/Product.h
    src/model/CartItem.h
    src/model/Order.h
    src/repository/UserRepository.h
    src/repository/UserRepository.cpp
    src/repository/ProductRepository.h
    src/repository/ProductRepository.cpp
    src/repository/CartRepository.h
    src/repository/CartRepository.cpp
    src/repository/OrderRepository.h
    src/repository/OrderRepository.cpp
    src/service/AuthService.h
    src/service/AuthService.cpp
    src/service/ProductService.h
    src/service/ProductService.cpp
    src/service/CartService.h
    src/service/CartService.cpp
    src/service/OrderService.h
    src/service/OrderService.cpp
    src/controller/AuthController.h
    src/controller/AuthController.cpp
    src/controller/ProductController.h
    src/controller/ProductController.cpp
    src/controller/CartController.h
    src/controller/CartController.cpp
    src/controller/OrderController.h
    src/controller/OrderController.cpp
    src/util/Database.h
    src/util/Database.cpp
)

target_include_directories(kishoremart PRIVATE src)
target_link_libraries(kishoremart PRIVATE Drogon::Drogon SQLite::SQLite3 nlohmann_json::nlohmann_json)

if (MSVC)
    target_compile_options(kishoremart PRIVATE /W4)
else()
    target_compile_options(kishoremart PRIVATE -Wall -Wextra -Wpedantic)
endif()
