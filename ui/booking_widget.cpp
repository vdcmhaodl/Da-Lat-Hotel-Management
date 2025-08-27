#include "booking_widget.h"
#include <QDate>

BookingWidget::BookingWidget(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QWidget(parent)
    , m_hotelSystem(hotelSystem)
    , m_customer(nullptr)
    , m_isEmployee(false)
{
    setupUI();
    setupStyles();
    connectSignals();
    refreshData();
}

void BookingWidget::setCustomer(customer *customer)
{
    m_customer = customer;
    
    // Hide customer ID field if booking for self
    if (m_customer && !m_isEmployee) {
        m_customerIdEdit->setVisible(false);
        m_customerIdEdit->setText(QString::number(m_customer->getID()));
    }
    
    refreshData();
}

void BookingWidget::setEmployee(bool isEmployee)
{
    m_isEmployee = isEmployee;
    
    // Show customer ID field for employees
    m_customerIdEdit->setVisible(isEmployee);
    
    if (isEmployee) {
        m_customerIdEdit->setPlaceholderText("Enter customer ID");
    }
}

void BookingWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(15);
    
    // Title
    QLabel *titleLabel = new QLabel("Room Booking System");
    titleLabel->setObjectName("pageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Setup sections
    setupBookingForm();
    setupAvailableRooms();
    setupBookingsList();
}

void BookingWidget::setupBookingForm()
{
    m_bookingFormGroup = new QGroupBox("Book a Room");
    m_bookingFormGroup->setObjectName("formGroup");
    
    QGridLayout *formLayout = new QGridLayout(m_bookingFormGroup);
    
    // Customer ID (for employees)
    QLabel *customerLabel = new QLabel("Customer ID:");
    m_customerIdEdit = new QLineEdit();
    m_customerIdEdit->setPlaceholderText("Enter customer ID");
    m_customerIdEdit->setObjectName("lineEdit");
    
    // Room ID
    QLabel *roomLabel = new QLabel("Room ID:");
    m_roomIdEdit = new QLineEdit();
    m_roomIdEdit->setPlaceholderText("Select from available rooms or enter manually");
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
    
    // Layout
    int row = 0;
    formLayout->addWidget(customerLabel, row, 0);
    formLayout->addWidget(m_customerIdEdit, row++, 1);
    formLayout->addWidget(roomLabel, row, 0);
    formLayout->addWidget(m_roomIdEdit, row++, 1);
    formLayout->addWidget(checkinLabel, row, 0);
    formLayout->addWidget(m_checkinDateEdit, row++, 1);
    formLayout->addWidget(checkoutLabel, row, 0);
    formLayout->addWidget(m_checkoutDateEdit, row++, 1);
    formLayout->addWidget(m_bookRoomBtn, row, 0, 1, 2);
    
    m_mainLayout->addWidget(m_bookingFormGroup);
}

void BookingWidget::setupAvailableRooms()
{
    m_availableRoomsGroup = new QGroupBox("Available Rooms");
    m_availableRoomsGroup->setObjectName("tableGroup");
    
    QVBoxLayout *roomsLayout = new QVBoxLayout(m_availableRoomsGroup);
    
    // Rooms table
    m_roomsTable = new QTableWidget();
    m_roomsTable->setObjectName("dataTable");
    m_roomsTable->setAlternatingRowColors(true);
    m_roomsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_roomsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    QStringList headers;
    headers << "Room ID" << "Floor" << "Type" << "Price/Night" << "Status";
    m_roomsTable->setColumnCount(headers.size());
    m_roomsTable->setHorizontalHeaderLabels(headers);
    m_roomsTable->horizontalHeader()->setStretchLastSection(true);
    
    roomsLayout->addWidget(m_roomsTable);
    
    // Refresh button
    QPushButton *refreshRoomsBtn = new QPushButton("Refresh Available Rooms");
    refreshRoomsBtn->setObjectName("actionButton");
    connect(refreshRoomsBtn, &QPushButton::clicked, this, &BookingWidget::populateAvailableRooms);
    
    roomsLayout->addWidget(refreshRoomsBtn);
    
    m_mainLayout->addWidget(m_availableRoomsGroup);
}

void BookingWidget::setupBookingsList()
{
    m_bookingsGroup = new QGroupBox("Current Bookings");
    m_bookingsGroup->setObjectName("tableGroup");
    
    QVBoxLayout *bookingsLayout = new QVBoxLayout(m_bookingsGroup);
    
    // Bookings table
    m_bookingsTable = new QTableWidget();
    m_bookingsTable->setObjectName("dataTable");
    m_bookingsTable->setAlternatingRowColors(true);
    m_bookingsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_bookingsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    QStringList bookingHeaders;
    bookingHeaders << "Customer ID" << "Room ID" << "Check-in" << "Check-out" << "Status" << "Total Cost";
    m_bookingsTable->setColumnCount(bookingHeaders.size());
    m_bookingsTable->setHorizontalHeaderLabels(bookingHeaders);
    m_bookingsTable->horizontalHeader()->setStretchLastSection(true);
    
    bookingsLayout->addWidget(m_bookingsTable);
    
    // Action buttons
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    
    m_cancelBookingBtn = new QPushButton("Cancel Selected Booking");
    m_cancelBookingBtn->setObjectName("dangerButton");
    m_cancelBookingBtn->setEnabled(false);
    
    QPushButton *refreshBookingsBtn = new QPushButton("Refresh Bookings");
    refreshBookingsBtn->setObjectName("actionButton");
    connect(refreshBookingsBtn, &QPushButton::clicked, this, &BookingWidget::populateBookingsList);
    
    actionsLayout->addWidget(m_cancelBookingBtn);
    actionsLayout->addWidget(refreshBookingsBtn);
    actionsLayout->addStretch();
    
    bookingsLayout->addLayout(actionsLayout);
    
    m_mainLayout->addWidget(m_bookingsGroup);
}

void BookingWidget::setupStyles()
{
    setStyleSheet(R"(
        #pageTitle {
            font-size: 22px;
            font-weight: bold;
            color: #2c3e50;
            margin: 10px 0;
        }
        
        #formGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #3498db;
            border-radius: 8px;
            margin: 5px 0;
            padding-top: 10px;
        }
        
        #formGroup::title {
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
            border-radius: 8px;
            margin: 5px 0;
            padding-top: 10px;
        }
        
        #tableGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px 0 10px;
            color: #27ae60;
            font-weight: bold;
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
        
        #dataTable::item:selected {
            background-color: #3498db;
            color: white;
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
        
        #actionButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 2px;
        }
        
        #actionButton:hover {
            background-color: #2980b9;
        }
        
        #dangerButton {
            background-color: #e74c3c;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 2px;
        }
        
        #dangerButton:hover {
            background-color: #c0392b;
        }
        
        #dangerButton:disabled {
            background-color: #bdc3c7;
            color: #7f8c8d;
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
    )");
}

void BookingWidget::connectSignals()
{
    connect(m_bookRoomBtn, &QPushButton::clicked, this, &BookingWidget::onBookRoom);
    connect(m_cancelBookingBtn, &QPushButton::clicked, this, &BookingWidget::onCancelBooking);
    
    // Room selection updates room ID field
    connect(m_roomsTable, &QTableWidget::itemSelectionChanged, this, &BookingWidget::onRoomSelectionChanged);
    
    // Booking selection enables/disables cancel button
    connect(m_bookingsTable, &QTableWidget::itemSelectionChanged, [this]() {
        m_cancelBookingBtn->setEnabled(m_bookingsTable->currentRow() >= 0);
    });
}

void BookingWidget::refreshData()
{
    populateAvailableRooms();
    populateBookingsList();
}

void BookingWidget::populateAvailableRooms()
{
    if (!m_hotelSystem) return;
    
    try {
        m_roomsTable->setRowCount(0);
        
        // This would need hotel methods to get available rooms
        // For now, showing placeholder
        
        // Example implementation when methods are available:
        /*
        std::vector<room*> availableRooms = m_hotelSystem->getHotel().getAllAvailableRooms();
        
        for (size_t i = 0; i < availableRooms.size(); ++i) {
            room* r = availableRooms[i];
            if (!r || !r->isAvailable()) continue;
            
            m_roomsTable->insertRow(i);
            
            m_roomsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(r->getID())));
            m_roomsTable->setItem(i, 1, new QTableWidgetItem(QString::number(r->getFloor())));
            m_roomsTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(r->getTypeName())));
            m_roomsTable->setItem(i, 3, new QTableWidgetItem(QString::number(r->checkPrice(), 'f', 2)));
            m_roomsTable->setItem(i, 4, new QTableWidgetItem("Available"));
        }
        */
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load available rooms: %1").arg(e.what()));
    }
}

void BookingWidget::populateBookingsList()
{
    if (!m_hotelSystem) return;
    
    try {
        m_bookingsTable->setRowCount(0);
        
        if (m_customer && !m_isEmployee) {
            // Show customer's own bookings
            std::vector<current_booking> bookings = m_customer->getCurrentBookings();
            
            for (size_t i = 0; i < bookings.size(); ++i) {
                const current_booking &booking = bookings[i];
                
                m_bookingsTable->insertRow(i);
                
                m_bookingsTable->setItem(i, 0, new QTableWidgetItem(QString::number(m_customer->getID())));
                m_bookingsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(booking.roomID)));
                m_bookingsTable->setItem(i, 2, new QTableWidgetItem(QString("%1/%2/%3")
                    .arg(booking.checkin.day).arg(booking.checkin.month).arg(booking.checkin.year)));
                m_bookingsTable->setItem(i, 3, new QTableWidgetItem(QString("%1/%2/%3")
                    .arg(booking.checkout.day).arg(booking.checkout.month).arg(booking.checkout.year)));
                m_bookingsTable->setItem(i, 4, new QTableWidgetItem("Active"));
                m_bookingsTable->setItem(i, 5, new QTableWidgetItem(QString::number(booking.bill)));
            }
        } else if (m_isEmployee) {
            // Show all current bookings for employees
            std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
            int row = 0;
            
            for (customer* cust : customers) {
                if (!cust) continue;
                
                std::vector<current_booking> bookings = cust->getCurrentBookings();
                for (const current_booking &booking : bookings) {
                    m_bookingsTable->insertRow(row);
                    
                    m_bookingsTable->setItem(row, 0, new QTableWidgetItem(QString::number(cust->getID())));
                    m_bookingsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(booking.roomID)));
                    m_bookingsTable->setItem(row, 2, new QTableWidgetItem(QString("%1/%2/%3")
                        .arg(booking.checkin.day).arg(booking.checkin.month).arg(booking.checkin.year)));
                    m_bookingsTable->setItem(row, 3, new QTableWidgetItem(QString("%1/%2/%3")
                        .arg(booking.checkout.day).arg(booking.checkout.month).arg(booking.checkout.year)));
                    m_bookingsTable->setItem(row, 4, new QTableWidgetItem("Active"));
                    m_bookingsTable->setItem(row, 5, new QTableWidgetItem(QString::number(booking.bill)));
                    
                    row++;
                }
            }
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load bookings: %1").arg(e.what()));
    }
}

void BookingWidget::onBookRoom()
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
    
    customer *targetCustomer = m_customer;
    
    // If employee, get customer by ID
    if (m_isEmployee) {
        int customerId = m_customerIdEdit->text().toInt();
        if (customerId <= 0) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid customer ID.");
            return;
        }
        
        targetCustomer = m_hotelSystem->findCustomer(customerId);
        if (!targetCustomer) {
            QMessageBox::warning(this, "Error", "Customer not found.");
            return;
        }
    }
    
    if (!targetCustomer) {
        QMessageBox::warning(this, "Error", "No customer selected for booking.");
        return;
    }
    
    try {
        date checkin = {checkinDate.day(), checkinDate.month(), checkinDate.year()};
        date checkout = {checkoutDate.day(), checkoutDate.month(), checkoutDate.year()};
        
        if (targetCustomer->bookRoom(m_hotelSystem->getHotel(), roomId.toStdString(), checkin, checkout)) {
            QMessageBox::information(this, "Success", "Room booked successfully!");
            
            // Clear form
            m_roomIdEdit->clear();
            if (m_isEmployee) {
                m_customerIdEdit->clear();
            }
            m_checkinDateEdit->setDate(QDate::currentDate());
            m_checkoutDateEdit->setDate(QDate::currentDate().addDays(1));
            
            refreshData();
        } else {
            QMessageBox::warning(this, "Booking Failed", "Failed to book the room. It may not be available for the selected dates.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to book room: %1").arg(e.what()));
    }
}

void BookingWidget::onCancelBooking()
{
    int currentRow = m_bookingsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a booking to cancel.");
        return;
    }
    
    QString roomId = m_bookingsTable->item(currentRow, 1)->text();
    int customerId = m_bookingsTable->item(currentRow, 0)->text().toInt();
    
    int reply = QMessageBox::question(this, "Cancel Booking", 
                                      QString("Are you sure you want to cancel the booking for room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            customer *targetCustomer = m_customer;
            
            // If employee or different customer, find the customer
            if (m_isEmployee || !targetCustomer || targetCustomer->getID() != customerId) {
                targetCustomer = m_hotelSystem->findCustomer(customerId);
            }
            
            if (targetCustomer && targetCustomer->cancelRoom(roomId.toStdString())) {
                QMessageBox::information(this, "Success", "Booking cancelled successfully!");
                refreshData();
            } else {
                QMessageBox::warning(this, "Cancel Failed", "Failed to cancel the booking.");
            }
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to cancel booking: %1").arg(e.what()));
        }
    }
}

void BookingWidget::onRoomSelectionChanged()
{
    int currentRow = m_roomsTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem *roomIdItem = m_roomsTable->item(currentRow, 0);
        if (roomIdItem) {
            m_roomIdEdit->setText(roomIdItem->text());
        }
    }
}

