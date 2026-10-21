CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(ENGO419_Lab6 LANGUAGES CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/5.0.0/eigen-5.0.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(eigen)

add_executable(ENGO419_Lab6
    main.cpp
    functions.cpp
    functions.h     
)   

target_link_libraries(ENGO419_Lab6
    PRIVATE Eigen3::Eigen)