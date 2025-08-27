#include "customer_window.h"
#include <QDate>

CustomerWindow::CustomerWindow(HotelManagementSystem *hotelSystem, customer *customer, QWidget *parent)
    : QMainWindow(parent)
    , m_hotelSystem(hotelSystem)
    , m_customer(customer)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupStyles();
    connectSignals();
    updateDashboard();
    
    setWindowTitle(QString("Hotel Management System - Customer Dashboard (%1)")
                   .arg(QString::fromStdString(customer->getName())));
    setMinimumSize(1000, 700);
    resize(1200, 800);
}

CustomerWindow::~CustomerWindow()
{
    // Save system state when closing
    if (m_hotelSystem) {
        m_hotelSystem->saveSystemState();
    }
}

void CustomerWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // Welcome header
    m_welcomeLabel = new QLabel(QString("Welcome, %1!").arg(QString::fromStdString(m_customer->getName())));
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
    
    // My bookings section
    setupMyBookingsSection();
    
    // Billing section
    setupBillingSection();
    
    // Personal info section
    setupPersonalInfoSection();
    
    mainLayout->addWidget(m_tabWidget);
}

void CustomerWindow::setupDashboard()
{
    m_dashboardWidget = new QWidget();
    QVBoxLayout *dashboardLayout = new QVBoxLayout(m_dashboardWidget);
    dashboardLayout->setSpacing(20);
    dashboardLayout->setContentsMargins(20, 20, 20, 20);
    
    // Statistics cards
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    // Current bookings
    QGroupBox *bookingsGroup = new QGroupBox("Current Bookings");
    bookingsGroup->setObjectName("statsGroup");
    QVBoxLayout *bookingsLayout = new QVBoxLayout(bookingsGroup);
    
    m_currentBookingsLabel = new QLabel("Active: 0");
    m_currentBookingsLabel->setObjectName("statLabel");
    bookingsLayout->addWidget(m_currentBookingsLabel);
    
    // Total bill
    QGroupBox *billGroup = new QGroupBox("Total Bill");
    billGroup->setObjectName("statsGroup");
    QVBoxLayout *billLayout = new QVBoxLayout(billGroup);
    
    m_totalBillLabel = new QLabel("Amount: $0");
    m_totalBillLabel->setObjectName("statLabel");
    billLayout->addWidget(m_totalBillLabel);
    
    // Discount
    QGroupBox *discountGroup = new QGroupBox("Discount");
    discountGroup->setObjectName("statsGroup");
    QVBoxLayout *discountLayout = new QVBoxLayout(discountGroup);
    
    m_discountLabel = new QLabel("Discount: 0%");
    m_discountLabel->setObjectName("statLabel");
    discountLayout->addWidget(m_discountLabel);
    
    statsLayout->addWidget(bookingsGroup);
    statsLayout->addWidget(billGroup);
    statsLayout->addWidget(discountGroup);
    statsLayout->addStretch();
    
    dashboardLayout->addLayout(statsLayout);
    
    // Quick actions
    QGroupBox *quickActionsGroup = new QGroupBox("Quick Actions");
    quickActionsGroup->setObjectName("statsGroup");
    QHBoxLayout *quickActionsLayout = new QHBoxLayout(quickActionsGroup);
    
    QPushButton *viewRoomsBtn = new QPushButton("View Available Rooms");
    QPushButton *bookRoomBtn = new QPushButton("Book Room");
    QPushButton *viewBookingsBtn = new QPushButton("My Bookings");
    QPushButton *viewBillBtn = new QPushButton("View Bill");
    QPushButton *refreshBtn = new QPushButton("Refresh Data");
    
    viewRoomsBtn->setObjectName("actionButton");
    bookRoomBtn->setObjectName("actionButton");
    viewBookingsBtn->setObjectName("actionButton");
    viewBillBtn->setObjectName("actionButton");
    refreshBtn->setObjectName("actionButton");
    
    connect(viewRoomsBtn, &QPushButton::clicked, [this]() { m_tabWidget->setCurrentIndex(1); });
    connect(bookRoomBtn, &QPushButton::clicked, [this]() { m_tabWidget->setCurrentIndex(1); });
    connect(viewBookingsBtn, &QPushButton::clicked, [this]() { m_tabWidget->setCurrentIndex(2); });
    connect(viewBillBtn, &QPushButton::clicked, [this]() { m_tabWidget->setCurrentIndex(3); });
    connect(refreshBtn, &QPushButton::clicked, this, &CustomerWindow::onRefreshData);
    
    quickActionsLayout->addWidget(viewRoomsBtn);
    quickActionsLayout->addWidget(bookRoomBtn);
    quickActionsLayout->addWidget(viewBookingsBtn);
    quickActionsLayout->addWidget(viewBillBtn);
    quickActionsLayout->addWidget(refreshBtn);
    quickActionsLayout->addStretch();
    
    dashboardLayout->addWidget(quickActionsGroup);
    dashboardLayout->addStretch();
    
    m_tabWidget->addTab(m_dashboardWidget, "Dashboard");
}

void CustomerWindow::setupBookingSection()
{
    m_bookingWidget = new QWidget();
    QVBoxLayout *bookingLayout = new QVBoxLayout(m_bookingWidget);
    bookingLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *bookingTitle = new QLabel("Book a Room");
    bookingTitle->setObjectName("sectionTitle");
    bookingTitle->setAlignment(Qt::AlignCenter);
    bookingLayout->addWidget(bookingTitle);
    
    // Available rooms table
    QGroupBox *roomsGroup = new QGroupBox("Available Rooms");
    roomsGroup->setObjectName("tableGroup");
    QVBoxLayout *roomsLayout = new QVBoxLayout(roomsGroup);
    
    m_roomTable = new QTableWidget();
    m_roomTable->setObjectName("dataTable");
    m_roomTable->setAlternatingRowColors(true);
    m_roomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QStringList headers;
    headers << "Room ID" << "Floor" << "Type" << "Price/Night" << "Amenities";
    m_roomTable->setColumnCount(headers.size());
    m_roomTable->setHorizontalHeaderLabels(headers);
    m_roomTable->horizontalHeader()->setStretchLastSection(true);
    
    roomsLayout->addWidget(m_roomTable);
    
    QPushButton *refreshRoomsBtn = new QPushButton("Refresh Available Rooms");
    refreshRoomsBtn->setObjectName("secondaryButton");
    connect(refreshRoomsBtn, &QPushButton::clicked, this, &CustomerWindow::onViewAllRooms);
    roomsLayout->addWidget(refreshRoomsBtn);
    
    bookingLayout->addWidget(roomsGroup);
    
    // Booking form
    QGroupBox *bookingFormGroup = new QGroupBox("Book Selected Room");
    bookingFormGroup->setObjectName("formGroup");
    QGridLayout *formLayout = new QGridLayout(bookingFormGroup);
    
    // Room ID
    QLabel *roomIdLabel = new QLabel("Room ID:");
    m_roomIdEdit = new QLineEdit();
    m_roomIdEdit->setPlaceholderText("Enter room ID or select from table");
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
    
    formLayout->addWidget(roomIdLabel, 0, 0);
    formLayout->addWidget(m_roomIdEdit, 0, 1);
    formLayout->addWidget(checkinLabel, 1, 0);
    formLayout->addWidget(m_checkinDateEdit, 1, 1);
    formLayout->addWidget(checkoutLabel, 2, 0);
    formLayout->addWidget(m_checkoutDateEdit, 2, 1);
    formLayout->addWidget(m_bookRoomBtn, 3, 0, 1, 2);
    
    bookingLayout->addWidget(bookingFormGroup);
    
    // Connect room table selection to room ID field
    connect(m_roomTable, &QTableWidget::itemSelectionChanged, [this]() {
        int currentRow = m_roomTable->currentRow();
        if (currentRow >= 0) {
            QTableWidgetItem *roomIdItem = m_roomTable->item(currentRow, 0);
            if (roomIdItem) {
                m_roomIdEdit->setText(roomIdItem->text());
            }
        }
    });
    
    m_tabWidget->addTab(m_bookingWidget, "Book Room");
}

void CustomerWindow::setupMyBookingsSection()
{
    m_myBookingsWidget = new QWidget();
    QVBoxLayout *bookingsLayout = new QVBoxLayout(m_myBookingsWidget);
    bookingsLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *bookingsTitle = new QLabel("My Bookings");
    bookingsTitle->setObjectName("sectionTitle");
    bookingsTitle->setAlignment(Qt::AlignCenter);
    bookingsLayout->addWidget(bookingsTitle);
    
    // Current bookings table
    QGroupBox *currentBookingsGroup = new QGroupBox("Current Bookings");
    currentBookingsGroup->setObjectName("tableGroup");
    QVBoxLayout *currentLayout = new QVBoxLayout(currentBookingsGroup);
    
    m_bookingsTable = new QTableWidget();
    m_bookingsTable->setObjectName("dataTable");
    m_bookingsTable->setAlternatingRowColors(true);
    m_bookingsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    QStringList bookingHeaders;
    bookingHeaders << "Room ID" << "Room Type" << "Check-in" << "Check-out" << "Total Cost" << "Status";
    m_bookingsTable->setColumnCount(bookingHeaders.size());
    m_bookingsTable->setHorizontalHeaderLabels(bookingHeaders);
    m_bookingsTable->horizontalHeader()->setStretchLastSection(true);
    
    currentLayout->addWidget(m_bookingsTable);
    
    // Booking actions
    QHBoxLayout *bookingActionsLayout = new QHBoxLayout();
    
    m_cancelBookingBtn = new QPushButton("Cancel Selected Booking");
    m_cancelBookingBtn->setObjectName("dangerButton");
    m_cancelBookingBtn->setEnabled(false);
    
    m_viewHistoryBtn = new QPushButton("View Booking History");
    m_viewHistoryBtn->setObjectName("actionButton");
    
    QPushButton *refreshBookingsBtn = new QPushButton("Refresh Bookings");
    refreshBookingsBtn->setObjectName("secondaryButton");
    
    connect(refreshBookingsBtn, &QPushButton::clicked, this, &CustomerWindow::onViewCurrentBookings);
    
    bookingActionsLayout->addWidget(m_cancelBookingBtn);
    bookingActionsLayout->addWidget(m_viewHistoryBtn);
    bookingActionsLayout->addWidget(refreshBookingsBtn);
    bookingActionsLayout->addStretch();
    
    currentLayout->addLayout(bookingActionsLayout);
    bookingsLayout->addWidget(currentBookingsGroup);
    
    // Enable/disable cancel button based on selection
    connect(m_bookingsTable, &QTableWidget::itemSelectionChanged, [this]() {
        m_cancelBookingBtn->setEnabled(m_bookingsTable->currentRow() >= 0);
    });
    
    m_tabWidget->addTab(m_myBookingsWidget, "My Bookings");
}

void CustomerWindow::setupBillingSection()
{
    m_billingWidget = new QWidget();
    QVBoxLayout *billingLayout = new QVBoxLayout(m_billingWidget);
    billingLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *billingTitle = new QLabel("Billing & Payments");
    billingTitle->setObjectName("sectionTitle");
    billingTitle->setAlignment(Qt::AlignCenter);
    billingLayout->addWidget(billingTitle);
    
    // Bill display
    QGroupBox *billGroup = new QGroupBox("Current Bill");
    billGroup->setObjectName("tableGroup");
    QVBoxLayout *billLayout = new QVBoxLayout(billGroup);
    
    m_billTextEdit = new QTextEdit();
    m_billTextEdit->setObjectName("billText");
    m_billTextEdit->setReadOnly(true);
    m_billTextEdit->setMaximumHeight(200);
    m_billTextEdit->setPlainText("Click 'Show Bill' to view your current bill...");
    
    billLayout->addWidget(m_billTextEdit);
    
    // Bill actions
    QHBoxLayout *billActionsLayout = new QHBoxLayout();
    
    m_showBillBtn = new QPushButton("Show My Bill");
    m_showBillBtn->setObjectName("actionButton");
    
    billActionsLayout->addWidget(m_showBillBtn);
    billActionsLayout->addStretch();
    
    billLayout->addLayout(billActionsLayout);
    billingLayout->addWidget(billGroup);
    
    // Payment section
    QGroupBox *paymentGroup = new QGroupBox("Make Payment");
    paymentGroup->setObjectName("formGroup");
    QGridLayout *paymentLayout = new QGridLayout(paymentGroup);
    
    QLabel *payRoomLabel = new QLabel("Room ID to Pay:");
    m_payRoomIdEdit = new QLineEdit();
    m_payRoomIdEdit->setPlaceholderText("Enter room ID for payment");
    m_payRoomIdEdit->setObjectName("lineEdit");
    
    m_payBillBtn = new QPushButton("Pay Bill");
    m_payBillBtn->setObjectName("primaryButton");
    
    paymentLayout->addWidget(payRoomLabel, 0, 0);
    paymentLayout->addWidget(m_payRoomIdEdit, 0, 1);
    paymentLayout->addWidget(m_payBillBtn, 1, 0, 1, 2);
    
    billingLayout->addWidget(paymentGroup);
    billingLayout->addStretch();
    
    m_tabWidget->addTab(m_billingWidget, "Billing");
}

void CustomerWindow::setupPersonalInfoSection()
{
    m_personalInfoWidget = new QWidget();
    QVBoxLayout *infoLayout = new QVBoxLayout(m_personalInfoWidget);
    infoLayout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *infoTitle = new QLabel("Personal Information");
    infoTitle->setObjectName("sectionTitle");
    infoTitle->setAlignment(Qt::AlignCenter);
    infoLayout->addWidget(infoTitle);
    
    // Personal info display
    QGroupBox *infoGroup = new QGroupBox("My Information");
    infoGroup->setObjectName("tableGroup");
    QVBoxLayout *infoGroupLayout = new QVBoxLayout(infoGroup);
    
    m_personalInfoText = new QTextEdit();
    m_personalInfoText->setObjectName("infoText");
    m_personalInfoText->setReadOnly(true);
    
    infoGroupLayout->addWidget(m_personalInfoText);
    
    QPushButton *refreshInfoBtn = new QPushButton("Refresh Information");
    refreshInfoBtn->setObjectName("actionButton");
    connect(refreshInfoBtn, &QPushButton::clicked, this, &CustomerWindow::onViewPersonalInfo);
    
    infoGroupLayout->addWidget(refreshInfoBtn);
    infoLayout->addWidget(infoGroup);
    
    m_tabWidget->addTab(m_personalInfoWidget, "Personal Info");
    
    // Load personal info initially
    onViewPersonalInfo();
}

void CustomerWindow::setupMenuBar()
{
    m_menuBar = menuBar();
    
    // Account menu
    QMenu *accountMenu = m_menuBar->addMenu("&Account");
    
    QAction *personalInfoAction = accountMenu->addAction("&Personal Information");
    connect(personalInfoAction, &QAction::triggered, this, &CustomerWindow::onViewPersonalInfo);
    
    accountMenu->addSeparator();
    
    QAction *logoutAction = accountMenu->addAction("&Logout");
    logoutAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(logoutAction, &QAction::triggered, this, &CustomerWindow::onLogout);
    
    // Booking menu
    QMenu *bookingMenu = m_menuBar->addMenu("&Booking");
    
    QAction *viewRoomsAction = bookingMenu->addAction("View &Available Rooms");
    connect(viewRoomsAction, &QAction::triggered, this, &CustomerWindow::onViewAllRooms);
    
    QAction *bookRoomAction = bookingMenu->addAction("&Book Room");
    connect(bookRoomAction, &QAction::triggered, this, &CustomerWindow::onBookRoom);
    
    QAction *viewBookingsAction = bookingMenu->addAction("&My Bookings");
    connect(viewBookingsAction, &QAction::triggered, this, &CustomerWindow::onViewCurrentBookings);
    
    QAction *bookingHistoryAction = bookingMenu->addAction("Booking &History");
    connect(bookingHistoryAction, &QAction::triggered, this, &CustomerWindow::onViewBookingHistory);
    
    // Billing menu
    QMenu *billingMenu = m_menuBar->addMenu("Bi&lling");
    
    QAction *showBillAction = billingMenu->addAction("&Show Bill");
    connect(showBillAction, &QAction::triggered, this, &CustomerWindow::onShowBill);
    
    QAction *payBillAction = billingMenu->addAction("&Pay Bill");
    connect(payBillAction, &QAction::triggered, this, &CustomerWindow::onPayBill);
}

void CustomerWindow::setupStatusBar()
{
    m_statusBar = statusBar();
    m_statusBar->showMessage("Ready");
    
    // Add permanent widgets to status bar
    QLabel *userLabel = new QLabel(QString("Logged in as: %1 (ID: %2)")
                                   .arg(QString::fromStdString(m_customer->getName()))
                                   .arg(m_customer->getID()));
    m_statusBar->addPermanentWidget(userLabel);
}

void CustomerWindow::setupStyles()
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
        
        #tableGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #27ae60;
            border-radius: 10px;
            margin: 5px;
            padding-top: 10px;
        }
        
        #tableGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #27ae60;
            font-weight: bold;
        }
        
        #formGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #e67e22;
            border-radius: 10px;
            margin: 5px;
            padding-top: 10px;
        }
        
        #formGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #e67e22;
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
        
        #dangerButton {
            background-color: #e74c3c;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 5px;
        }
        
        #dangerButton:hover {
            background-color: #c0392b;
        }
        
        #dangerButton:disabled {
            background-color: #bdc3c7;
            color: #7f8c8d;
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
        
        #billText, #infoText {
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            font-family: 'Courier New', monospace;
            font-size: 12px;
            background-color: #ecf0f1;
        }
    )");
}

void CustomerWindow::connectSignals()
{
    connect(m_bookRoomBtn, &QPushButton::clicked, this, &CustomerWindow::onBookRoom);
    connect(m_cancelBookingBtn, &QPushButton::clicked, this, &CustomerWindow::onCancelRoom);
    connect(m_viewHistoryBtn, &QPushButton::clicked, this, &CustomerWindow::onViewBookingHistory);
    connect(m_showBillBtn, &QPushButton::clicked, this, &CustomerWindow::onShowBill);
    connect(m_payBillBtn, &QPushButton::clicked, this, &CustomerWindow::onPayBill);
}

void CustomerWindow::updateDashboard()
{
    if (!m_customer) return;
    
    try {
        // Update current bookings count
        std::vector<current_booking> currentBookings = m_customer->getCurrentBookings();
        m_currentBookingsLabel->setText(QString("Active: %1").arg(currentBookings.size()));
        
        // Update total bill
        int totalBill = m_customer->getTotalBill();
        m_totalBillLabel->setText(QString("Amount: $%1").arg(totalBill));
        
        // Update discount
        int discount = m_customer->getDiscount();
        m_discountLabel->setText(QString("Discount: %1%").arg(discount));
        
    } catch (const std::exception &e) {
        m_statusBar->showMessage(QString("Error updating dashboard: %1").arg(e.what()), 5000);
    }
}

void CustomerWindow::refreshRoomTable()
{
    // This would populate the room table with available rooms
    // Implementation depends on hotel class methods
    m_roomTable->setRowCount(0);
}

void CustomerWindow::refreshBookingsTable()
{
    if (!m_customer) return;
    
    try {
        m_bookingsTable->setRowCount(0);
        
        std::vector<current_booking> bookings = m_customer->getCurrentBookings();
        
        for (size_t i = 0; i < bookings.size(); ++i) {
            const current_booking &booking = bookings[i];
            
            m_bookingsTable->insertRow(i);
            
            m_bookingsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(booking.roomID)));
            m_bookingsTable->setItem(i, 1, new QTableWidgetItem("Room Type")); // Would need room type from roomPtr
            m_bookingsTable->setItem(i, 2, new QTableWidgetItem(QString("%1/%2/%3")
                .arg(booking.checkin.day).arg(booking.checkin.month).arg(booking.checkin.year)));
            m_bookingsTable->setItem(i, 3, new QTableWidgetItem(QString("%1/%2/%3")
                .arg(booking.checkout.day).arg(booking.checkout.month).arg(booking.checkout.year)));
            m_bookingsTable->setItem(i, 4, new QTableWidgetItem(QString::number(booking.bill)));
            m_bookingsTable->setItem(i, 5, new QTableWidgetItem("Active"));
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to refresh bookings: %1").arg(e.what()));
    }
}

void CustomerWindow::onLogout()
{
    int reply = QMessageBox::question(this, "Logout", 
                                      "Are you sure you want to logout?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_hotelSystem->saveSystemState();
        close();
    }
}

void CustomerWindow::onRefreshData()
{
    updateDashboard();
    refreshRoomTable();
    refreshBookingsTable();
    m_statusBar->showMessage("Data refreshed", 3000);
}

void CustomerWindow::onViewAllRooms()
{
    try {
        // Switch to booking tab
        m_tabWidget->setCurrentIndex(1);
        
        // Capture room output and populate table
        std::ostringstream roomStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(roomStream.rdbuf());
        
        m_customer->viewAllRooms(m_hotelSystem->getHotel());
        
        std::cout.rdbuf(orig);
        
        refreshRoomTable();
        m_statusBar->showMessage("Available rooms loaded", 3000);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load rooms: %1").arg(e.what()));
    }
}

void CustomerWindow::onBookRoom()
{
    QString roomId = m_roomIdEdit->text().trimmed();
    QDate checkinDate = m_checkinDateEdit->date();
    QDate checkoutDate = m_checkoutDateEdit->date();
    
    if (roomId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a room ID.");
        return;
    }
    
    if (checkinDate >= checkoutDate) {
        QMessageBox::warning(this, "Date Error", "Check-out date must be after check-in date.");
        return;
    }
    
    try {
        date checkin = {checkinDate.day(), checkinDate.month(), checkinDate.year()};
        date checkout = {checkoutDate.day(), checkoutDate.month(), checkoutDate.year()};
        
        if (m_customer->bookRoom(m_hotelSystem->getHotel(), roomId.toStdString(), checkin, checkout)) {
            QMessageBox::information(this, "Success", "Room booked successfully!");
            
            // Clear form
            m_roomIdEdit->clear();
            m_checkinDateEdit->setDate(QDate::currentDate());
            m_checkoutDateEdit->setDate(QDate::currentDate().addDays(1));
            
            updateDashboard();
            refreshBookingsTable();
        } else {
            QMessageBox::warning(this, "Booking Failed", "Failed to book the room. It may not be available for the selected dates.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to book room: %1").arg(e.what()));
    }
}

void CustomerWindow::onCancelRoom()
{
    int currentRow = m_bookingsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a booking to cancel.");
        return;
    }
    
    QString roomId = m_bookingsTable->item(currentRow, 0)->text();
    
    int reply = QMessageBox::question(this, "Cancel Booking", 
                                      QString("Are you sure you want to cancel the booking for room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            if (m_customer->cancelRoom(roomId.toStdString())) {
                QMessageBox::information(this, "Success", "Booking cancelled successfully!");
                refreshBookingsTable();
                updateDashboard();
            } else {
                QMessageBox::warning(this, "Cancel Failed", "Failed to cancel the booking.");
            }
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to cancel booking: %1").arg(e.what()));
        }
    }
}

void CustomerWindow::onViewBookingHistory()
{
    try {
        // Switch to reports (we could create a separate history tab)
        std::ostringstream historyStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(historyStream.rdbuf());
        
        m_customer->viewMyBookingHistory();
        
        std::cout.rdbuf(orig);
        
        QString history = QString::fromStdString(historyStream.str());
        if (history.isEmpty()) {
            history = "No booking history available.";
        }
        
        // Show in a message box for now
        QMessageBox::information(this, "My Booking History", history);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load booking history: %1").arg(e.what()));
    }
}

void CustomerWindow::onViewCurrentBookings()
{
    // Switch to my bookings tab
    m_tabWidget->setCurrentIndex(2);
    refreshBookingsTable();
}

void CustomerWindow::onShowBill()
{
    try {
        // Switch to billing tab
        m_tabWidget->setCurrentIndex(3);
        
        std::ostringstream billStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(billStream.rdbuf());
        
        m_customer->showBill();
        
        std::cout.rdbuf(orig);
        
        QString bill = QString::fromStdString(billStream.str());
        if (bill.isEmpty()) {
            bill = "No bill information available.";
        }
        
        m_billTextEdit->setPlainText(bill);
        m_statusBar->showMessage("Bill loaded", 3000);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load bill: %1").arg(e.what()));
    }
}

void CustomerWindow::onPayBill()
{
    QString roomId = m_payRoomIdEdit->text().trimmed();
    
    if (roomId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a room ID for payment.");
        return;
    }
    
    int reply = QMessageBox::question(this, "Confirm Payment", 
                                      QString("Are you sure you want to pay the bill for room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            if (m_customer->payBill(roomId.toStdString())) {
                QMessageBox::information(this, "Success", "Payment processed successfully!");
                m_payRoomIdEdit->clear();
                updateDashboard();
                onShowBill(); // Refresh bill display
            } else {
                QMessageBox::warning(this, "Payment Failed", "Failed to process payment. Please check the room ID.");
            }
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to process payment: %1").arg(e.what()));
        }
    }
}

void CustomerWindow::onViewPersonalInfo()
{
    try {
        std::ostringstream infoStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(infoStream.rdbuf());
        
        m_customer->showInfo();
        
        std::cout.rdbuf(orig);
        
        QString info = QString::fromStdString(infoStream.str());
        if (info.isEmpty()) {
            info = QString("Customer ID: %1\nName: %2\nPhone: %3\nEmail: %4\nGender: %5\nDiscount: %6%\nTotal Bill: $%7")
                .arg(m_customer->getID())
                .arg(QString::fromStdString(m_customer->getName()))
                .arg(QString::fromStdString(m_customer->getPhone()))
                .arg(QString::fromStdString(m_customer->getEmail()))
                .arg(m_customer->getGender() ? "Male" : "Female")
                .arg(m_customer->getDiscount())
                .arg(m_customer->getTotalBill());
        }
        
        m_personalInfoText->setPlainText(info);
        m_statusBar->showMessage("Personal information loaded", 3000);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load personal information: %1").arg(e.what()));
    }
}

