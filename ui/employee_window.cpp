#include "employee_window.h"
#include <QDate>

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
    m_welcomeLabel = new QLabel(QString("Welcome, Employee %1").arg(m_employeeId));
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
    
    statsLayout->addWidget(availableRoomsGroup);
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
}

void EmployeeWindow::setupRoomView()
{
    QWidget *roomWidget = new QWidget();
    QVBoxLayout *roomLayout = new QVBoxLayout(roomWidget);
    
    QLabel *roomTitle = new QLabel("Available Rooms");
    roomTitle->setObjectName("sectionTitle");
    roomTitle->setAlignment(Qt::AlignCenter);
    roomLayout->addWidget(roomTitle);
    
    // Room table
    m_roomTable = new QTableWidget();
    m_roomTable->setObjectName("dataTable");
    m_roomTable->setAlternatingRowColors(true);
    m_roomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QStringList headers;
    headers << "Room ID" << "Floor" << "Type" << "Price/Night" << "Status" << "Current Guest";
    m_roomTable->setColumnCount(headers.size());
    m_roomTable->setHorizontalHeaderLabels(headers);
    
    m_roomTable->horizontalHeader()->setStretchLastSection(true);
    
    roomLayout->addWidget(m_roomTable);
    
    // Refresh button
    QPushButton *refreshRoomsBtn = new QPushButton("Refresh Rooms");
    refreshRoomsBtn->setObjectName("actionButton");
    connect(refreshRoomsBtn, &QPushButton::clicked, this, &EmployeeWindow::onViewRooms);
    
    roomLayout->addWidget(refreshRoomsBtn);
    
    m_tabWidget->addTab(roomWidget, "View Rooms");
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
        }
        
        #dataTable::item {
            padding: 8px;
            border: none;
        }
        
        #reportText {
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            background-color: #ecf0f1;
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
        // Update available rooms count (placeholder)
        m_availableRoomsLabel->setText("Available: N/A");
        
        // Update today's bookings count (placeholder)
        m_todayBookingsLabel->setText("Bookings: N/A");
        
    } catch (const std::exception &e) {
        m_statusBar->showMessage(QString("Error updating dashboard: %1").arg(e.what()), 5000);
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
        // Capture room list output
        std::ostringstream roomStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(roomStream.rdbuf());
        
        m_hotelSystem->showRoom();
        
        std::cout.rdbuf(orig);
        
        // For now, clear the table and show placeholder
        m_roomTable->setRowCount(0);
        m_statusBar->showMessage("Room list updated", 3000);
        
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
        customer *cust = m_hotelSystem->findCustomer(customerId);
        if (cust) {
            m_hotelSystem->bookRoom(cust);
            QMessageBox::information(this, "Success", "Room booked successfully!");
            
            // Clear form
            m_customerIdEdit->clear();
            m_roomIdEdit->clear();
            m_checkinDateEdit->setDate(QDate::currentDate());
            m_checkoutDateEdit->setDate(QDate::currentDate().addDays(1));
            
            updateDashboard();
        } else {
            QMessageBox::warning(this, "Error", "Customer not found!");
        }
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
    bool ok;
    int customerId = QInputDialog::getInt(this, "Customer History", 
                                         "Enter customer ID:", 0, 0, 999999, 1, &ok);
    
    if (ok) {
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
