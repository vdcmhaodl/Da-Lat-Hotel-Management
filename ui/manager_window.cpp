#include "manager_window.h"
#include "room_management_widget.h"
#include "customer_management_widget.h"
#include "employee_management_widget.h"
#include "add_customer_dialog.h"
#include "add_employee_dialog.h"

ManagerWindow::ManagerWindow(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QMainWindow(parent)
    , m_hotelSystem(hotelSystem)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupStyles();
    connectSignals();
    updateDashboard();
    
    setWindowTitle("Hotel Management System - Manager Dashboard");
    setMinimumSize(1200, 800);
    resize(1400, 900);
}

ManagerWindow::~ManagerWindow()
{
    // Save system state when closing
    if (m_hotelSystem) {
        m_hotelSystem->saveSystemState();
    }
}

void ManagerWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Welcome header
    QLabel *welcomeLabel = new QLabel("Welcome to Manager Dashboard");
    welcomeLabel->setObjectName("welcomeLabel");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(welcomeLabel);
    
    // Tab widget
    m_tabWidget = new QTabWidget();
    m_tabWidget->setObjectName("mainTabWidget");
    
    // Dashboard tab
    setupDashboard();
    
    // Room management tab
    m_roomManagement = new RoomManagementWidget(m_hotelSystem);
    m_tabWidget->addTab(m_roomManagement, "Room Management");
    
    // Customer management tab
    m_customerManagement = new CustomerManagementWidget(m_hotelSystem);
    m_tabWidget->addTab(m_customerManagement, "Customer Management");
    
    // Employee management tab
    m_employeeManagement = new EmployeeManagementWidget(m_hotelSystem);
    m_tabWidget->addTab(m_employeeManagement, "Employee Management");
    
    // Reports tab
    setupReports();
    
    mainLayout->addWidget(m_tabWidget);
}

void ManagerWindow::setupDashboard()
{
    m_dashboardWidget = new QWidget();
    QVBoxLayout *dashboardLayout = new QVBoxLayout(m_dashboardWidget);
    dashboardLayout->setSpacing(20);
    dashboardLayout->setContentsMargins(20, 20, 20, 20);
    
    // Statistics cards
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    // Room statistics
    QGroupBox *roomStatsGroup = new QGroupBox("Room Statistics");
    roomStatsGroup->setObjectName("statsGroup");
    QVBoxLayout *roomStatsLayout = new QVBoxLayout(roomStatsGroup);
    
    m_totalRoomsLabel = new QLabel("Total Rooms: 0");
    m_availableRoomsLabel = new QLabel("Available: 0");
    m_occupiedRoomsLabel = new QLabel("Occupied: 0");
    
    m_totalRoomsLabel->setObjectName("statLabel");
    m_availableRoomsLabel->setObjectName("statLabel");
    m_occupiedRoomsLabel->setObjectName("statLabel");
    
    roomStatsLayout->addWidget(m_totalRoomsLabel);
    roomStatsLayout->addWidget(m_availableRoomsLabel);
    roomStatsLayout->addWidget(m_occupiedRoomsLabel);
    
    // Customer statistics
    QGroupBox *customerStatsGroup = new QGroupBox("Customer Statistics");
    customerStatsGroup->setObjectName("statsGroup");
    QVBoxLayout *customerStatsLayout = new QVBoxLayout(customerStatsGroup);
    
    m_totalCustomersLabel = new QLabel("Total Customers: 0");
    m_totalCustomersLabel->setObjectName("statLabel");
    customerStatsLayout->addWidget(m_totalCustomersLabel);
    
    // Employee statistics
    QGroupBox *employeeStatsGroup = new QGroupBox("Employee Statistics");
    employeeStatsGroup->setObjectName("statsGroup");
    QVBoxLayout *employeeStatsLayout = new QVBoxLayout(employeeStatsGroup);
    
    m_totalEmployeesLabel = new QLabel("Total Employees: 0");
    m_totalEmployeesLabel->setObjectName("statLabel");
    employeeStatsLayout->addWidget(m_totalEmployeesLabel);
    
    // Revenue statistics
    QGroupBox *revenueStatsGroup = new QGroupBox("Revenue Statistics");
    revenueStatsGroup->setObjectName("statsGroup");
    QVBoxLayout *revenueStatsLayout = new QVBoxLayout(revenueStatsGroup);
    
    m_totalRevenueLabel = new QLabel("Total Revenue: $0");
    m_totalRevenueLabel->setObjectName("statLabel");
    revenueStatsLayout->addWidget(m_totalRevenueLabel);
    
    statsLayout->addWidget(roomStatsGroup);
    statsLayout->addWidget(customerStatsGroup);
    statsLayout->addWidget(employeeStatsGroup);
    statsLayout->addWidget(revenueStatsGroup);
    
    dashboardLayout->addLayout(statsLayout);
    
    // Quick actions
    QGroupBox *quickActionsGroup = new QGroupBox("Quick Actions");
    quickActionsGroup->setObjectName("statsGroup");
    QHBoxLayout *quickActionsLayout = new QHBoxLayout(quickActionsGroup);
    
    QPushButton *refreshBtn = new QPushButton("Refresh Data");
    QPushButton *generateReportBtn = new QPushButton("Generate Report");
    QPushButton *viewStatsBtn = new QPushButton("View Statistics");
    QPushButton *viewRevenueBtn = new QPushButton("View Revenue");
    
    refreshBtn->setObjectName("actionButton");
    generateReportBtn->setObjectName("actionButton");
    viewStatsBtn->setObjectName("actionButton");
    viewRevenueBtn->setObjectName("actionButton");
    
    connect(refreshBtn, &QPushButton::clicked, this, &ManagerWindow::refreshAllData);
    connect(generateReportBtn, &QPushButton::clicked, this, &ManagerWindow::onGenerateReport);
    connect(viewStatsBtn, &QPushButton::clicked, this, &ManagerWindow::onViewStatistics);
    connect(viewRevenueBtn, &QPushButton::clicked, this, &ManagerWindow::onViewRevenue);
    
    quickActionsLayout->addWidget(refreshBtn);
    quickActionsLayout->addWidget(generateReportBtn);
    quickActionsLayout->addWidget(viewStatsBtn);
    quickActionsLayout->addWidget(viewRevenueBtn);
    
    dashboardLayout->addWidget(quickActionsGroup);
    dashboardLayout->addStretch();
    
    m_tabWidget->addTab(m_dashboardWidget, "Dashboard");
}

void ManagerWindow::setupReports()
{
    m_reportsWidget = new QWidget();
    QVBoxLayout *reportsLayout = new QVBoxLayout(m_reportsWidget);
    
    QLabel *reportsTitle = new QLabel("System Reports");
    reportsTitle->setObjectName("sectionTitle");
    reportsTitle->setAlignment(Qt::AlignCenter);
    
    m_reportTextEdit = new QTextEdit();
    m_reportTextEdit->setObjectName("reportText");
    m_reportTextEdit->setReadOnly(true);
    m_reportTextEdit->setPlainText("Click 'Generate Report' to view detailed system reports...");
    
    QHBoxLayout *reportButtonsLayout = new QHBoxLayout();
    QPushButton *generateBtn = new QPushButton("Generate Booking Report");
    QPushButton *clearBtn = new QPushButton("Clear Report");
    
    generateBtn->setObjectName("actionButton");
    clearBtn->setObjectName("secondaryButton");
    
    connect(generateBtn, &QPushButton::clicked, this, &ManagerWindow::onGenerateReport);
    connect(clearBtn, &QPushButton::clicked, [this]() {
        m_reportTextEdit->clear();
    });
    
    reportButtonsLayout->addWidget(generateBtn);
    reportButtonsLayout->addWidget(clearBtn);
    reportButtonsLayout->addStretch();
    
    reportsLayout->addWidget(reportsTitle);
    reportsLayout->addWidget(m_reportTextEdit);
    reportsLayout->addLayout(reportButtonsLayout);
    
    m_tabWidget->addTab(m_reportsWidget, "Reports");
}

void ManagerWindow::setupMenuBar()
{
    m_menuBar = menuBar();
    
    // File menu
    QMenu *fileMenu = m_menuBar->addMenu("&File");
    
    QAction *saveAction = fileMenu->addAction("&Save System State");
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &ManagerWindow::onSaveSystem);
    
    QAction *loadAction = fileMenu->addAction("&Load System State");
    loadAction->setShortcut(QKeySequence::Open);
    connect(loadAction, &QAction::triggered, this, &ManagerWindow::onLoadSystem);
    
    fileMenu->addSeparator();
    
    QAction *logoutAction = fileMenu->addAction("&Logout");
    logoutAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(logoutAction, &QAction::triggered, this, &ManagerWindow::onLogout);
    
    // View menu
    QMenu *viewMenu = m_menuBar->addMenu("&View");
    
    QAction *refreshAction = viewMenu->addAction("&Refresh All Data");
    refreshAction->setShortcut(QKeySequence::Refresh);
    connect(refreshAction, &QAction::triggered, this, &ManagerWindow::refreshAllData);
    
    // Reports menu
    QMenu *reportsMenu = m_menuBar->addMenu("&Reports");
    
    QAction *bookingReportAction = reportsMenu->addAction("&Booking Report");
    connect(bookingReportAction, &QAction::triggered, this, &ManagerWindow::onGenerateReport);
    
    QAction *statisticsAction = reportsMenu->addAction("&Statistics");
    connect(statisticsAction, &QAction::triggered, this, &ManagerWindow::onViewStatistics);
    
    QAction *revenueAction = reportsMenu->addAction("&Revenue Report");
    connect(revenueAction, &QAction::triggered, this, &ManagerWindow::onViewRevenue);
}

void ManagerWindow::setupStatusBar()
{
    m_statusBar = statusBar();
    m_statusBar->showMessage("Ready");
    
    // Add permanent widgets to status bar
    QLabel *userLabel = new QLabel(QString("Logged in as: Manager (%1)")
                                   .arg(QString::fromStdString(m_hotelSystem->getManager().getName())));
    m_statusBar->addPermanentWidget(userLabel);
}

void ManagerWindow::setupStyles()
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
        
        #mainTabWidget {
            background-color: white;
            border: 1px solid #bdc3c7;
        }
        
        #mainTabWidget::pane {
            border: 1px solid #bdc3c7;
            background-color: white;
        }
        
        #mainTabWidget::tab-bar {
            alignment: center;
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
        
        #mainTabWidget QTabBar::tab:hover {
            background-color: #d5dbdb;
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
        
        #statLabel {
            font-size: 16px;
            color: #27ae60;
            font-weight: bold;
            padding: 5px;
        }
        
        #sectionTitle {
            font-size: 20px;
            font-weight: bold;
            color: #2c3e50;
            margin: 10px 0;
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
        
        #actionButton:pressed {
            background-color: #21618c;
        }
        
        #secondaryButton {
            background-color: #95a5a6;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 5px;
        }
        
        #secondaryButton:hover {
            background-color: #7f8c8d;
        }
        
        #reportText {
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            background-color: white;
            color: black;
        }
        
        /* Table Styles */
        QTableWidget {
            background-color: white;
            color: black;
            gridline-color: #bdc3c7;
            border: 1px solid #bdc3c7;
            selection-background-color: #3498db;
            selection-color: white;
        }
        
        QTableWidget::item {
            background-color: white;
            color: black;
            padding: 5px;
        }
        
        QTableWidget::item:selected {
            background-color: #3498db;
            color: white;
        }
        
        QHeaderView::section {
            background-color: #ecf0f1;
            color: #2c3e50;
            border: 1px solid #bdc3c7;
            padding: 8px;
            font-weight: bold;
        }
        
        /* Input Fields */
        QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox {
            background-color: white;
            color: black;
            border: 2px solid #bdc3c7;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
        }
        
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus {
            border-color: #3498db;
        }
        
        QComboBox::drop-down {
            border: none;
            background-color: #ecf0f1;
        }
        
        QComboBox::down-arrow {
            width: 12px;
            height: 12px;
        }
        
        QComboBox QAbstractItemView {
            background-color: white;
            color: black;
            selection-background-color: #3498db;
            selection-color: white;
        }
    )");
}

void ManagerWindow::connectSignals()
{
    // Connect tab change signal to refresh data
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &ManagerWindow::updateDashboard);
}

void ManagerWindow::updateDashboard()
{
    if (!m_hotelSystem) return;
    
    try {
        // Update room statistics
        hotel &h = m_hotelSystem->getHotel();
        int totalRooms = 0;
        int availableRooms = 0;
        int occupiedRooms = 0;
        
        // Count total rooms from all floors
        std::vector<floor_> floors = h.getFloors();
        for (const auto& floor : floors) {
            totalRooms += const_cast<floor_&>(floor).getNumRooms();
        }
        
        // Count available rooms from all floors
        std::vector<floor_> availableFloors = h.findAvailableRooms();
        for (const auto& floor : availableFloors) {
            std::vector<room> roomsOnFloor = const_cast<floor_&>(floor).findAvailableRooms();
            availableRooms += roomsOnFloor.size();
        }
        
        occupiedRooms = totalRooms - availableRooms;
        
        m_totalRoomsLabel->setText(QString("Total Rooms: %1").arg(totalRooms));
        m_availableRoomsLabel->setText(QString("Available: %1").arg(availableRooms));
        m_occupiedRoomsLabel->setText(QString("Occupied: %1").arg(occupiedRooms));
        
        // Update customer statistics
        std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
        m_totalCustomersLabel->setText(QString("Total Customers: %1").arg(customers.size()));
        
        // Update employee statistics
        manager& mgr = m_hotelSystem->getManager();
        std::vector<IPerson*> employees = mgr.getEmployeeList();
        m_totalEmployeesLabel->setText(QString("Total Employees: %1").arg(employees.size()));
        
        // Update revenue statistics (calculate from customer bookings)
        double totalRevenue = 0.0;
        for (customer* cust : customers) {
            if (cust) {
                // Get customer's booking history and sum up costs
                std::vector<current_booking> bookings = cust->getCurrentBookings();
                for (const current_booking& booking : bookings) {
                    totalRevenue += booking.bill;
                }
            }
        }
        m_totalRevenueLabel->setText(QString("Total Revenue: $%1").arg(QString::number(totalRevenue, 'f', 2)));
        
    } catch (const std::exception &e) {
        m_statusBar->showMessage(QString("Error updating dashboard: %1").arg(e.what()), 5000);
    }
}

void ManagerWindow::onLogout()
{
    int reply = QMessageBox::question(this, "Logout", 
                                      "Are you sure you want to logout?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_hotelSystem->saveSystemState();
        close();
    }
}

void ManagerWindow::onSaveSystem()
{
    try {
        m_hotelSystem->saveSystemState();
        m_statusBar->showMessage("System state saved successfully", 3000);
        QMessageBox::information(this, "Success", "System state saved successfully!");
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to save system state: %1").arg(e.what()));
    }
}

void ManagerWindow::onLoadSystem()
{
    int reply = QMessageBox::question(this, "Load System State", 
                                      "Loading will overwrite current data. Continue?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            m_hotelSystem->loadSystemState();
            refreshAllData();
            m_statusBar->showMessage("System state loaded successfully", 3000);
            QMessageBox::information(this, "Success", "System state loaded successfully!");
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to load system state: %1").arg(e.what()));
        }
    }
}

void ManagerWindow::onGenerateReport()
{
    try {
        // Switch to reports tab
        m_tabWidget->setCurrentWidget(m_reportsWidget);
        
        // Generate booking report
        std::ostringstream reportStream;
        
        // Redirect cout to our string stream temporarily
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(reportStream.rdbuf());
        
        // Generate the report
        m_hotelSystem->getManager().generateBookingReport(m_hotelSystem->getAllCustomers());
        
        // Restore cout
        std::cout.rdbuf(orig);
        
        // Display the report
        m_reportTextEdit->setPlainText(QString::fromStdString(reportStream.str()));
        
        m_statusBar->showMessage("Booking report generated", 3000);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to generate report: %1").arg(e.what()));
    }
}

void ManagerWindow::onViewStatistics()
{
    try {
        // Switch to reports tab
        m_tabWidget->setCurrentWidget(m_reportsWidget);
        
        std::ostringstream statsStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(statsStream.rdbuf());
        
        m_hotelSystem->getManager().viewBookingStatistics(m_hotelSystem->getAllCustomers());
        
        std::cout.rdbuf(orig);
        
        m_reportTextEdit->setPlainText(QString::fromStdString(statsStream.str()));
        m_statusBar->showMessage("Statistics generated", 3000);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to generate statistics: %1").arg(e.what()));
    }
}

void ManagerWindow::onViewRevenue()
{
    try {
        // Switch to reports tab
        m_tabWidget->setCurrentWidget(m_reportsWidget);
        
        std::ostringstream revenueStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(revenueStream.rdbuf());
        
        m_hotelSystem->getManager().viewRevenueReport(m_hotelSystem->getAllCustomers());
        
        std::cout.rdbuf(orig);
        
        m_reportTextEdit->setPlainText(QString::fromStdString(revenueStream.str()));
        m_statusBar->showMessage("Revenue report generated", 3000);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to generate revenue report: %1").arg(e.what()));
    }
}

void ManagerWindow::refreshAllData()
{
    updateDashboard();
    
    // Refresh management widgets
    if (m_roomManagement) {
        m_roomManagement->refreshData();
    }
    if (m_customerManagement) {
        m_customerManagement->refreshData();
    }
    if (m_employeeManagement) {
        m_employeeManagement->refreshData();
    }
    
    m_statusBar->showMessage("All data refreshed", 3000);
}

