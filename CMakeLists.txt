cmake_minimum_required(VERSION 3.12.0)

project(data-structures VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(DATASTRUCTURES_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(DATASTRUCTURES_TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

find_package(GTest REQUIRED)

include_directories(${DATASTRUCTURES_INCLUDE_DIRS})

file(GLOB DATASTRUCTURES_TEST_SOURCES "${DATASTRUCTURES_TESTS_DIR}/*.cpp")

enable_testing()

foreach(TEST_SOURCE ${DATASTRUCTURES_TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_SOURCE})
	target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main)
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
