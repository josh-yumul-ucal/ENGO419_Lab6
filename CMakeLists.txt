CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(ENGO419_Lab6 LANGUAGES CXX)

# The original CMAKE_C_STANDARD setting only applied to C, but this project
# builds C++ sources. Set the C++ standard so the compiler uses C++17.
set(CMAKE_CXX_STANDARD 17)
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

FetchContent_Declare(
    boost_math
    GIT_REPOSITORY https://github.com/boostorg/math
    GIT_TAG boost-1.92.0
    GIT_SHALLOW TRUE
)

set(BOOST_MATH_STANDALONE ON)
FetchContent_MakeAvailable(boost_math)

target_link_libraries(ENGO419_Lab6 PRIVATE
    Eigen3::Eigen
    Boost::math
)