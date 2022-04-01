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
set(EXE_NAME_SIM_TEST "simulation_tests")

# make a library of the individual class
set(OVERALL_LIB "sensitive_windows_lib")

# google test url
set(GOOGLETEST_URL "https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip") 


#### THE ACTUAL PROJECT FILE ####

# project name
project(Weaning_duration)

# the executable (i.e., the actual programme)
add_executable("${EXE_NAME}" weaning_duration.cpp)
add_executable("${EXE_NAME_IND_TEST}" individual_tests.cpp)
add_executable("${EXE_NAME_SIM_TEST}" simulation_tests.cpp)

add_library("${OVERALL_LIB}" individual.cpp simulation.cpp)

# add the current dir in which the executable is being built
# as include dir, as there are a bunch of header files in there
target_include_directories("${EXE_NAME}" PUBLIC
    "${PROJECT_BINARY_DIR}"
    )
target_include_directories("${EXE_NAME_IND_TEST}" PUBLIC
    "${PROJECT_BINARY_DIR}"
    )
target_include_directories("${EXE_NAME_SIM_TEST}" PUBLIC
    "${PROJECT_BINARY_DIR}"
    )

# make sure it is c++11. Turns out that on a mac with clang
# you need to also add flags (eye-roll)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# now adding the google mock testing framework
# see: https://google.github.io/googletest/quickstart-cmake.html

# call cmake's FetchContent module
# see https://cmake.org/cmake/help/latest/module/FetchContent.html 
include(FetchContent)
FetchContent_Declare(
    googletest
    URL "${GOOGLETEST_URL}"
)

FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
    "${EXE_NAME}"
    "${OVERALL_LIB}" 
)
target_link_libraries(
    "${EXE_NAME_IND_TEST}"
    "${OVERALL_LIB}"
    gtest_main
)
target_link_libraries(
    "${EXE_NAME_SIM_TEST}"
    "${OVERALL_LIB}"
    gtest_main
)


include(GoogleTest)
gtest_discover_tests("${EXE_NAME_IND_TEST}")
gtest_discover_tests("${EXE_NAME_SIM_TEST}")


