cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-O3 -Wall -Wextra)

project(MD5_PIN_Brute_Force)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(MD5_PIN_BRUTE_FORCE_SOURCE "src/MD5Array.cpp"
                               "src/PINBruteForce.cpp"
                               "src/main.cpp")
set(MD5_PIN_BRUTE_FORCE_HEADERS "include")

add_executable(MD5_PIN_Brute_Force ${MD5_PIN_BRUTE_FORCE_SOURCE})

target_include_directories(MD5_PIN_Brute_Force PUBLIC ${MD5_PIN_BRUTE_FORCE_HEADERS})

target_link_libraries(MD5_PIN_Brute_Force ssl)
target_link_libraries(MD5_PIN_Brute_Force crypto)