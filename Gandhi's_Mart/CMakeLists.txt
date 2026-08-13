cmake_minimum_required(VERSION 3.20)
project(GandhiMart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(GandhiMart
    src/main.cpp
    src/db/Database.cpp
    src/repository/UserRepository.cpp
    src/repository/ProductRepository.cpp
    src/repository/OrderRepository.cpp
    src/service/AuthService.cpp
    src/service/ProductService.cpp
    src/service/OrderService.cpp
    src/controller/AuthController.cpp
    src/controller/ProductController.cpp
    src/controller/OrderController.cpp
)

target_include_directories(GandhiMart PRIVATE src)

target_link_libraries(GandhiMart PRIVATE
    Drogon::Drogon
    unofficial::sqlite3::sqlite3
)

if (WIN32)
    target_compile_definitions(GandhiMart PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
