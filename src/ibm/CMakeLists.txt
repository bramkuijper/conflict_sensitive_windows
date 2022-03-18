# this file is used for the programme CMake,
# which allows us to build and compile the executable
# see https://cmake.org/cmake/help/latest/index.html

# minimum version of cmake
cmake_minimum_required(VERSION 3.10)

#### VARIABLES ####

# put executable name in variable, as we
# need it in multiple places
set(EXE_NAME "Weaning_duration")
set(EXE_NAME_IND_TEST "individual_tests")

# google test url
set(GOOGLETEST_URL "https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip") 


#### THE ACTUAL PROJECT FILE ####

# project name
project(Weaning_duration)

# the executable (i.e., the actual programme)
add_executable("${EXE_NAME}" weaning_duration.cpp)

# add the current dir in which the executable is being built
# as include dir, as there are a bunch of header files in there
target_include_directories("${EXE_NAME}" PUBLIC
    "${PROJECT_BINARY_DIR}"
    )

# now adding the google mock testing framework
# see: https://google.github.io/googletest/quickstart-cmake.html
set(CMAKE_CXX_STANDARD 11)

# call cmake's FetchContent module
# see https://cmake.org/cmake/help/latest/module/FetchContent.html 
include(FetchContent)
FetchContent_Declare(
    googletest
    URL "${GOOGLETEST_URL}"
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    "${EXE_NAME_IND_TEST}"
    individual_tests.cpp)

target_link_libraries(
    "${EXE_NAME_IND_TEST}"
    gtest_main
)

include(GoogleTest)
gtest_discover_tests("${EXE_NAME_IND_TEST}")


