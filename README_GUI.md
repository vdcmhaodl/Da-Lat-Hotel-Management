# Hotel Management System - Qt6 GUI

This is a comprehensive hotel management system with both console and graphical user interface versions.

## Features

### Manager Features
- Dashboard with hotel statistics
- Room management (add, remove, view rooms)
- Customer management (add, remove, view customers)
- Employee management (hire, fire, view employees)
- Booking reports and statistics
- Revenue reports
- System state save/load

### Employee Features
- Dashboard with daily statistics
- View available rooms
- Book rooms for customers
- Give discounts to customers
- View booking histories (hotel, customer, room)
- Lock/unlock rooms

### Customer Features
- Dashboard with personal booking info
- View available rooms
- Book rooms with date selection
- View and cancel current bookings
- View booking history
- View and pay bills
- View personal information

## Requirements

### For Building
- Qt6 (Core, Widgets, Gui modules)
- CMake 3.22 or higher
- C++17 compatible compiler
- MinGW or Visual Studio (on Windows)

### For Running
- Qt6 runtime libraries
- Windows 10/11 (for Windows build)

## Building the Project

### Windows (MinGW)
1. Install Qt6 and make sure it's in your PATH
2. Install CMake and MinGW
3. Open command prompt in project directory
4. Run: `build_gui.bat`

### Manual Build
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
```

## Running the Application

### GUI Version
```bash
.\build\bin\hotel_management_gui.exe
```

### Console Version
```bash
.\build\bin\hotel_management_console.exe
```

## Default Login Credentials

### Manager
- ID: Any (leave empty)
- Password: 31082025

### Employee
- Created through manager interface
- Default password: 12345

### Customer
- Register through login screen or created by manager/employee
- Default password: 12345

## Project Structure

```
├── include/           # Header files
├── src/              # Source files (console logic)
├── ui/               # Qt6 GUI files
├── data/             # Data storage
├── CMakeLists.txt    # Build configuration
├── build_gui.bat     # Windows build script
└── README_GUI.md     # This file
```

## GUI Components

### Login Window
- User type selection (Manager/Employee/Customer)
- Login form with ID and password
- Customer registration form
- Modern dark theme design

### Manager Window
- Tabbed interface with Dashboard, Room Management, Customer Management, Employee Management, and Reports
- Real-time statistics and data visualization
- Comprehensive management tools

### Employee Window
- Dashboard with daily statistics
- Room booking interface
- Customer service tools
- Report viewing capabilities

### Customer Window
- Personal dashboard
- Room browsing and booking
- Booking management
- Billing and payment interface
- Personal information view

## Data Persistence

The system automatically saves and loads data from `data/hotel_system.dat`. All bookings, customer information, and hotel state are preserved between sessions.




