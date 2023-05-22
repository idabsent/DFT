cmake_minimum_required(VERSION 3.15)

find_package(GTest 1.13 REQUIRED COMPONENTS gtest gtest_main)

list(APPEND TESTS TestDFT.cpp)
list(APPEND TESTS TestTools.cpp)

include(CMakePrintHelpers)
cmake_print_variables(TESTS)

add_executable(UnitTestDFT ${TESTS})

target_include_directories(UnitTestDFT 
	PRIVATE ${GTEST_INCLUDE_DIRS}
	PRIVATE ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR})
target_link_libraries(UnitTestDFT 
	PRIVATE GTest::gtest GTest::Main
	PRIVATE DFT
)
target_compile_features(UnitTestDFT 
	PUBLIC cxx_std_20)

include(GoogleTest)
gtest_add_tests(
	TARGET UnitTestDFT
	SOURCES ${TESTS})
