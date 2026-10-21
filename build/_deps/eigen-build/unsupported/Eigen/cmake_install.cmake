# Install script for directory: C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ENGO419_Lab6")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/AdolcForward"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/AlignedVector3"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/ArpackSupport"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/AutoDiff"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/BVH"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/EulerAngles"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/FFT"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/IterativeSolvers"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/KroneckerProduct"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/LevenbergMarquardt"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/MatrixFunctions"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/MPRealSupport"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/NNLS"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/NonLinearOptimization"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/NumericalDiff"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/OpenGLSupport"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/Polynomials"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/SparseExtra"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/SpecialFunctions"
    "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-src/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/MY PC/Documents/School Coding/ENGO419_Lab6/build/_deps/eigen-build/unsupported/Eigen/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
