cmake_minimum_required(VERSION 3.5)

project(fashio_mnist)

find_package(Boost 1.65.0 COMPONENTS system unit_test_framework REQUIRED)
add_executable(fashio_mnist main.cpp LogregClassifier.h helpers.h)
add_executable(test tests.cpp)

set(TARGETS fashio_mnist test)

foreach(target ${TARGETS})
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
            CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE "-g;-Wall;-Wextra;-Werror;-pedantic")
        target_link_libraries(${target} PUBLIC pthread)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE "/W4;/WX")
    endif()
    target_compile_features(${target} PUBLIC cxx_std_17)
endforeach(target IN ${TARGETS})

target_link_libraries(fashio_mnist PUBLIC Boost::system)