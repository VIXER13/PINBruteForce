cmake_minimum_required(VERSION 3.10)

project(MD5Utils)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(MD5_UTILS_SOURSE "src/MD5Array.cpp"
                     "src/PINBruteForce.cpp")
set(MD5_UTILS_HEADERS "include")

add_library(MD5Utils STATIC ${MD5_UTILS_SOURSE})

target_include_directories(MD5Utils PUBLIC ${MD5_UTILS_HEADERS})

target_link_libraries(MD5Utils ssl)
target_link_libraries(MD5Utils crypto)