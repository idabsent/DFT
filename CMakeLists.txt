# CMakeList.txt : CMake project for DFT, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.12)

include(CMakeDefinitions.cmake)

# Add source to this project's executable.
project(DFT
	DESCRIPTION ${LIBRARY_DESCRIPTION}
	VERSION ${LIBRARY_VERSION}
	LANGUAGES CXX
)

set(CMAKE_VERBOSE_MAKEFILE True)

set(INCLUDE_DIR include/)
set(SOURCES_DIR src/)

configure_file(config.h.in config.h)
add_subdirectory(${SOURCES_DIR})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} 
	PUBLIC ${SRCS})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DFT PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
include(CTest)

add_subdirectory(tests)

enable_testing()
