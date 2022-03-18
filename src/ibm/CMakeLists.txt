# this file is used for the programme CMake,
# which allows us to build and compile the executable
# see https://cmake.org/cmake/help/latest/index.html

# minimum version of cmake
cmake_minimum_required(VERSION 3.10)

#### VARIABLES ####

# put executable name in variable, as we
# need it in multiple places
set(EXE_NAME "Weaning_duration")
set(TESTS_EXE "Weaning_duration_tests")

# make a library of the individual class
set(INDIVIDUAL_LIB "individual_lib")
# make a library of the simulation class
set(SIMULATION_LIB "simulation_lib")

# google test url
set(GOOGLETEST_URL "https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip") 


#### THE ACTUAL PROJECT FILE ####

# project name
project(Weaning_duration)

# the executable (i.e., the actual programme)
add_executable("${EXE_NAME}" weaning_duration.cpp)

add_library("${INDIVIDUAL_LIB}" individual.cpp)
add_library("${SIMULATION_LIB}" simulation.cpp)

# add the current dir in which the executable is being built
# as include dir, as there are a bunch of header files in there
target_include_directories("${EXE_NAME}" PUBLIC
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
    "${INDIVIDUAL_LIB}"
)
target_link_libraries(
    "${EXE_NAME}"
    "${SIMULATION_LIB}"
)


include(GoogleTest)
gtest_discover_tests("${EXE_NAME_IND_TEST}")


# run all tests directly after building
# see https://stackoverflow.com/questions/32901679/unit-testing-as-part-of-the-build 
#set(UNIT_TEST "${EXE_NAME_IND_TEST}")
#add_test(NAME "${UNIT_TEST}" COMMAND "${UNIT_TEST}")
#add_custom_command(
#    TARGET ${UNIT_TEST}
#    COMMENT "Run tests"
#    POST_BUILD
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures
#)
create_test_sourcelist(Tests
    all_tests.cpp # the c++ file in which all the source code from the other test files will be collected
    individual_tests.cpp # testing the individual library
    simulation_tests.cpp # testing the simulation library
)

# add a testing executable
add_executable("${TESTS_EXE}" "${Tests}")

# remove the test driver source code

# link libraries for the individual unit testing
target_link_libraries(
    "${TESTS_EXE}"
    "${INDIVIDUAL_LIB}"
)

# link libraries for the simulation unit testing
target_link_libraries(
    "${TESTS_EXE}"
    "${SIMULATION_LIB}"
)

target_link_libraries(
    "${TESTS_EXE}"
    gtest_main
)
