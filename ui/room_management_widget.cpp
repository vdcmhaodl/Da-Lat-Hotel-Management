#include "room_management_widget.h"

RoomManagementWidget::RoomManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QWidget(parent)
    , m_hotelSystem(hotelSystem)
{
    setupUI();
    setupStyles();
    connectSignals();
    refreshData();
}

void RoomManagementWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(15);
    
    // Title
    QLabel *titleLabel = new QLabel("Room Management");
    titleLabel->setObjectName("pageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Search and filter section
    setupSearchAndFilter();
    
    // Room table section
    setupRoomTable();
    
    // Controls section
    setupControls();
    
    // Add room section
    setupAddRoomSection();
}

void RoomManagementWidget::setupRoomTable()
{
    QGroupBox *tableGroup = new QGroupBox("Rooms Overview");
    tableGroup->setObjectName("tableGroup");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    
    // Room count label
    m_roomCountLabel = new QLabel("Total Rooms: 0");
    m_roomCountLabel->setObjectName("countLabel");
    tableLayout->addWidget(m_roomCountLabel);
    
    // Room table
    m_roomTable = new QTableWidget();
    m_roomTable->setObjectName("dataTable");
    m_roomTable->setAlternatingRowColors(true);
    m_roomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_roomTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_roomTable->setSortingEnabled(true);
    
    // Set table headers
    QStringList headers;
    headers << "Room ID" << "Floor" << "Type" << "Price/Night" << "Status" 
            << "Current Guest" << "Available";
    m_roomTable->setColumnCount(headers.size());
    m_roomTable->setHorizontalHeaderLabels(headers);
    
    // Configure table
    m_roomTable->horizontalHeader()->setStretchLastSection(true);
    m_roomTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_roomTable->verticalHeader()->setVisible(false);
    
    tableLayout->addWidget(m_roomTable);
    m_mainLayout->addWidget(tableGroup);
}

void RoomManagementWidget::setupSearchAndFilter()
{
    m_searchGroup = new QGroupBox("Search & Filter");
    m_searchGroup->setObjectName("controlGroup");
    QHBoxLayout *searchLayout = new QHBoxLayout(m_searchGroup);
    
    // Search by room ID
    QLabel *searchLabel = new QLabel("Search Room:");
    m_searchLineEdit = new QLineEdit();
    m_searchLineEdit->setPlaceholderText("Enter Room ID...");
    m_searchLineEdit->setObjectName("searchInput");
    
    m_searchBtn = new QPushButton("Search");
    m_searchBtn->setObjectName("actionButton");
    
    // Filter by status
    QLabel *filterLabel = new QLabel("Filter:");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItem("All Rooms", "all");
    m_filterCombo->addItem("Available", "available");
    m_filterCombo->addItem("Occupied", "occupied");
    m_filterCombo->addItem("Maintenance", "maintenance");
    m_filterCombo->setObjectName("filterCombo");
    
    m_clearFilterBtn = new QPushButton("Clear Filter");
    m_clearFilterBtn->setObjectName("secondaryButton");
    
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(m_searchLineEdit);
    searchLayout->addWidget(m_searchBtn);
    searchLayout->addWidget(filterLabel);
    searchLayout->addWidget(m_filterCombo);
    searchLayout->addWidget(m_clearFilterBtn);
    searchLayout->addStretch();
    
    m_mainLayout->addWidget(m_searchGroup);
}

void RoomManagementWidget::setupControls()
{
    m_controlsGroup = new QGroupBox("Room Actions");
    m_controlsGroup->setObjectName("controlGroup");
    QHBoxLayout *controlsLayout = new QHBoxLayout(m_controlsGroup);
    
    m_addRoomBtn = new QPushButton("Add New Room");
    m_addRoomBtn->setObjectName("primaryButton");
    
    m_removeRoomBtn = new QPushButton("Remove Room");
    m_removeRoomBtn->setObjectName("dangerButton");
    m_removeRoomBtn->setEnabled(false);
    
    m_viewDetailsBtn = new QPushButton("View Details");
    m_viewDetailsBtn->setObjectName("actionButton");
    m_viewDetailsBtn->setEnabled(false);
    
    m_refreshBtn = new QPushButton("Refresh");
    m_refreshBtn->setObjectName("actionButton");
    
    controlsLayout->addWidget(m_addRoomBtn);
    controlsLayout->addWidget(m_removeRoomBtn);
    controlsLayout->addWidget(m_viewDetailsBtn);
    controlsLayout->addWidget(m_refreshBtn);
    controlsLayout->addStretch();
    
    m_mainLayout->addWidget(m_controlsGroup);
}

void RoomManagementWidget::setupAddRoomSection()
{
    m_addRoomGroup = new QGroupBox("Add New Room");
    m_addRoomGroup->setObjectName("controlGroup");
    m_addRoomGroup->setVisible(false); // Initially hidden
    
    QGridLayout *addRoomLayout = new QGridLayout(m_addRoomGroup);
    
    // Floor selection
    QLabel *floorLabel = new QLabel("Floor:");
    m_floorSpinBox = new QSpinBox();
    m_floorSpinBox->setMinimum(1);
    m_floorSpinBox->setMaximum(20);
    m_floorSpinBox->setValue(1);
    m_floorSpinBox->setObjectName("spinBox");
    
    // Room type selection
    QLabel *typeLabel = new QLabel("Room Type:");
    m_roomTypeCombo = new QComboBox();
    m_roomTypeCombo->addItem("Standard Single (Type 1)", 1);
    m_roomTypeCombo->addItem("Standard Double (Type 2)", 2);
    m_roomTypeCombo->addItem("Deluxe Single (Type 3)", 3);
    m_roomTypeCombo->addItem("Deluxe Double (Type 4)", 4);
    m_roomTypeCombo->addItem("Suite (Type 5)", 5);
    m_roomTypeCombo->addItem("Presidential Suite (Type 6)", 6);
    m_roomTypeCombo->addItem("Family Room (Type 7)", 7);
    m_roomTypeCombo->addItem("Executive Room (Type 8)", 8);
    m_roomTypeCombo->setObjectName("comboBox");
    
    // Confirm button
    m_confirmAddBtn = new QPushButton("Confirm Add Room");
    m_confirmAddBtn->setObjectName("primaryButton");
    
    QPushButton *cancelAddBtn = new QPushButton("Cancel");
    cancelAddBtn->setObjectName("secondaryButton");
    
    addRoomLayout->addWidget(floorLabel, 0, 0);
    addRoomLayout->addWidget(m_floorSpinBox, 0, 1);
    addRoomLayout->addWidget(typeLabel, 1, 0);
    addRoomLayout->addWidget(m_roomTypeCombo, 1, 1);
    addRoomLayout->addWidget(m_confirmAddBtn, 2, 0);
    addRoomLayout->addWidget(cancelAddBtn, 2, 1);
    
    // Connect cancel button
    connect(cancelAddBtn, &QPushButton::clicked, [this]() {
        m_addRoomGroup->setVisible(false);
    });
    
    m_mainLayout->addWidget(m_addRoomGroup);
}

void RoomManagementWidget::setupStyles()
{
    setStyleSheet(R"(
        #pageTitle {
            font-size: 22px;
            font-weight: bold;
            color: #2c3e50;
            margin: 10px 0;
        }
        
        #controlGroup {
            font-size: 14px;
            font-weight: bold;
            color: #2c3e50;
            border: 2px solid #3498db;
            border-radius: 8px;
            margin: 5px 0;
            padding-top: 10px;
        }
        
        #controlGroup::title {
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
        
        #countLabel {
            font-size: 16px;
            font-weight: bold;
            color: #27ae60;
            margin: 5px 0;
        }
        
        #primaryButton {
            background-color: #27ae60;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 2px;
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
        
        #actionButton:disabled {
            background-color: #bdc3c7;
            color: #7f8c8d;
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
        
        #secondaryButton {
            background-color: #95a5a6;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 2px;
        }
        
        #secondaryButton:hover {
            background-color: #7f8c8d;
        }
        
        #searchInput, #spinBox, #comboBox, #filterCombo {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            background-color: white;
        }
        
        #searchInput:focus, #spinBox:focus, #comboBox:focus, #filterCombo:focus {
            border-color: #3498db;
        }
    )");
}

void RoomManagementWidget::connectSignals()
{
    connect(m_addRoomBtn, &QPushButton::clicked, this, &RoomManagementWidget::onAddRoom);
    connect(m_removeRoomBtn, &QPushButton::clicked, this, &RoomManagementWidget::onRemoveRoom);
    connect(m_viewDetailsBtn, &QPushButton::clicked, this, &RoomManagementWidget::onViewRoomDetails);
    connect(m_refreshBtn, &QPushButton::clicked, this, &RoomManagementWidget::refreshData);
    
    connect(m_searchBtn, &QPushButton::clicked, this, &RoomManagementWidget::onSearchRoom);
    connect(m_clearFilterBtn, &QPushButton::clicked, this, &RoomManagementWidget::onFilterRooms);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &RoomManagementWidget::onFilterRooms);
    
    connect(m_confirmAddBtn, &QPushButton::clicked, [this]() {
        int floor = m_floorSpinBox->value();
        int type = m_roomTypeCombo->currentData().toInt();
        
        try {
            m_hotelSystem->addRoom(floor, type);
            QMessageBox::information(this, "Success", "Room added successfully!");
            m_addRoomGroup->setVisible(false);
            refreshData();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to add room: %1").arg(e.what()));
        }
    });
    
    connect(m_roomTable, &QTableWidget::itemSelectionChanged, 
            this, &RoomManagementWidget::onRoomSelectionChanged);
}

void RoomManagementWidget::populateRoomTable()
{
    if (!m_hotelSystem) return;
    
    try {
        // Clear existing data
        m_roomTable->setRowCount(0);
        
        // Get hotel reference
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
                
                // Set room data in table
                m_roomTable->setItem(rowIndex, 0, new QTableWidgetItem(QString::fromStdString(r.getID())));
                m_roomTable->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(floorIndex + 1)));
                m_roomTable->setItem(rowIndex, 2, new QTableWidgetItem(QString::fromStdString(r.getTypeName())));
                m_roomTable->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(r.checkPrice(), 'f', 0) + " VND"));
                m_roomTable->setItem(rowIndex, 4, new QTableWidgetItem(r.isAvailable() ? "Available" : "Occupied"));
                m_roomTable->setItem(rowIndex, 5, new QTableWidgetItem("N/A")); // getCurrentGuest() is not available
                m_roomTable->setItem(rowIndex, 6, new QTableWidgetItem(r.isAvailable() ? "Yes" : "No"));
                
                totalRooms++;
                rowIndex++;
            }
        }
        
        m_roomCountLabel->setText(QString("Total Rooms: %1").arg(totalRooms));
        
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
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load room data: %1").arg(e.what()));
        m_roomCountLabel->setText("Total Rooms: Error loading data");
    }
}

void RoomManagementWidget::refreshData()
{
    populateRoomTable();
}

void RoomManagementWidget::onAddRoom()
{
    m_addRoomGroup->setVisible(true);
}

void RoomManagementWidget::onRemoveRoom()
{
    int currentRow = m_roomTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a room to remove.");
        return;
    }
    
    QString roomId = m_roomTable->item(currentRow, 0)->text();
    QString floorText = m_roomTable->item(currentRow, 1)->text();
    
    int reply = QMessageBox::question(this, "Confirm Removal", 
                                      QString("Are you sure you want to remove room %1?").arg(roomId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            // Parse floor number from the table
            int floorNumber = floorText.toInt();
            if (floorNumber > 0) {
                // Use hotel API directly since HotelManagementSystem::removeRoom() needs console input
                hotel& h = m_hotelSystem->getHotel();
                h.removeRoom(floorNumber - 1, roomId.toStdString());  // Floor is 0-indexed in hotel class
                QMessageBox::information(this, "Success", "Room removed successfully!");
                refreshData();
            } else {
                QMessageBox::warning(this, "Error", "Invalid floor number. Cannot remove room.");
            }
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to remove room: %1").arg(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "Error", "An unknown error occurred while removing the room.");
        }
    }
}

void RoomManagementWidget::onViewRoomDetails()
{
    int currentRow = m_roomTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a room to view details.");
        return;
    }
    
    QString roomId = m_roomTable->item(currentRow, 0)->text();
    
    try {
        // Capture room details output
        std::ostringstream detailsStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(detailsStream.rdbuf());
        
        m_hotelSystem->showRoomByID(roomId.toStdString());
        
        std::cout.rdbuf(orig);
        
        QString details = QString::fromStdString(detailsStream.str());
        if (details.isEmpty()) {
            details = "Room details not available.";
        }
        
        QMessageBox::information(this, QString("Room %1 Details").arg(roomId), details);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to get room details: %1").arg(e.what()));
    }
}

void RoomManagementWidget::onSearchRoom()
{
    QString searchText = m_searchLineEdit->text().trimmed();
    if (searchText.isEmpty()) {
        refreshData();
        return;
    }
    
    // Filter table rows based on search text
    for (int row = 0; row < m_roomTable->rowCount(); ++row) {
        bool found = false;
        for (int col = 0; col < m_roomTable->columnCount(); ++col) {
            QTableWidgetItem *item = m_roomTable->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                found = true;
                break;
            }
        }
        m_roomTable->setRowHidden(row, !found);
    }
}

void RoomManagementWidget::onFilterRooms()
{
    QString filter = m_filterCombo->currentData().toString();
    
    if (filter == "all") {
        // Show all rows
        for (int row = 0; row < m_roomTable->rowCount(); ++row) {
            m_roomTable->setRowHidden(row, false);
        }
    } else {
        // Filter based on status
        for (int row = 0; row < m_roomTable->rowCount(); ++row) {
            QTableWidgetItem *statusItem = m_roomTable->item(row, 4); // Status column
            if (statusItem) {
                QString status = statusItem->text().toLower();
                bool show = false;
                
                if (filter == "available" && status.contains("available")) {
                    show = true;
                } else if (filter == "occupied" && status.contains("occupied")) {
                    show = true;
                } else if (filter == "maintenance" && status.contains("maintenance")) {
                    show = true;
                }
                
                m_roomTable->setRowHidden(row, !show);
            }
        }
    }
    
    // Clear search if filtering
    if (filter != "all") {
        m_searchLineEdit->clear();
    }
}

void RoomManagementWidget::onRoomSelectionChanged()
{
    bool hasSelection = m_roomTable->currentRow() >= 0;
    m_removeRoomBtn->setEnabled(hasSelection);
    m_viewDetailsBtn->setEnabled(hasSelection);
}

#include "room_management_widget.moc"
