cmake_minimum_required(VERSION 3.22)
project(HotelManagement LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Qt6 automatic MOC, UIC and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(include)

# Collect all source files (console version)
file(GLOB CONSOLE_SOURCES
    "src/*.cpp"
    "main.cpp"
)

# GUI source files
set(GUI_SOURCES
    src/hotel.cpp
    src/HotelManagement.cpp
    src/custormer_function.cpp
    src/custormer_getset.cpp
    src/custormer_init.cpp
    src/custormer_check.cpp
    src/employee_function.cpp
    src/employee_init.cpp
    src/hotel_floor.cpp
    src/init_price_type.cpp
    src/manager_function.cpp
    src/manager_init.cpp
    src/person_check.cpp
    src/person_function.cpp
    src/person_getset.cpp
    src/person_init.cpp
    src/room_basic.cpp
    src/room_concrete.cpp
    src/room_director.cpp
    src/room_functions.cpp
    src/room_init.cpp
    src/room_item.cpp
    
    # GUI source files
    ui/main_gui.cpp
    ui/login_window.cpp
    ui/manager_window.cpp
    ui/employee_window.cpp
    ui/customer_window.cpp
    ui/room_management_widget.cpp
    ui/customer_management_widget.cpp
    ui/employee_management_widget.cpp
    ui/booking_widget.cpp
    ui/room_booking_dialog.cpp
    ui/add_customer_dialog.cpp
    ui/add_employee_dialog.cpp
)

# Collect all header files
file(GLOB HEADERS "include/*.h")

# Create console executable
add_executable(hotel_management_console ${CONSOLE_SOURCES} ${HEADERS})

# Create GUI executable
add_executable(hotel_management_gui ${GUI_SOURCES} ${HEADERS})

# Link Qt6 libraries to GUI version
target_link_libraries(hotel_management_gui Qt6::Core Qt6::Widgets Qt6::Gui)

# Compiler flags
if(MSVC)
    target_compile_options(hotel_management_console PRIVATE /W3 /EHsc)
    target_compile_options(hotel_management_gui PRIVATE /W3 /EHsc)
else()
    target_compile_options(hotel_management_console PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(hotel_management_gui PRIVATE -Wall -Wextra -pedantic)
endif()

# Debug/Release flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Copy data folder to build directory
add_custom_command(TARGET hotel_management_gui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:hotel_management_gui>/data)

# Print some info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Console sources: ${CONSOLE_SOURCES}")
message(STATUS "GUI sources: ${GUI_SOURCES}")