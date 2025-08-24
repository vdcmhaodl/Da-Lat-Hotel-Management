cmake_minimum_required(VERSION 3.10)
project(HotelManagement LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(include)

# Collect all source files
file(GLOB SOURCES
    "src/*.cpp"
    "main.cpp"
)

# Collect all header files (optional, just for IDE)
file(GLOB HEADERS "include/*.h")

# Create executable
add_executable(hotel_management ${SOURCES} ${HEADERS})

# Compiler flags
if(MSVC)
    target_compile_options(hotel_management PRIVATE /W3 /EHsc)
else()
    target_compile_options(hotel_management PRIVATE -Wall -Wextra -pedantic)
endif()

# Debug/Release flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Print some info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Source files: ${SOURCES}")