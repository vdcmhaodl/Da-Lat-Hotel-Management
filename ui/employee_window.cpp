#include "employee_window.h"
#include "../include/customer.h"
#include <QDate>
#include <sstream>
#include <iostream>

EmployeeWindow::EmployeeWindow(HotelManagementSystem *hotelSystem, int employeeId, QWidget *parent)
    : QMainWindow(parent)
    , m_hotelSystem(hotelSystem)
    , m_employeeId(employeeId)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupStyles();
    connectSignals();
    updateDashboard();
    onViewRooms(); // Load rooms by default
    
    setWindowTitle(QString("Hotel Management System - Employee Dashboard (ID: %1)").arg(employeeId));
    setMinimumSize(1000, 700);
    resize(1200, 800);
}

EmployeeWindow::~EmployeeWindow()
{
    // Save system state when closing
    if (m_hotelSystem) {
        m_hotelSystem->saveSystemState();
    }
}

void EmployeeWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Welcome header
    QString employeeName = "Employee";
    try {
        manager& mgr = m_hotelSystem->getManager();
        std::vector<IPerson*> employees = mgr.getEmployeeList();
        
        for (IPerson* person : employees) {
            if (person && person->getID() == m_employeeId) {
                // Cast to employee to get name
                employee* emp = dynamic_cast<employee*>(person);
                if (emp) {
                    employeeName = QString::fromStdString(emp->getName());
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        qDebug() << "Error getting employee name:" << e.what();
    }
    
    m_welcomeLabel = new QLabel(QString("Welcome, %1").arg(employeeName));
    m_welcomeLabel->setObjectName("welcomeLabel");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_welcomeLabel);
    
    // Tab widget
    m_tabWidget = new QTabWidget();
    m_tabWidget->setObjectName("mainTabWidget");
    
    // Dashboard tab
    setupDashboard();
    
    // Booking section
    setupBookingSection();
    
    // Room view tab
    setupRoomView();
    
    // Customer management tab
    setupCustomerManagement();
    
    // Reports tab
    setupReports();
    
    mainLayout->addWidget(m_tabWidget);
}

void EmployeeWindow::setupDashboard()
{
    m_dashboardWidget = new QWidget();
    QVBoxLayout *dashboardLayout = new QVBoxLayout(m_dashboardWidget);
    dashboardLayout->setSpacing(20);
    dashboardLayout->setContentsMargins(20, 20, 20, 20);
    
    // Statistics cards
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    // Available rooms
    QGroupBox *availableRoomsGroup = new QGroupBox("Available Rooms");
    availableRoomsGroup->setObjectName("statsGroup");
    QVBoxLayout *availableLayout = new QVBoxLayout(availableRoomsGroup);
    
    m_availableRoomsLabel = new QLabel("Available: 0");
    m_availableRoomsLabel->setObjectName("statLabel");
    availableLayout->addWidget(m_availableRoomsLabel);
    
    // Today's bookings
    QGroupBox *todayBookingsGroup = new QGroupBox("Today's Bookings");
    todayBookingsGroup->setObjectName("statsGroup");
    QVBoxLayout *todayLayout = new QVBoxLayout(todayBookingsGroup);
    
    m_todayBookingsLabel = new QLabel("Bookings: 0");
    m_todayBookingsLabel->setObjectName("statLabel");
    todayLayout->addWidget(m_todayBookingsLabel);
    
    // Total customers
    QGroupBox *totalCustomersGroup = new QGroupBox("Total Customers");
    totalCustomersGroup->setObjectName("statsGroup");
    QVBoxLayout *customersLayout = new QVBoxLayout(totalCustomersGroup);
    
    m_totalCustomersLabel = new QLabel("Customers: 0");
    m_totalCustomersLabel->setObjectName("statLabel");
    customersLayout->addWidget(m_totalCustomersLabel);
    
    // Occupied rooms
    QGroupBox *occupiedRoomsGroup = new QGroupBox("Occupied Rooms");
    occupiedRoomsGroup->setObjectName("statsGroup");
    QVBoxLayout *occupiedLayout = new QVBoxLayout(occupiedRoomsGroup);
    
    m_occupiedRoomsLabel = new QLabel("Occupied: 0");
    m_occupiedRoomsLabel->setObjectName("statLabel");
    occupiedLayout->addWidget(m_occupiedRoomsLabel);
    
    statsLayout->addWidget(availableRoomsGroup);
    statsLayout->addWidget(occupiedRoomsGroup);
    statsLayout->addWidget(totalCustomersGroup);
    statsLayout->addWidget(todayBookingsGroup);
    statsLayout->addStretch();
    
    dashboardLayout->addLayout(statsLayout);
    
    // Quick actions
    QGroupBox *quickActionsGroup = new QGroupBox("Quick Actions");
    quickActionsGroup->setObjectName("statsGroup");
    QHBoxLayout *quickActionsLayout = new QHBoxLayout(quickActionsGroup);
    
    QPushButton *viewRoomsBtn = new QPushButton("View Rooms");
    QPushButton *bookRoomBtn = new QPushButton("Book Room");
    QPushButton *giveDiscountBtn = new QPushButton("Give Discount");
    QPushButton *refreshBtn = new QPushButton("Refresh Data");
    
    viewRoomsBtn->setObjectName("actionButton");
    bookRoomBtn->setObjectName("actionButton");
    giveDiscountBtn->setObjectName("actionButton");
    refreshBtn->setObjectName("actionButton");
    
    connect(viewRoomsBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRooms);
    connect(bookRoomBtn, &QPushButton::clicked, [this]() { m_tabWidget->setCurrentIndex(1); });
    connect(giveDiscountBtn, &QPushButton::clicked, this, &EmployeeWindow::onGiveDiscount);
    connect(refreshBtn, &QPushButton::clicked, this, &EmployeeWindow::onRefreshData);
    
    quickActionsLayout->addWidget(viewRoomsBtn);
    quickActionsLayout->addWidget(bookRoomBtn);
    quickActionsLayout->addWidget(giveDiscountBtn);
    quickActionsLayout->addWidget(refreshBtn);
    quickActionsLayout->addStretch();
    
    dashboardLayout->addWidget(quickActionsGroup);
    dashboardLayout->addStretch();
    
    m_tabWidget->addTab(m_dashboardWidget, "Dashboard");
}

void EmployeeWindow::setupBookingSection()
{
    m_bookingWidget = new QWidget();
    QVBoxLayout *bookingLayout = new QVBoxLayout(m_bookingWidget);
    bookingLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *bookingTitle = new QLabel("Book Room for Customer");
    bookingTitle->setObjectName("sectionTitle");
    bookingTitle->setAlignment(Qt::AlignCenter);
    bookingLayout->addWidget(bookingTitle);
    
    // Available rooms table
    QGroupBox *availableRoomsGroup = new QGroupBox("Available Rooms");
    availableRoomsGroup->setObjectName("tableGroup");
    QVBoxLayout *roomsLayout = new QVBoxLayout(availableRoomsGroup);
    
    // Room table
    m_availableRoomsTable = new QTableWidget();
    m_availableRoomsTable->setObjectName("dataTable");
    m_availableRoomsTable->setAlternatingRowColors(true);
    m_availableRoomsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_availableRoomsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    QStringList roomHeaders;
    roomHeaders << "Room ID" << "Floor" << "Type" << "Beds" << "Capacity" << "Amenities" << "Price/Night" << "Status";
    m_availableRoomsTable->setColumnCount(roomHeaders.size());
    m_availableRoomsTable->setHorizontalHeaderLabels(roomHeaders);
    
    // Set column widths - make Type column wider for full names
    m_availableRoomsTable->setColumnWidth(0, 80);  // Room ID
    m_availableRoomsTable->setColumnWidth(1, 60);  // Floor
    m_availableRoomsTable->setColumnWidth(2, 250); // Type
    m_availableRoomsTable->setColumnWidth(3, 80);  // Beds
    m_availableRoomsTable->setColumnWidth(4, 80);  // Capacity
    m_availableRoomsTable->setColumnWidth(5, 200); // Amenities
    m_availableRoomsTable->setColumnWidth(6, 100); // Price/Night
    m_availableRoomsTable->horizontalHeader()->setStretchLastSection(true); // Status stretches
    
    // Connect room selection
    connect(m_availableRoomsTable, &QTableWidget::itemSelectionChanged, this, &EmployeeWindow::onAvailableRoomSelected);
    
    roomsLayout->addWidget(m_availableRoomsTable);
    
    // Action buttons
    QHBoxLayout *roomActionLayout = new QHBoxLayout();
    
    QPushButton *refreshAvailableBtn = new QPushButton("Refresh Available Rooms");
    refreshAvailableBtn->setObjectName("actionButton");
    connect(refreshAvailableBtn, &QPushButton::clicked, this, &EmployeeWindow::refreshAvailableRooms);
    
    QPushButton *viewRoomDetailsBtn = new QPushButton("View Room Details");
    viewRoomDetailsBtn->setObjectName("actionButton");
    connect(viewRoomDetailsBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRoomDetails);
    
    roomActionLayout->addWidget(refreshAvailableBtn);
    roomActionLayout->addWidget(viewRoomDetailsBtn);
    roomActionLayout->addStretch();
    
    roomsLayout->addLayout(roomActionLayout);
    
    bookingLayout->addWidget(availableRoomsGroup);
    
    // Booking form
    QGroupBox *bookingFormGroup = new QGroupBox("Booking Information");
    bookingFormGroup->setObjectName("formGroup");
    QGridLayout *formLayout = new QGridLayout(bookingFormGroup);
    
    // Customer ID
    QLabel *customerIdLabel = new QLabel("Customer ID:");
    m_customerIdEdit = new QLineEdit();
    m_customerIdEdit->setPlaceholderText("Enter customer ID");
    m_customerIdEdit->setObjectName("lineEdit");
    
    // Room ID
    QLabel *roomIdLabel = new QLabel("Room ID:");
    m_roomIdEdit = new QLineEdit();
    m_roomIdEdit->setPlaceholderText("Enter room ID");
    m_roomIdEdit->setObjectName("lineEdit");
    
    // Check-in date
    QLabel *checkinLabel = new QLabel("Check-in Date:");
    m_checkinDateEdit = new QDateEdit(QDate::currentDate());
    m_checkinDateEdit->setCalendarPopup(true);
    m_checkinDateEdit->setObjectName("dateEdit");
    
    // Check-out date
    QLabel *checkoutLabel = new QLabel("Check-out Date:");
    m_checkoutDateEdit = new QDateEdit(QDate::currentDate().addDays(1));
    m_checkoutDateEdit->setCalendarPopup(true);
    m_checkoutDateEdit->setObjectName("dateEdit");
    
    // Book button
    m_bookRoomBtn = new QPushButton("Book Room");
    m_bookRoomBtn->setObjectName("primaryButton");
    
    formLayout->addWidget(customerIdLabel, 0, 0);
    formLayout->addWidget(m_customerIdEdit, 0, 1);
    formLayout->addWidget(roomIdLabel, 1, 0);
    formLayout->addWidget(m_roomIdEdit, 1, 1);
    formLayout->addWidget(checkinLabel, 2, 0);
    formLayout->addWidget(m_checkinDateEdit, 2, 1);
    formLayout->addWidget(checkoutLabel, 3, 0);
    formLayout->addWidget(m_checkoutDateEdit, 3, 1);
    formLayout->addWidget(m_bookRoomBtn, 4, 0, 1, 2);
    
    bookingLayout->addWidget(bookingFormGroup);
    bookingLayout->addStretch();
    
    m_tabWidget->addTab(m_bookingWidget, "Book Room");
    
    // Load available rooms data initially
    refreshAvailableRooms();
}

void EmployeeWindow::setupRoomView()
{
    QWidget *roomWidget = new QWidget();
    QVBoxLayout *roomLayout = new QVBoxLayout(roomWidget);
    
    QLabel *roomTitle = new QLabel("Rooms Overview");
    roomTitle->setObjectName("sectionTitle");
    roomTitle->setAlignment(Qt::AlignCenter);
    roomLayout->addWidget(roomTitle);
    
    // Room count label
    m_roomCountLabel = new QLabel("Total Rooms: 0");
    m_roomCountLabel->setObjectName("countLabel");
    roomLayout->addWidget(m_roomCountLabel);
    
    // Room table
    m_roomTable = new QTableWidget();
    m_roomTable->setObjectName("dataTable");
    m_roomTable->setAlternatingRowColors(true);
    m_roomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QStringList headers;
    headers << "Room ID" << "Floor" << "Type" << "Beds" << "Capacity" << "Amenities" << "Price/Night" << "Status" << "Current Guest" << "Available";
    m_roomTable->setColumnCount(headers.size());
    m_roomTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths - make Type column wider for full names
    m_roomTable->setColumnWidth(0, 80);  // Room ID
    m_roomTable->setColumnWidth(1, 60);  // Floor
    m_roomTable->setColumnWidth(2, 250); // Type
    m_roomTable->setColumnWidth(3, 80);  // Beds
    m_roomTable->setColumnWidth(4, 80);  // Capacity
    m_roomTable->setColumnWidth(5, 200); // Amenities
    m_roomTable->setColumnWidth(6, 100); // Price/Night
    m_roomTable->setColumnWidth(7, 80);  // Status
    m_roomTable->setColumnWidth(8, 120); // Current Guest
    m_roomTable->horizontalHeader()->setStretchLastSection(true); // Available stretches
    
    roomLayout->addWidget(m_roomTable);
    
    // Room control buttons
    QHBoxLayout *roomControlLayout = new QHBoxLayout();
    
    // Refresh button
    QPushButton *refreshRoomsBtn = new QPushButton("Refresh Rooms");
    refreshRoomsBtn->setObjectName("actionButton");
    connect(refreshRoomsBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRooms);
    
    // Lock room button
    QPushButton *lockRoomBtn = new QPushButton("Lock Room");
    lockRoomBtn->setObjectName("actionButton");
    connect(lockRoomBtn, &QPushButton::clicked, this, &EmployeeWindow::onLockRoom);
    
    // Unlock room button
    QPushButton *unlockRoomBtn = new QPushButton("Unlock Room");
    unlockRoomBtn->setObjectName("actionButton");
    connect(unlockRoomBtn, &QPushButton::clicked, this, &EmployeeWindow::onUnlockRoom);
    
    // View room details button
    QPushButton *viewDetailsBtn = new QPushButton("View Room Details");
    viewDetailsBtn->setObjectName("actionButton");
    connect(viewDetailsBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRoomDetails);
    
    roomControlLayout->addWidget(refreshRoomsBtn);
    roomControlLayout->addWidget(lockRoomBtn);
    roomControlLayout->addWidget(unlockRoomBtn);
    roomControlLayout->addWidget(viewDetailsBtn);
    roomControlLayout->addStretch();
    
    roomLayout->addLayout(roomControlLayout);
    
    m_tabWidget->addTab(roomWidget, "View Rooms");
}

void EmployeeWindow::setupCustomerManagement()
{
    m_customerWidget = new QWidget();
    QVBoxLayout *customerLayout = new QVBoxLayout(m_customerWidget);
    
    QLabel *customerTitle = new QLabel("Customer Management");
    customerTitle->setObjectName("sectionTitle");
    customerTitle->setAlignment(Qt::AlignCenter);
    customerLayout->addWidget(customerTitle);
    
    // Customer table
    m_customerTable = new QTableWidget();
    m_customerTable->setObjectName("dataTable");
    m_customerTable->setAlternatingRowColors(true);
    m_customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_customerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    QStringList customerHeaders;
    customerHeaders << "Customer ID" << "Name" << "Email" << "Phone" << "Gender" << "Total Bookings";
    m_customerTable->setColumnCount(customerHeaders.size());
    m_customerTable->setHorizontalHeaderLabels(customerHeaders);
    
    // Set column widths - make Name and Email columns wider for full information
    m_customerTable->setColumnWidth(0, 100); // Customer ID
    m_customerTable->setColumnWidth(1, 200); // Name - wider for full names
    m_customerTable->setColumnWidth(2, 200); // Email - wider for full email addresses
    m_customerTable->setColumnWidth(3, 120); // Phone
    m_customerTable->setColumnWidth(4, 80);  // Gender
    m_customerTable->horizontalHeader()->setStretchLastSection(true); // Total Bookings stretches
    
    customerLayout->addWidget(m_customerTable);
    
    // Connect customer selection to auto-fill customer ID
    connect(m_customerTable, &QTableWidget::itemSelectionChanged, this, &EmployeeWindow::onCustomerSelected);
    
    // Control buttons
    QHBoxLayout *customerControlLayout = new QHBoxLayout();
    
    QPushButton *refreshCustomersBtn = new QPushButton("Refresh Customers");
    refreshCustomersBtn->setObjectName("actionButton");
    connect(refreshCustomersBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewAllCustomers);
    
    QPushButton *viewCustomerHistoryBtn = new QPushButton("View Customer History");
    viewCustomerHistoryBtn->setObjectName("actionButton");
    connect(viewCustomerHistoryBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewCustomerHistory);
    
    customerControlLayout->addWidget(refreshCustomersBtn);
    customerControlLayout->addWidget(viewCustomerHistoryBtn);
    customerControlLayout->addStretch();
    
    customerLayout->addLayout(customerControlLayout);
    
    // Load customers on setup (without popup message)
    loadCustomersData();
    
    m_tabWidget->addTab(m_customerWidget, "Customers");
}

void EmployeeWindow::setupReports()
{
    m_reportsWidget = new QWidget();
    QVBoxLayout *reportsLayout = new QVBoxLayout(m_reportsWidget);
    
    QLabel *reportsTitle = new QLabel("Booking Reports");
    reportsTitle->setObjectName("sectionTitle");
    reportsTitle->setAlignment(Qt::AlignCenter);
    
    m_reportTextEdit = new QTextEdit();
    m_reportTextEdit->setObjectName("reportText");
    m_reportTextEdit->setReadOnly(true);
    m_reportTextEdit->setPlainText("Select a report option to view booking information...");
    
    QHBoxLayout *reportButtonsLayout = new QHBoxLayout();
    QPushButton *hotelHistoryBtn = new QPushButton("Hotel Booking History");
    QPushButton *customerHistoryBtn = new QPushButton("Customer History");
    QPushButton *roomHistoryBtn = new QPushButton("Room History");
    
    hotelHistoryBtn->setObjectName("actionButton");
    customerHistoryBtn->setObjectName("actionButton");
    roomHistoryBtn->setObjectName("actionButton");
    
    connect(hotelHistoryBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewBookingHistory);
    connect(customerHistoryBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewCustomerHistory);
    connect(roomHistoryBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRoomHistory);
    
    reportButtonsLayout->addWidget(hotelHistoryBtn);
    reportButtonsLayout->addWidget(customerHistoryBtn);
    reportButtonsLayout->addWidget(roomHistoryBtn);
    reportButtonsLayout->addStretch();
    
    reportsLayout->addWidget(reportsTitle);
    reportsLayout->addWidget(m_reportTextEdit);
    reportsLayout->addLayout(reportButtonsLayout);
    
    m_tabWidget->addTab(m_reportsWidget, "Reports");
}

void EmployeeWindow::setupMenuBar()
{
    m_menuBar = menuBar();
    
    // File menu
    QMenu *fileMenu = m_menuBar->addMenu("&File");
    
    QAction *logoutAction = fileMenu->addAction("&Logout");
    logoutAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(logoutAction, &QAction::triggered, this, &EmployeeWindow::onLogout);
    
    // View menu
    QMenu *viewMenu = m_menuBar->addMenu("&View");
    
    QAction *refreshAction = viewMenu->addAction("&Refresh Data");
    refreshAction->setShortcut(QKeySequence::Refresh);
    connect(refreshAction, &QAction::triggered, this, &EmployeeWindow::onRefreshData);
    
    QAction *viewRoomsAction = viewMenu->addAction("View &Rooms");
    connect(viewRoomsAction, &QAction::triggered, this, &EmployeeWindow::onViewRooms);
    
    // Booking menu
    QMenu *bookingMenu = m_menuBar->addMenu("&Booking");
    
    QAction *bookRoomAction = bookingMenu->addAction("&Book Room");
    connect(bookRoomAction, &QAction::triggered, this, &EmployeeWindow::onBookRoomForCustomer);
    
    QAction *giveDiscountAction = bookingMenu->addAction("&Give Discount");
    connect(giveDiscountAction, &QAction::triggered, this, &EmployeeWindow::onGiveDiscount);
}

void EmployeeWindow::setupStatusBar()
{
    m_statusBar = statusBar();
    m_statusBar->showMessage("Ready");
    
    // Add permanent widgets to status bar
    QLabel *userLabel = new QLabel(QString("Logged in as: Employee %1").arg(m_employeeId));
    m_statusBar->addPermanentWidget(userLabel);
}

void EmployeeWindow::setupStyles()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f5f5f5;
        }
        
        #welcomeLabel {
            font-size: 24px;
            font-weight: bold;
            color: #2c3e50;
            margin: 10px 0;
        }
        
        #sectionTitle {
            font-size: 20px;
            font-weight: bold;
            color: #2c3e50;
            margin: 10px 0;
        }
        
        #mainTabWidget {
            background-color: white;
            border: 1px solid #bdc3c7;
        }
        
        #mainTabWidget::pane {
            border: 1px solid #bdc3c7;
            background-color: white;
        }
        
        #mainTabWidget QTabBar::tab {
            background-color: #ecf0f1;
            color: #2c3e50;
            border: 1px solid #bdc3c7;
            padding: 8px 16px;
            margin-right: 2px;
        }
        
        #mainTabWidget QTabBar::tab:selected {
            background-color: #3498db;
            color: white;
        }
        
        #statsGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #3498db;
            border-radius: 10px;
            margin: 5px;
            padding-top: 10px;
        }
        
        #statsGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #3498db;
            font-weight: bold;
        }
        
        #formGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #27ae60;
            border-radius: 10px;
            margin: 5px;
            padding-top: 10px;
        }
        
        #formGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #27ae60;
            font-weight: bold;
        }
        
        #statLabel {
            font-size: 16px;
            color: #27ae60;
            font-weight: bold;
            padding: 5px;
        }
        
        #countLabel {
            font-size: 16px;
            font-weight: bold;
            color: #27ae60;
            margin: 5px 0;
        }
        
        #actionButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 5px;
        }
        
        #actionButton:hover {
            background-color: #2980b9;
        }
        
        #primaryButton {
            background-color: #27ae60;
            color: white;
            border: none;
            padding: 12px 24px;
            border-radius: 5px;
            font-size: 16px;
            font-weight: bold;
            margin: 10px;
        }
        
        #primaryButton:hover {
            background-color: #229954;
        }
        
        #lineEdit, #dateEdit {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            background-color: white;
            color: black;
        }
        
        #lineEdit:focus, #dateEdit:focus {
            border-color: #3498db;
        }
        
        #dataTable {
            gridline-color: #bdc3c7;
            background-color: white;
            alternate-background-color: #f8f9fa;
            selection-background-color: #3498db;
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            color: black;
        }
        
        #dataTable::item {
            padding: 8px;
            border: none;
            color: black;
        }
        
        #reportText {
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            background-color: white;
            color: black;
        }
    )");
}

void EmployeeWindow::connectSignals()
{
    connect(m_bookRoomBtn, &QPushButton::clicked, this, &EmployeeWindow::onBookRoomForCustomer);
}

void EmployeeWindow::updateDashboard()
{
    if (!m_hotelSystem) return;
    
    try {
        // Count available rooms
        hotel& h = m_hotelSystem->getHotel();
        
        int totalRooms = 0;
        int availableRooms = 0;
        
        // Count total rooms from all floors
        std::vector<floor_> floors = h.getFloors();
        for (const auto& floor : floors) {
            totalRooms += const_cast<floor_&>(floor).getNumRooms();
        }
        
        // Count available rooms from all floors
        std::vector<floor_> availableFloors = h.findAvailableRooms();
        for (const auto& floor : availableFloors) {
            availableRooms += const_cast<floor_&>(floor).getNumRooms();
        }

        m_availableRoomsLabel->setText(QString("Available: %1/%2").arg(availableRooms).arg(totalRooms));
        
        // Count occupied rooms  
        int occupiedRooms = totalRooms - availableRooms;
        m_occupiedRoomsLabel->setText(QString("Occupied: %1/%2").arg(occupiedRooms).arg(totalRooms));
        
        // Count total customers
        std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
        m_totalCustomersLabel->setText(QString("Total: %1").arg(customers.size()));
        
        // Count today's bookings (count all customers with current bookings)
        int todayBookings = 0;
        
        for (customer* cust : customers) {
            if (cust && cust->getCurrentBookings().size() > 0) {
                todayBookings++;
            }
        }
        
        m_todayBookingsLabel->setText(QString("Active Bookings: %1").arg(todayBookings));
        
    } catch (const std::exception &e) {
        m_statusBar->showMessage(QString("Error updating dashboard: %1").arg(e.what()), 5000);
        // Fallback to N/A on error
        m_availableRoomsLabel->setText("Available: N/A");
        m_occupiedRoomsLabel->setText("Occupied: N/A");
        m_totalCustomersLabel->setText("Total: N/A");
        m_todayBookingsLabel->setText("Bookings: N/A");
    }
}

void EmployeeWindow::onLogout()
{
    int reply = QMessageBox::question(this, "Logout", 
                                      "Are you sure you want to logout?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_hotelSystem->saveSystemState();
        close();
    }
}

void EmployeeWindow::onRefreshData()
{
    updateDashboard();
    onViewRooms();
    m_statusBar->showMessage("Data refreshed", 3000);
}

void EmployeeWindow::onViewRooms()
{
    try {
        // Clear existing data
        m_roomTable->setRowCount(0);
        
        // Get hotel and populate room table
        hotel& h = m_hotelSystem->getHotel();
        std::vector<floor_> floors = h.getFloors();
        
        int totalRooms = 0;
        int rowIndex = 0;
        
        // Iterate through all floors and rooms
        for (size_t floorIndex = 0; floorIndex < floors.size(); ++floorIndex) {
            floor_ currentFloor = floors[floorIndex];  // Make a copy to call non-const methods
            std::vector<room> roomsOnFloor = currentFloor.findAllRooms();
            
            for (auto& r : roomsOnFloor) {  // Remove const to allow non-const method calls
                m_roomTable->insertRow(rowIndex);
                
                // Get type name for bed info and amenities
                std::string typeName = r.getTypeName();
                
                // Create bed info and capacity based on room type
                QString bedInfo;
                QString capacity;
                QString amenities;
                
                if (typeName.find("Single") != std::string::npos) {
                    bedInfo = "1 Single";
                    capacity = "1-2";
                    amenities = "TV, Bath";
                    if (typeName.find("VIP") != std::string::npos) {
                        amenities = "TV, Bath, Balcony, Fridge";
                    }
                } else if (typeName.find("Double") != std::string::npos) {
                    bedInfo = "1 Double";
                    capacity = "2-3";
                    amenities = "TV, Bath, Balcony";
                    if (typeName.find("luxury") != std::string::npos) {
                        amenities = "TV, Bath, Balcony, Fridge, Chair";
                    }
                } else if (typeName.find("Family") != std::string::npos) {
                    bedInfo = "2 Double";
                    capacity = "4-6";
                    amenities = "TV, Bath, Balcony, Fridge, Chair";
                } else {
                    bedInfo = "1 Single";
                    capacity = "1-2";
                    amenities = "TV, Bath";
                }
                
                // Set room data in table
                m_roomTable->setItem(rowIndex, 0, new QTableWidgetItem(QString::fromStdString(r.getID())));
                m_roomTable->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(floorIndex + 1)));
                m_roomTable->setItem(rowIndex, 2, new QTableWidgetItem(QString::fromStdString(r.getTypeName())));
                m_roomTable->setItem(rowIndex, 3, new QTableWidgetItem(bedInfo));
                m_roomTable->setItem(rowIndex, 4, new QTableWidgetItem(capacity));
                m_roomTable->setItem(rowIndex, 5, new QTableWidgetItem(amenities));
                m_roomTable->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(r.checkPrice(), 'f', 0) + " VND"));
                m_roomTable->setItem(rowIndex, 7, new QTableWidgetItem(r.isAvailable() ? "Available" : "Occupied"));
                
                // Find current guest name
                QString guestName = "N/A";
                if (!r.isAvailable()) {
                    // Find customer who booked this room
                    std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
                    for (customer* cust : customers) {
                        if (cust) {
                            std::vector<current_booking> bookings = cust->getCurrentBookings();
                            for (const current_booking& booking : bookings) {
                                if (booking.roomID == r.getID()) {
                                    guestName = QString::fromStdString(cust->getName());
                                    break;
                                }
                            }
                            if (guestName != "N/A") break;
                        }
                    }
                    if (guestName == "N/A") guestName = "Unknown Guest";
                }
                
                m_roomTable->setItem(rowIndex, 8, new QTableWidgetItem(guestName));
                m_roomTable->setItem(rowIndex, 9, new QTableWidgetItem(r.isAvailable() ? "Yes" : "No"));
                
                totalRooms++;
                rowIndex++;
            }
        }
        
        // If no rooms found, show message
        if (totalRooms == 0) {
            m_roomTable->insertRow(0);
            m_roomTable->setItem(0, 0, new QTableWidgetItem("No rooms found"));
            m_roomTable->setItem(0, 1, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 2, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 3, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 4, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 5, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 6, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 7, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 8, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 9, new QTableWidgetItem(""));
        }
        
        m_roomCountLabel->setText(QString("Total Rooms: %1").arg(totalRooms));
        m_statusBar->showMessage(QString("Loaded %1 rooms").arg(totalRooms), 3000);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load rooms: %1").arg(e.what()));
    }
}

void EmployeeWindow::onBookRoomForCustomer()
{
    int customerId = m_customerIdEdit->text().toInt();
    QString roomId = m_roomIdEdit->text().trimmed();
    QDate checkinDate = m_checkinDateEdit->date();
    QDate checkoutDate = m_checkoutDateEdit->date();
    
    if (customerId <= 0 || roomId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter valid customer ID and room ID.");
        return;
    }
    
    if (checkinDate >= checkoutDate) {
        QMessageBox::warning(this, "Date Error", "Check-out date must be after check-in date.");
        return;
    }
    
    try {
        // Find customer
        customer *cust = m_hotelSystem->findCustomer(customerId);
        if (!cust) {
            QMessageBox::warning(this, "Error", "Customer not found!");
            return;
        }
        
        // Find room
        room *roomPtr = m_hotelSystem->getHotel().findRoomByNumber(roomId.toStdString());
        if (!roomPtr) {
            QMessageBox::warning(this, "Error", "Room not found!");
            return;
        }
        
        // Check if room is available
        if (!roomPtr->isAvailable()) {
            QMessageBox::warning(this, "Error", "Room is not available!");
            return;
        }
        
        // Create booking record (simplified - using room price and dates)
        date checkin(checkinDate.day(), checkinDate.month(), checkinDate.year());
        date checkout(checkoutDate.day(), checkoutDate.month(), checkoutDate.year());
        
        // Book the room for customer
        hotel& h = m_hotelSystem->getHotel();
        bool success = cust->bookRoom(h, roomId.toStdString(), checkin, checkout);
        
        if (success) {
            QMessageBox::information(this, "Success", 
                                    QString("Room %1 booked successfully for customer %2!\nCheck-in: %3\nCheck-out: %4")
                                    .arg(roomId)
                                    .arg(cust->getName().c_str())
                                    .arg(checkinDate.toString())
                                    .arg(checkoutDate.toString()));
        } else {
            QMessageBox::warning(this, "Booking Failed", "Failed to book the room. It may be unavailable or there was an error.");
        }
        
        // Clear form
        m_customerIdEdit->clear();
        m_roomIdEdit->clear();
        m_checkinDateEdit->setDate(QDate::currentDate());
        m_checkoutDateEdit->setDate(QDate::currentDate().addDays(1));
        
        updateDashboard();
        onViewRooms(); // Refresh room table
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to book room: %1").arg(e.what()));
    }
}

void EmployeeWindow::onGiveDiscount()
{
    bool ok;
    int customerId = QInputDialog::getInt(this, "Give Discount", 
                                         "Enter customer ID:", 0, 0, 999999, 1, &ok);
    
    if (!ok) return;
    
    int discount = QInputDialog::getInt(this, "Give Discount", 
                                       "Enter discount percentage:", 0, 0, 50, 1, &ok);
    
    if (ok) {
        try {
            m_hotelSystem->giveDiscountToCustomer(customerId, discount);
            QMessageBox::information(this, "Success", 
                QString("Discount of %1% given to customer %2 successfully!").arg(discount).arg(customerId));
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to give discount: %1").arg(e.what()));
        }
    }
}

void EmployeeWindow::onViewBookingHistory()
{
    try {
        // Switch to reports tab
        m_tabWidget->setCurrentWidget(m_reportsWidget);
        
        std::ostringstream historyStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(historyStream.rdbuf());
        
        m_hotelSystem->viewAllBookingHistory();
        
        std::cout.rdbuf(orig);
        
        QString history = QString::fromStdString(historyStream.str());
        if (history.isEmpty()) {
            history = "No booking history available.";
        }
        
        m_reportTextEdit->setPlainText(history);
        m_statusBar->showMessage("Booking history loaded", 3000);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load booking history: %1").arg(e.what()));
    }
}

void EmployeeWindow::onViewCustomerHistory()
{
    // Check if a customer is selected in the table
    if (!m_customerTable) return;
    
    int currentRow = m_customerTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* customerIdItem = m_customerTable->item(currentRow, 0);
        if (customerIdItem) {
            int customerId = customerIdItem->text().toInt();
            
            try {
                // Switch to reports tab
                m_tabWidget->setCurrentWidget(m_reportsWidget);
                
                std::ostringstream historyStream;
                std::streambuf* orig = std::cout.rdbuf();
                std::cout.rdbuf(historyStream.rdbuf());
                
                m_hotelSystem->viewCustomerBookingHistory(customerId);
                
                std::cout.rdbuf(orig);
                
                QString history = QString::fromStdString(historyStream.str());
                if (history.isEmpty()) {
                    history = QString("No booking history found for customer %1.").arg(customerId);
                }
                
                m_reportTextEdit->setPlainText(history);
                m_statusBar->showMessage("Customer history loaded", 3000);
            } catch (const std::exception &e) {
                QMessageBox::critical(this, "Error", QString("Failed to load customer history: %1").arg(e.what()));
            }
        }
    } else {
        QMessageBox::information(this, "No Selection", "Please select a customer from the table to view their history.");
    }
}

void EmployeeWindow::onViewRoomHistory()
{
    bool ok;
    QString roomId = QInputDialog::getText(this, "Room History", 
                                          "Enter room ID:", QLineEdit::Normal, "", &ok);
    
    if (ok && !roomId.isEmpty()) {
        try {
            // Switch to reports tab
            m_tabWidget->setCurrentWidget(m_reportsWidget);
            
            room *foundRoom = m_hotelSystem->getHotel().findRoomByNumber(roomId.toStdString());
            if (foundRoom) {
                std::ostringstream historyStream;
                std::streambuf* orig = std::cout.rdbuf();
                std::cout.rdbuf(historyStream.rdbuf());
                
                foundRoom->displayBookingHistory();
                
                std::cout.rdbuf(orig);
                
                QString history = QString::fromStdString(historyStream.str());
                if (history.isEmpty()) {
                    history = QString("No booking history found for room %1.").arg(roomId);
                }
                
                m_reportTextEdit->setPlainText(history);
                m_statusBar->showMessage("Room history loaded", 3000);
            } else {
                QMessageBox::warning(this, "Error", "Room not found!");
            }
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to load room history: %1").arg(e.what()));
        }
    }
}

void EmployeeWindow::onLockRoom()
{
    int currentRow = m_roomTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a room to lock.");
        return;
    }
    
    QString roomId = m_roomTable->item(currentRow, 0)->text();
    
    int reply = QMessageBox::question(this, "Confirm Lock", 
                                      QString("Are you sure you want to lock room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            // Get employee object from manager
            manager& mgr = m_hotelSystem->getManager();
            std::vector<IPerson*> employees = mgr.getEmployeeList();
            
            employee* emp = nullptr;
            for (IPerson* person : employees) {
                if (person->getID() == m_employeeId) {
                    emp = dynamic_cast<employee*>(person);
                    break;
                }
            }
            
            if (emp) {
                hotel& h = m_hotelSystem->getHotel();
                emp->lockRoom(h, roomId.toStdString());
                
                QMessageBox::information(this, "Success", QString("Room %1 has been locked.").arg(roomId));
                onViewRooms(); // Refresh the table
                updateDashboard(); // Update dashboard
            } else {
                QMessageBox::warning(this, "Error", "Employee not found in system.");
            }
            
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to lock room: %1").arg(e.what()));
        }
    }
}

void EmployeeWindow::onUnlockRoom()
{
    int currentRow = m_roomTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a room to unlock.");
        return;
    }
    
    QString roomId = m_roomTable->item(currentRow, 0)->text();
    
    int reply = QMessageBox::question(this, "Confirm Unlock", 
                                      QString("Are you sure you want to unlock room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            // Get employee object from manager
            manager& mgr = m_hotelSystem->getManager();
            std::vector<IPerson*> employees = mgr.getEmployeeList();
            
            employee* emp = nullptr;
            for (IPerson* person : employees) {
                if (person->getID() == m_employeeId) {
                    emp = dynamic_cast<employee*>(person);
                    break;
                    }
            }
            
            if (emp) {
                hotel& h = m_hotelSystem->getHotel();
                emp->unlockRoom(h, roomId.toStdString());
                
                QMessageBox::information(this, "Success", QString("Room %1 has been unlocked.").arg(roomId));
                onViewRooms(); // Refresh the table
                updateDashboard(); // Update dashboard
            } else {
                QMessageBox::warning(this, "Error", "Employee not found in system.");
            }
            
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to unlock room: %1").arg(e.what()));
        }
    }
}

// Customer management functions implementation
void EmployeeWindow::onViewAllCustomers() {
    try {
        // Get all customers from the hotel system
        auto customers = m_hotelSystem->getAllCustomers();
        
        // Clear existing data
        m_customerTable->setRowCount(0);
        
        int row = 0;
        for (auto* cust : customers) {
            if (cust) {
                m_customerTable->insertRow(row);
                
                // Calculate total bookings (current + history)
                int currentBookings = cust->getCurrentBookings().size();
                int pastBookings = cust->getBookingHistory().size();
                int totalBookings = currentBookings + pastBookings;
                
                m_customerTable->setItem(row, 0, new QTableWidgetItem(QString::number(cust->getID())));
                m_customerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cust->getName())));
                m_customerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(cust->getEmail())));
                m_customerTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(cust->getPhone())));
                m_customerTable->setItem(row, 4, new QTableWidgetItem(cust->getGender() ? "Male" : "Female"));
                m_customerTable->setItem(row, 5, new QTableWidgetItem(QString::number(totalBookings)));
                
                row++;
            }
        }
        
        // Show success message when manually refreshed
        QMessageBox::information(this, "Success", QString("Customer data refreshed. Total customers: %1").arg(row));
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load customers: %1").arg(e.what()));
    }
}

// Available rooms functions implementation
void EmployeeWindow::refreshAvailableRooms() {
    try {
        if (!m_availableRoomsTable) return;
        
        // Clear existing data
        m_availableRoomsTable->setRowCount(0);
        
        hotel& h = m_hotelSystem->getHotel();
        
        // Get all floors and their rooms
        auto floors = h.getFloors();
        
        int row = 0;
        for (auto& floor : floors) {  // Remove const to allow non-const method calls
            auto availableRooms = floor.findAvailableRooms();
            for (auto& r : availableRooms) {  // Remove const to allow non-const method calls
                m_availableRoomsTable->insertRow(row);
                
                // Extract floor number from room ID (first 2 digits)
                std::string roomId = r.getID();
                int floorNumber = std::stoi(roomId.substr(0, 2)) + 1; // Convert to 1-based indexing
                
                // Get type name
                std::string typeName = r.getTypeName();
                
                // Create bed info and capacity based on room type
                QString bedInfo;
                QString capacity;
                QString amenities;
                
                if (typeName.find("Single") != std::string::npos) {
                    bedInfo = "1 Single";
                    capacity = "1-2";
                    amenities = "TV, Bath";
                    if (typeName.find("VIP") != std::string::npos) {
                        amenities = "TV, Bath, Balcony, Fridge";
                    }
                } else if (typeName.find("Double") != std::string::npos) {
                    bedInfo = "1 Double";
                    capacity = "2-3";
                    amenities = "TV, Bath, Balcony";
                    if (typeName.find("luxury") != std::string::npos) {
                        amenities = "TV, Bath, Balcony, Fridge, Chair";
                    }
                } else if (typeName.find("Family") != std::string::npos) {
                    bedInfo = "2 Double";
                    capacity = "4-6";
                    amenities = "TV, Bath, Balcony, Fridge, Chair";
                } else {
                    bedInfo = "1 Single";
                    capacity = "1-2";
                    amenities = "TV, Bath";
                }
                
                m_availableRoomsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(r.getID())));
                m_availableRoomsTable->setItem(row, 1, new QTableWidgetItem(QString::number(floorNumber)));
                m_availableRoomsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r.getTypeName())));
                m_availableRoomsTable->setItem(row, 3, new QTableWidgetItem(bedInfo));
                m_availableRoomsTable->setItem(row, 4, new QTableWidgetItem(capacity));
                m_availableRoomsTable->setItem(row, 5, new QTableWidgetItem(amenities));
                m_availableRoomsTable->setItem(row, 6, new QTableWidgetItem(QString::number(r.checkPrice(), 'f', 2)));
                m_availableRoomsTable->setItem(row, 7, new QTableWidgetItem("Available"));
                
                row++;
            }
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to refresh available rooms: %1").arg(e.what()));
    }
}

void EmployeeWindow::onCustomerSelected() {
    if (!m_customerTable) return;
    
    int currentRow = m_customerTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* customerIdItem = m_customerTable->item(currentRow, 0);
        if (customerIdItem) {
            QString customerId = customerIdItem->text();
            // Automatically fill the customer ID in the booking form
            if (m_customerIdEdit) {
                m_customerIdEdit->setText(customerId);
            }
        }
    }
}

void EmployeeWindow::onAvailableRoomSelected() {
    if (!m_availableRoomsTable) return;
    
    int currentRow = m_availableRoomsTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* roomItem = m_availableRoomsTable->item(currentRow, 0);
        if (roomItem) {
            QString roomId = roomItem->text();
            // Automatically fill the room ID in the booking form
            if (m_roomIdEdit) {
                m_roomIdEdit->setText(roomId);
            }
        }
    }
}

void EmployeeWindow::onViewRoomDetails() {
    if (!m_availableRoomsTable) return;
    
    int currentRow = m_availableRoomsTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* roomItem = m_availableRoomsTable->item(currentRow, 0);
        if (roomItem) {
            QString roomId = roomItem->text();
            
            try {
                hotel& h = m_hotelSystem->getHotel();
                room* r = h.findRoomByNumber(roomId.toStdString());
                
                if (r) {
                    QString details = QString("Room Details:\n\n");
                    details += QString("Room ID: %1\n").arg(QString::fromStdString(r->getID()));
                    details += QString("Room Type: %1\n").arg(QString::fromStdString(r->getTypeName()));
                    details += QString("Price: $%1\n").arg(r->checkPrice(), 0, 'f', 2);
                    details += QString("Status: %1\n\n").arg(r->isAvailable() ? "Available" : "Occupied");
                    
                    // Capture furniture information
                    std::ostringstream furnitureStream;
                    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
                    std::cout.rdbuf(furnitureStream.rdbuf());
                    r->displayFurniture();
                    std::cout.rdbuf(oldCoutStreamBuf);
                    
                    QString furnitureInfo = QString::fromStdString(furnitureStream.str()).trimmed();
                    if (!furnitureInfo.isEmpty()) {
                        details += QString("Furniture:\n%1\n\n").arg(furnitureInfo);
                    }
                    
                    // Capture items information
                    std::ostringstream itemsStream;
                    std::cout.rdbuf(itemsStream.rdbuf());
                    r->displayItem();
                    std::cout.rdbuf(oldCoutStreamBuf);
                    
                    QString itemsInfo = QString::fromStdString(itemsStream.str()).trimmed();
                    if (!itemsInfo.isEmpty()) {
                        details += QString("Items:\n%1").arg(itemsInfo);
                    }
                    
                    QMessageBox::information(this, "Room Details", details);
                } else {
                    QMessageBox::warning(this, "Error", "Room not found.");
                }
                
            } catch (const std::exception &e) {
                QMessageBox::critical(this, "Error", QString("Failed to get room details: %1").arg(e.what()));
            }
        }
    } else {
        QMessageBox::information(this, "No Selection", "Please select a room to view details.");
    }
}

// New function to load customer data without popup
void EmployeeWindow::loadCustomersData() {
    try {
        // Get all customers from the hotel system
        auto customers = m_hotelSystem->getAllCustomers();
        
        // Clear existing data
        m_customerTable->setRowCount(0);
        
        int row = 0;
        for (auto* cust : customers) {
            if (cust) {
                m_customerTable->insertRow(row);
                
                // Calculate total bookings (current + history)
                int currentBookings = cust->getCurrentBookings().size();
                int pastBookings = cust->getBookingHistory().size();
                int totalBookings = currentBookings + pastBookings;
                
                m_customerTable->setItem(row, 0, new QTableWidgetItem(QString::number(cust->getID())));
                m_customerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cust->getName())));
                m_customerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(cust->getEmail())));
                m_customerTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(cust->getPhone())));
                m_customerTable->setItem(row, 4, new QTableWidgetItem(cust->getGender() ? "Male" : "Female"));
                m_customerTable->setItem(row, 5, new QTableWidgetItem(QString::number(totalBookings)));
                
                row++;
            }
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load customers: %1").arg(e.what()));
    }
}
