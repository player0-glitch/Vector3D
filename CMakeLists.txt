cmake_minimum_required(VERSION 3.30.5)
project(o)
#Setting C++ standard 
set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
#hopefully this allows to create compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#include directory 
include_directories(${CMAKE_SOURCE_DIR}/include)

#sources directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

#Add executable 
add_executable(${PROJECT_NAME} ${SOURCES})

#Setting compile flags 
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -std=c++23 -g -O0) #just to make sure compile with c++ 20

#setting up SDL2 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})


#Google Test Suite of Cpp tests
#Enabling the fetch content modules
include(FetchContent)

#Fetch the content 
FetchContent_Declare(include(FetchContent))
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)

#Make Google Test available
FetchContent_MakeAvailable(googletest)

#Adding my executables for my test cases
set(SOURCES ${CMAKE_SOURCE_DIR}/tests/tests.cc)
enable_testing()
add_executable(my_test tests/tests.cc)

# Linking GoogleTest and GoogleMock to test executable
target_link_libraries(my_test PRIVATE gtest_main gtest gmock)

include(GoogleTest)
gtest_discover_tests(my_test)
# ATTEMPT 1: FAILED Registering tests 
# add_test(NAME EngineTest COMMAND my_test)


