#include "customer_window.h"
#include <QDate>
#include <QDebug>
#include <sstream>
#include <iostream>

CustomerWindow::CustomerWindow(HotelManagementSystem *hotelSystem, customer *customer, QWidget *parent)
    : QMainWindow(parent)
    , m_hotelSystem(hotelSystem)
    , m_customer(customer)
{
    qDebug() << "CustomerWindow constructor started";
    
    if (!customer) {
        qDebug() << "ERROR: Customer pointer is null";
        throw std::runtime_error("Customer pointer is null");
    }
    
    if (!hotelSystem) {
        qDebug() << "ERROR: Hotel system pointer is null";
        throw std::runtime_error("Hotel system pointer is null");
    }
    
    qDebug() << "Customer found, attempting to get name...";
    try {
        QString customerName = QString::fromStdString(customer->getName());
        qDebug() << "Customer name:" << customerName;
        qDebug() << "Customer ID:" << customer->getID();
    } catch (const std::exception& e) {
        qDebug() << "Error getting customer info:" << e.what();
        throw std::runtime_error(QString("Failed to access customer data: %1").arg(e.what()).toStdString());
    }
    
    try {
        qDebug() << "Setting up UI...";
        setupUI();
        qDebug() << "UI setup completed";
        
        qDebug() << "Setting up menu bar...";
        setupMenuBar();
        qDebug() << "Menu bar setup completed";
        
        qDebug() << "Setting up status bar...";
        setupStatusBar();
        qDebug() << "Status bar setup completed";
        
        qDebug() << "Setting up styles...";
        setupStyles();
        qDebug() << "Styles setup completed";
        
        qDebug() << "Connecting signals...";
        connectSignals();
        qDebug() << "Signals connected";
        
        qDebug() << "Updating dashboard...";
        updateDashboard();
        qDebug() << "Dashboard updated";
        
        qDebug() << "Setting window properties...";
        setWindowTitle(QString("Hotel Management System - Customer Dashboard (%1)")
                       .arg(QString::fromStdString(customer->getName())));
        setMinimumSize(1000, 700);
        resize(1200, 800);
        qDebug() << "Window properties set";
        
        qDebug() << "CustomerWindow constructor completed successfully";
    } catch (const std::exception& e) {
        qDebug() << "Exception during CustomerWindow initialization:" << e.what();
        throw std::runtime_error(QString("Failed to initialize customer window: %1").arg(e.what()).toStdString());
    }
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
    qDebug() << "setupUI: Creating central widget...";
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    qDebug() << "setupUI: Creating main layout...";
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    qDebug() << "setupUI: Creating welcome label...";
    // Welcome header
    QString customerName = m_customer ? QString::fromStdString(m_customer->getName()) : "Guest";
    m_welcomeLabel = new QLabel(QString("Welcome, %1!").arg(customerName));
    m_welcomeLabel->setObjectName("welcomeLabel");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_welcomeLabel);
    
    qDebug() << "setupUI: Creating tab widget...";
    // Tab widget
    m_tabWidget = new QTabWidget();
    m_tabWidget->setObjectName("mainTabWidget");
    
    qDebug() << "setupUI: Setting up dashboard...";
    // Dashboard tab
    setupDashboard();
    
    qDebug() << "setupUI: Setting up booking section...";
    // Booking section
    setupBookingSection();
    
    qDebug() << "setupUI: Setting up my bookings section...";
    // My bookings section
    setupMyBookingsSection();
    
    qDebug() << "setupUI: Setting up billing section...";
    // Billing section
    setupBillingSection();
    
    qDebug() << "setupUI: Setting up personal info section...";
    // Personal info section
    setupPersonalInfoSection();
    
    qDebug() << "setupUI: Adding tab widget to main layout...";
    mainLayout->addWidget(m_tabWidget);
    qDebug() << "setupUI: Completed successfully";
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
    headers << "Room ID" << "Floor" << "Type" << "Beds" << "Capacity" << "Price/Night" << "Amenities";
    m_roomTable->setColumnCount(headers.size());
    m_roomTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths - make Type and Amenities columns wider for full information
    m_roomTable->setColumnWidth(0, 80);  // Room ID
    m_roomTable->setColumnWidth(1, 60);  // Floor
    m_roomTable->setColumnWidth(2, 270); // Type - wider for full names
    m_roomTable->setColumnWidth(3, 100); // Beds
    m_roomTable->setColumnWidth(4, 80);  // Capacity
    m_roomTable->setColumnWidth(5, 100); // Price/Night
    m_roomTable->horizontalHeader()->setStretchLastSection(true); // Amenities stretches
    
    roomsLayout->addWidget(m_roomTable);
    
    // Action buttons
    QHBoxLayout *roomActionLayout = new QHBoxLayout();
    
    QPushButton *refreshRoomsBtn = new QPushButton("Refresh Available Rooms");
    refreshRoomsBtn->setObjectName("secondaryButton");
    connect(refreshRoomsBtn, &QPushButton::clicked, this, &CustomerWindow::onViewAllRooms);
    
    QPushButton *viewRoomDetailsBtn = new QPushButton("View Room Details");
    viewRoomDetailsBtn->setObjectName("secondaryButton");
    connect(viewRoomDetailsBtn, &QPushButton::clicked, this, &CustomerWindow::onViewRoomDetails);
    
    roomActionLayout->addWidget(refreshRoomsBtn);
    roomActionLayout->addWidget(viewRoomDetailsBtn);
    roomActionLayout->addStretch();
    
    roomsLayout->addLayout(roomActionLayout);
    
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
    
    // Load room data initially
    refreshRoomTable();
    
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
    
    // Set column widths - make Room Type column wider
    m_bookingsTable->setColumnWidth(0, 80);  // Room ID
    m_bookingsTable->setColumnWidth(1, 270); // Room Type - wider for full names
    m_bookingsTable->setColumnWidth(2, 100); // Check-in
    m_bookingsTable->setColumnWidth(3, 100); // Check-out
    m_bookingsTable->setColumnWidth(4, 100); // Total Cost
    m_bookingsTable->horizontalHeader()->setStretchLastSection(true); // Status stretches
    
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
    
    // Load booking data initially
    refreshBookingsTable();
    
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
    
    // Auto-load personal information when section is set up
    loadPersonalInfoSafely();
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
        
        #dataTable::item:selected {
            background-color: #3498db;
            color: white;
        }
        
        QTextEdit {
            background-color: white;
            color: black;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            padding: 8px;
        }
        
        QTextEdit:focus {
            border-color: #3498db;
        }
        }
        
        #billText, #infoText {
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
            background-color: white;
            color: black;
            padding: 12px;
            line-height: 1.4;
        }
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
    if (!m_hotelSystem) return;
    
    try {
        // Clear existing data
        m_roomTable->setRowCount(0);
        
        // Get hotel and populate room table with available rooms only
        hotel& h = m_hotelSystem->getHotel();
        std::vector<floor_> floors = h.getFloors();
        
        int rowIndex = 0;
        for (size_t floorIndex = 0; floorIndex < floors.size(); ++floorIndex) {
            floor_ currentFloor = floors[floorIndex];  // Make a copy to call non-const methods
            std::vector<room> roomsOnFloor = currentFloor.findAllRooms();
            
            for (auto& r : roomsOnFloor) {
                // Only show available rooms
                if (r.isAvailable()) {
                    m_roomTable->insertRow(rowIndex);
                    
                    // Get bed and capacity info based on room type
                    QString bedsInfo, capacityInfo, amenitiesInfo;
                    QString typeName = QString::fromStdString(r.getTypeName());
                    
                    if (typeName.contains("Single normal")) {
                        bedsInfo = "1 Single";
                        capacityInfo = "1-2";
                        amenitiesInfo = "TV, Bath, Basic";
                    } else if (typeName.contains("Single VIP")) {
                        bedsInfo = "1 Large";
                        capacityInfo = "1-2";
                        amenitiesInfo = "TV, Bath, Balcony, Fridge";
                    } else if (typeName.contains("Double")) {
                        bedsInfo = "1 Large";
                        capacityInfo = "2-3";
                        amenitiesInfo = "TV, Bath, Balcony, Loving chair";
                    } else if (typeName.contains("Family")) {
                        bedsInfo = "2 Large";
                        capacityInfo = "4-6";
                        amenitiesInfo = "TV, Bath, Balcony, Fridge, Living area";
                    } else {
                        bedsInfo = "1 Single";
                        capacityInfo = "1-2";
                        amenitiesInfo = "Standard amenities";
                    }
                    
                    // Set room data in table
                    m_roomTable->setItem(rowIndex, 0, new QTableWidgetItem(QString::fromStdString(r.getID())));
                    m_roomTable->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(floorIndex + 1)));
                    m_roomTable->setItem(rowIndex, 2, new QTableWidgetItem(QString::fromStdString(r.getTypeName())));
                    m_roomTable->setItem(rowIndex, 3, new QTableWidgetItem(bedsInfo));
                    m_roomTable->setItem(rowIndex, 4, new QTableWidgetItem(capacityInfo));
                    m_roomTable->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(r.checkPrice(), 'f', 0) + " VND"));
                    m_roomTable->setItem(rowIndex, 6, new QTableWidgetItem(amenitiesInfo));

                    rowIndex++;
                }
            }
        }
        
        // If no available rooms found, show message
        if (rowIndex == 0) {
            m_roomTable->insertRow(0);
            m_roomTable->setItem(0, 0, new QTableWidgetItem("No available rooms"));
            m_roomTable->setItem(0, 1, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 2, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 3, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 4, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 5, new QTableWidgetItem(""));
            m_roomTable->setItem(0, 6, new QTableWidgetItem(""));
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load available rooms: %1").arg(e.what()));
    }
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
            
            // Get room type from hotel system
            room* bookedRoom = m_hotelSystem->getHotel().findRoomByNumber(booking.roomID);
            QString roomType = bookedRoom ? QString::fromStdString(bookedRoom->getTypeName()) : "Unknown";
            
            m_bookingsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(booking.roomID)));
            m_bookingsTable->setItem(i, 1, new QTableWidgetItem(roomType));
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
        
        // Refresh room table with available rooms
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
        
        // Create a dialog to show booking history
        QDialog *historyDialog = new QDialog(this);
        historyDialog->setWindowTitle("My Booking History");
        historyDialog->resize(900, 500);
        
        QVBoxLayout *layout = new QVBoxLayout(historyDialog);
        QTextEdit *textEdit = new QTextEdit();
        textEdit->setPlainText(history);
        textEdit->setReadOnly(true);
        textEdit->setFont(QFont("Courier New", 10)); // Set font size to 10
        textEdit->setWordWrapMode(QTextOption::NoWrap);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        
        QPushButton *closeBtn = new QPushButton("Close");
        closeBtn->setFixedWidth(100);
        connect(closeBtn, &QPushButton::clicked, historyDialog, &QDialog::accept);
        
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        buttonLayout->addWidget(closeBtn);
        buttonLayout->addStretch();
        
        layout->addWidget(textEdit);
        layout->addLayout(buttonLayout);
        
        historyDialog->exec();
        delete historyDialog;
        
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
    qDebug() << "onPayBill: Starting payment process...";
    
    try {
        // Check if customer object is valid
        if (!m_customer) {
            qDebug() << "onPayBill: Customer object is null";
            QMessageBox::critical(this, "Error", "Customer information not available. Please try logging in again.");
            return;
        }
        
        // Check if hotel system is available
        if (!m_hotelSystem) {
            qDebug() << "onPayBill: Hotel system is null";
            QMessageBox::critical(this, "Error", "Hotel system not available. Please try logging in again.");
            return;
        }
        
        QString roomId = m_payRoomIdEdit->text().trimmed();
        
        if (roomId.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter a room ID for payment.");
            return;
        }
        
        // Validate room ID format (should be numeric)
        bool ok;
        int roomIdInt = roomId.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid numeric room ID.");
            return;
        }
        
        qDebug() << "onPayBill: Processing payment for room ID:" << roomId;
        
        int reply = QMessageBox::question(this, "Confirm Payment", 
                                          QString("Are you sure you want to pay the bill for room %1?").arg(roomId),
                                          QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            try {
                qDebug() << "onPayBill: User confirmed payment, calling customer payBill...";
                
                // Check if customer has any outstanding bills first
                double totalBill = 0.0;
                try {
                    totalBill = m_customer->getTotalBill();
                    qDebug() << "onPayBill: Customer total bill:" << totalBill;
                } catch (const std::exception &e) {
                    qDebug() << "onPayBill: Error getting total bill:" << e.what();
                    QMessageBox::warning(this, "Warning", "Unable to verify current bill amount. Payment may not be processed correctly.");
                }
                
                // Try to process payment
                bool paymentResult = false;
                try {
                    paymentResult = m_customer->payBill(roomId.toStdString());
                    qDebug() << "onPayBill: Payment result:" << paymentResult;
                } catch (const std::exception &e) {
                    qDebug() << "onPayBill: Exception during payment:" << e.what();
                    QMessageBox::critical(this, "Payment Error", 
                        QString("Failed to process payment: %1\n\nThis may be due to:\n- Invalid room ID\n- No outstanding bill for this room\n- System error").arg(e.what()));
                    return;
                }
                
                if (paymentResult) {
                    QMessageBox::information(this, "Payment Successful", 
                        QString("Payment for room %1 has been processed successfully!\n\nYour bill has been updated.").arg(roomId));
                    
                    // Clear the input field
                    m_payRoomIdEdit->clear();
                    
                    // Try to refresh displays
                    try {
                        updateDashboard();
                        qDebug() << "onPayBill: Dashboard updated successfully";
                    } catch (const std::exception &e) {
                        qDebug() << "onPayBill: Error updating dashboard:" << e.what();
                    }
                    
                    try {
                        onShowBill(); // Refresh bill display
                        qDebug() << "onPayBill: Bill display refreshed successfully";
                    } catch (const std::exception &e) {
                        qDebug() << "onPayBill: Error refreshing bill display:" << e.what();
                    }
                    
                    // Try to refresh bookings table
                    try {
                        refreshBookingsTable();
                        qDebug() << "onPayBill: Bookings table refreshed successfully";
                    } catch (const std::exception &e) {
                        qDebug() << "onPayBill: Error refreshing bookings:" << e.what();
                    }
                    
                } else {
                    QMessageBox::warning(this, "Payment Failed", 
                        QString("Failed to process payment for room %1.\n\nPossible reasons:\n- No outstanding bill for this room\n- Room ID not found\n- Payment already processed\n\nPlease verify the room ID and try again.").arg(roomId));
                }
                
            } catch (const std::exception &e) {
                qDebug() << "onPayBill: Unexpected error during payment processing:" << e.what();
                QMessageBox::critical(this, "Payment Error", 
                    QString("An unexpected error occurred during payment processing:\n%1\n\nPlease contact support if this problem persists.").arg(e.what()));
            }
        } else {
            qDebug() << "onPayBill: User cancelled payment";
        }
        
    } catch (const std::exception &e) {
        qDebug() << "onPayBill: Critical error in payment function:" << e.what();
        QMessageBox::critical(this, "Critical Error", 
            QString("A critical error occurred: %1\n\nPlease restart the application and try again.").arg(e.what()));
    } catch (...) {
        qDebug() << "onPayBill: Unknown critical error occurred";
        QMessageBox::critical(this, "Critical Error", 
            "An unknown error occurred during payment processing.\n\nPlease restart the application and try again.");
    }
}

void CustomerWindow::onViewPersonalInfo()
{
    try {
        if (!m_customer) {
            QMessageBox::warning(this, "Error", "Customer information not available");
            return;
        }
        
        QString info;
        
        // Basic info that should be safe
        try {
            info = QString("Customer ID: %1\nName: %2\n")
                .arg(m_customer->getID())
                .arg(QString::fromStdString(m_customer->getName()));
        } catch (const std::exception &e) {
            info = QString("Customer ID: %1\nName: Unable to retrieve\n").arg(m_customer->getID());
        }
        
        // Try to get phone safely
        try {
            info += QString("Phone: %1\n").arg(QString::fromStdString(m_customer->getPhone()));
        } catch (const std::exception &e) {
            info += "Phone: Unable to retrieve\n";
        }
        
        // Try to get email safely
        try {
            info += QString("Email: %1\n").arg(QString::fromStdString(m_customer->getEmail()));
        } catch (const std::exception &e) {
            info += "Email: Unable to retrieve\n";
        }
        
        // Try to get gender safely
        try {
            info += QString("Gender: %1\n").arg(m_customer->getGender() ? "Male" : "Female");
        } catch (const std::exception &e) {
            info += "Gender: Unable to retrieve\n";
        }
        
        // Try to get discount safely
        try {
            info += QString("Discount: %1%\n").arg(m_customer->getDiscount());
        } catch (const std::exception &e) {
            info += "Discount: Unable to retrieve\n";
        }
        
        // Try to get total bill safely
        try {
            info += QString("Total Bill: $%1\n").arg(m_customer->getTotalBill());
        } catch (const std::exception &e) {
            info += "Total Bill: Unable to retrieve\n";
        }
        
        m_personalInfoText->setPlainText(info);
        m_statusBar->showMessage("Personal information loaded", 3000);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load personal information: %1").arg(e.what()));
    }
}

void CustomerWindow::loadPersonalInfoSafely()
{
    qDebug() << "loadPersonalInfoSafely: Starting to load personal info...";
    
    try {
        if (!m_customer) {
            qDebug() << "loadPersonalInfoSafely: Customer object is null, setting default message";
            m_personalInfoText->setPlainText("Customer information not available.\nPlease click 'Refresh Information' to try again.");
            return;
        }

        QString info;
        
        // Basic info that should be safe
        try {
            info = QString("=== Personal Information ===\n\n");
            info += QString("Customer ID: %1\n").arg(m_customer->getID());
            info += QString("Name: %1\n").arg(QString::fromStdString(m_customer->getName()));
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting basic info:" << e.what();
            info = QString("=== Personal Information ===\n\n");
            info += QString("Customer ID: %1\n").arg(m_customer->getID());
            info += "Name: Unable to retrieve\n";
        }
        
        // Try to get phone safely
        try {
            info += QString("Phone: %1\n").arg(QString::fromStdString(m_customer->getPhone()));
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting phone:" << e.what();
            info += "Phone: Unable to retrieve\n";
        }
        
        // Try to get email safely
        try {
            info += QString("Email: %1\n").arg(QString::fromStdString(m_customer->getEmail()));
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting email:" << e.what();
            info += "Email: Unable to retrieve\n";
        }
        
        // Try to get gender safely
        try {
            info += QString("Gender: %1\n").arg(m_customer->getGender() ? "Male" : "Female");
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting gender:" << e.what();
            info += "Gender: Unable to retrieve\n";
        }
        
        // Try to get discount safely
        try {
            info += QString("Discount Rate: %1%\n").arg(m_customer->getDiscount());
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting discount:" << e.what();
            info += "Discount Rate: Unable to retrieve\n";
        }
        
        // Try to get total bill safely
        try {
            info += QString("Total Outstanding Bill: $%1\n").arg(m_customer->getTotalBill());
        } catch (const std::exception &e) {
            qDebug() << "loadPersonalInfoSafely: Error getting total bill:" << e.what();
            info += "Total Outstanding Bill: Unable to retrieve\n";
        }
        
        // Add some additional info
        info += QString("\n=== Account Status ===\n");
        info += QString("Account Active: Yes\n");
        info += QString("Last Updated: %1\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        
        m_personalInfoText->setPlainText(info);
        qDebug() << "loadPersonalInfoSafely: Personal information loaded successfully";
        
    } catch (const std::exception &e) {
        qDebug() << "loadPersonalInfoSafely: Critical error:" << e.what();
        m_personalInfoText->setPlainText(QString("Error loading personal information: %1\n\nPlease click 'Refresh Information' to try again.").arg(e.what()));
    }
}

void CustomerWindow::onViewRoomDetails() {
    if (!m_roomTable) return;
    
    int currentRow = m_roomTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* roomItem = m_roomTable->item(currentRow, 0);
        if (roomItem) {
            QString roomId = roomItem->text();
            
            try {
                hotel& h = m_hotelSystem->getHotel();
                room* r = h.findRoomByNumber(roomId.toStdString());
                
                if (r) {
                    QString details = QString("Room %1\n").arg(roomId);
                    details += QString("Room Type: %1\n").arg(QString::fromStdString(r->getTypeName()));
                    
                    // Capture furniture details
                
                    std::ostringstream furnitureStream;
                    std::streambuf* origCout = std::cout.rdbuf();
                    std::cout.rdbuf(furnitureStream.rdbuf());
                    
                    r->displayFurniture();
                    
                    std::cout.rdbuf(origCout);
                    QString furnitureInfo = QString::fromStdString(furnitureStream.str());
                    if (!furnitureInfo.isEmpty()) {
                        details += furnitureInfo;
                    }
                    
                    // Capture items details  
        
                    std::ostringstream itemsStream;
                    std::cout.rdbuf(itemsStream.rdbuf());
                    
                    r->displayItem();
                    
                    std::cout.rdbuf(origCout);
                    QString itemsInfo = QString::fromStdString(itemsStream.str());
                    if (!itemsInfo.isEmpty()) {
                        details += itemsInfo;
                    }
                    
                    QMessageBox::information(this, QString("Room %1 Details").arg(roomId), details);
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

