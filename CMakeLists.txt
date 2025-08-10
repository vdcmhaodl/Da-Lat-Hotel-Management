cmake_minimum_required(VERSION 3.10)
project(HotelManagement)

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
    "bin/*.o"  # If you have object files to link
)

# Collect all header files
file(GLOB HEADERS
    "include/*.h"
)

# Create executable
add_executable(hotel_management ${SOURCES} ${HEADERS})

# If you need to link any libraries, add them here
# target_link_libraries(hotel_management library_name)

# Set compiler flags for Windows
if(WIN32)
    target_compile_options(hotel_management PRIVATE
        /W3  # Warning level 3
        /EHsc  # Exception handling
    )
endif()

# Set compiler flags for GCC/Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(hotel_management PRIVATE
        -Wall
        -Wextra
        -pedantic
    )
endif()

# Debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Print some information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Source files: ${SOURCES}")