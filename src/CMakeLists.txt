cmake_minimum_required(VERSION 3.5)

project(gists LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gists
    main.cpp
    gists.cpp gists.h
    httpdownloader.cpp httpdownloader.h
    inputhelper.cpp inputhelper.h
    jsonhelper.cpp jsonhelper.h
    )

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(gists PRIVATE curl)
target_link_libraries(gists PRIVATE nlohmann_json::nlohmann_json)
