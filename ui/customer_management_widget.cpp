#include "customer_management_widget.h"
#include "add_customer_dialog.h"

CustomerManagementWidget::CustomerManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QWidget(parent)
    , m_hotelSystem(hotelSystem)
{
    setupUI();
    setupStyles();
    connectSignals();
    refreshData();
}

void CustomerManagementWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(15);
    
    // Title
    QLabel *titleLabel = new QLabel("Customer Management");
    titleLabel->setObjectName("pageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Search and filter section
    setupSearchAndFilter();
    
    // Customer table section
    setupCustomerTable();
    
    // Controls section
    setupControls();
}

void CustomerManagementWidget::setupCustomerTable()
{
    QGroupBox *tableGroup = new QGroupBox("Customers Overview");
    tableGroup->setObjectName("tableGroup");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    
    // Customer count label
    m_customerCountLabel = new QLabel("Total Customers: 0");
    m_customerCountLabel->setObjectName("countLabel");
    tableLayout->addWidget(m_customerCountLabel);
    
    // Customer table
    m_customerTable = new QTableWidget();
    m_customerTable->setObjectName("dataTable");
    m_customerTable->setAlternatingRowColors(true);
    m_customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_customerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_customerTable->setSortingEnabled(true);
    
    // Set table headers
    QStringList headers;
    headers << "Customer ID" << "Name" << "Phone" << "Email" << "Gender" 
            << "Discount %" << "Total Bookings" << "Status";
    m_customerTable->setColumnCount(headers.size());
    m_customerTable->setHorizontalHeaderLabels(headers);
    
    // Configure table
    m_customerTable->horizontalHeader()->setStretchLastSection(true);
    m_customerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_customerTable->verticalHeader()->setVisible(false);
    
    tableLayout->addWidget(m_customerTable);
    m_mainLayout->addWidget(tableGroup);
}

void CustomerManagementWidget::setupSearchAndFilter()
{
    m_searchGroup = new QGroupBox("Search & Filter");
    m_searchGroup->setObjectName("controlGroup");
    QHBoxLayout *searchLayout = new QHBoxLayout(m_searchGroup);
    
    // Search by customer name or ID
    QLabel *searchLabel = new QLabel("Search Customer:");
    m_searchLineEdit = new QLineEdit();
    m_searchLineEdit->setPlaceholderText("Enter name or ID...");
    m_searchLineEdit->setObjectName("searchInput");
    
    m_searchBtn = new QPushButton("Search");
    m_searchBtn->setObjectName("actionButton");
    
    // Filter by status
    QLabel *filterLabel = new QLabel("Filter:");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItem("All Customers", "all");
    m_filterCombo->addItem("Active Bookings", "active");
    m_filterCombo->addItem("No Bookings", "inactive");
    m_filterCombo->addItem("With Discount", "discount");
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

void CustomerManagementWidget::setupControls()
{
    m_controlsGroup = new QGroupBox("Customer Actions");
    m_controlsGroup->setObjectName("controlGroup");
    QHBoxLayout *controlsLayout = new QHBoxLayout(m_controlsGroup);
    
    m_addCustomerBtn = new QPushButton("Add New Customer");
    m_addCustomerBtn->setObjectName("primaryButton");
    
    m_removeCustomerBtn = new QPushButton("Remove Customer");
    m_removeCustomerBtn->setObjectName("dangerButton");
    m_removeCustomerBtn->setEnabled(false);
    
    m_viewDetailsBtn = new QPushButton("View Details");
    m_viewDetailsBtn->setObjectName("actionButton");
    m_viewDetailsBtn->setEnabled(false);
    
    m_viewHistoryBtn = new QPushButton("Booking History");
    m_viewHistoryBtn->setObjectName("actionButton");
    m_viewHistoryBtn->setEnabled(false);
    
    m_giveDiscountBtn = new QPushButton("Give Discount");
    m_giveDiscountBtn->setObjectName("warningButton");
    m_giveDiscountBtn->setEnabled(false);
    
    m_refreshBtn = new QPushButton("Refresh");
    m_refreshBtn->setObjectName("actionButton");
    
    controlsLayout->addWidget(m_addCustomerBtn);
    controlsLayout->addWidget(m_removeCustomerBtn);
    controlsLayout->addWidget(m_viewDetailsBtn);
    controlsLayout->addWidget(m_viewHistoryBtn);
    controlsLayout->addWidget(m_giveDiscountBtn);
    controlsLayout->addWidget(m_refreshBtn);
    controlsLayout->addStretch();
    
    m_mainLayout->addWidget(m_controlsGroup);
}

void CustomerManagementWidget::setupStyles()
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
        
        #warningButton {
            background-color: #f39c12;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 5px;
            font-size: 14px;
            font-weight: bold;
            margin: 2px;
        }
        
        #warningButton:hover {
            background-color: #e67e22;
        }
        
        #warningButton:disabled {
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
        
        #searchInput, #filterCombo {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            background-color: white;
        }
        
        #searchInput:focus, #filterCombo:focus {
            border-color: #3498db;
        }
    )");
}

void CustomerManagementWidget::connectSignals()
{
    connect(m_addCustomerBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onAddCustomer);
    connect(m_removeCustomerBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onRemoveCustomer);
    connect(m_viewDetailsBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onViewCustomerDetails);
    connect(m_viewHistoryBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onViewBookingHistory);
    connect(m_giveDiscountBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onGiveDiscount);
    connect(m_refreshBtn, &QPushButton::clicked, this, &CustomerManagementWidget::refreshData);
    
    connect(m_searchBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onSearchCustomer);
    connect(m_clearFilterBtn, &QPushButton::clicked, this, &CustomerManagementWidget::onFilterCustomers);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CustomerManagementWidget::onFilterCustomers);
    
    connect(m_customerTable, &QTableWidget::itemSelectionChanged, 
            this, &CustomerManagementWidget::onCustomerSelectionChanged);
}

void CustomerManagementWidget::populateCustomerTable()
{
    if (!m_hotelSystem) return;
    
    try {
        // Clear existing data
        m_customerTable->setRowCount(0);
        
        // Get all customers
        std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
        
        for (size_t i = 0; i < customers.size(); ++i) {
            customer* cust = customers[i];
            if (!cust) continue;
            
            m_customerTable->insertRow(i);
            
            // Customer ID
            m_customerTable->setItem(i, 0, new QTableWidgetItem(QString::number(cust->getID())));
            
            // Name
            m_customerTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cust->getName())));
            
            // Phone
            m_customerTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cust->getPhone())));
            
            // Email
            m_customerTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(cust->getEmail())));
            
            // Gender
            m_customerTable->setItem(i, 4, new QTableWidgetItem(cust->getGender() ? "Male" : "Female"));
            
            // Discount
            m_customerTable->setItem(i, 5, new QTableWidgetItem(QString::number(cust->getDiscount())));
            
            // Total bookings
            std::vector<booking_record> history = cust->getBookingHistory();
            m_customerTable->setItem(i, 6, new QTableWidgetItem(QString::number(history.size())));
            
            // Status (active if has current bookings)
            std::vector<current_booking> currentBookings = cust->getCurrentBookings();
            QString status = currentBookings.empty() ? "Inactive" : "Active";
            m_customerTable->setItem(i, 7, new QTableWidgetItem(status));
        }
        
        m_customerCountLabel->setText(QString("Total Customers: %1").arg(customers.size()));
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load customer data: %1").arg(e.what()));
    }
}

void CustomerManagementWidget::refreshData()
{
    populateCustomerTable();
}

void CustomerManagementWidget::onAddCustomer()
{
    try {
        // Use the AddCustomerDialog
        AddCustomerDialog dialog(m_hotelSystem, this);
        connect(&dialog, &AddCustomerDialog::customerAdded, this, &CustomerManagementWidget::refreshData);
        if (dialog.exec() == QDialog::Accepted) {
            refreshData();
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to add customer: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "An unknown error occurred while adding customer.");
    }
}

void CustomerManagementWidget::onRemoveCustomer()
{
    int currentRow = m_customerTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a customer to remove.");
        return;
    }
    
    int customerId = m_customerTable->item(currentRow, 0)->text().toInt();
    QString customerName = m_customerTable->item(currentRow, 1)->text();
    
    int reply = QMessageBox::question(this, "Confirm Removal", 
                                      QString("Are you sure you want to remove customer %1 (%2)?")
                                      .arg(customerName).arg(customerId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            m_hotelSystem->removeCustomer(customerId);
            QMessageBox::information(this, "Success", "Customer removed successfully!");
            refreshData();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to remove customer: %1").arg(e.what()));
        }
    }
}

void CustomerManagementWidget::onViewCustomerDetails()
{
    int currentRow = m_customerTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a customer to view details.");
        return;
    }
    
    int customerId = m_customerTable->item(currentRow, 0)->text().toInt();
    
    try {
        customer *cust = m_hotelSystem->getCustomerById(customerId);
        if (cust) {
            // Capture customer details output
            std::ostringstream detailsStream;
            std::streambuf* orig = std::cout.rdbuf();
            std::cout.rdbuf(detailsStream.rdbuf());
            
            cust->showInfo();
            
            std::cout.rdbuf(orig);
            
            QString details = QString::fromStdString(detailsStream.str());
            if (details.isEmpty()) {
                details = QString("Customer ID: %1\nName: %2\nPhone: %3\nEmail: %4\nGender: %5\nDiscount: %6%\nTotal Bill: $%7")
                    .arg(cust->getID())
                    .arg(QString::fromStdString(cust->getName()))
                    .arg(QString::fromStdString(cust->getPhone()))
                    .arg(QString::fromStdString(cust->getEmail()))
                    .arg(cust->getGender() ? "Male" : "Female")
                    .arg(cust->getDiscount())
                    .arg(cust->getTotalBill());
            }
            
            QMessageBox::information(this, QString("Customer %1 Details").arg(customerId), details);
        } else {
            QMessageBox::warning(this, "Error", "Customer not found.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to get customer details: %1").arg(e.what()));
    }
}

void CustomerManagementWidget::onViewBookingHistory()
{
    int currentRow = m_customerTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a customer to view booking history.");
        return;
    }
    
    int customerId = m_customerTable->item(currentRow, 0)->text().toInt();
    
    try {
        // Capture booking history output
        std::ostringstream historyStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(historyStream.rdbuf());
        
        m_hotelSystem->viewCustomerBookingHistory(customerId);
        
        std::cout.rdbuf(orig);
        
        QString history = QString::fromStdString(historyStream.str());
        if (history.isEmpty()) {
            history = "No booking history available for this customer.";
        }
        
        // Create a dialog to show booking history
        QDialog *historyDialog = new QDialog(this);
        historyDialog->setWindowTitle(QString("Booking History - Customer %1").arg(customerId));
        historyDialog->resize(600, 400);
        
        QVBoxLayout *layout = new QVBoxLayout(historyDialog);
        QTextEdit *textEdit = new QTextEdit();
        textEdit->setPlainText(history);
        textEdit->setReadOnly(true);
        textEdit->setFont(QFont("Courier New", 10));
        
        QPushButton *closeBtn = new QPushButton("Close");
        connect(closeBtn, &QPushButton::clicked, historyDialog, &QDialog::accept);
        
        layout->addWidget(textEdit);
        layout->addWidget(closeBtn);
        
        historyDialog->exec();
        delete historyDialog;
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to get booking history: %1").arg(e.what()));
    }
}

void CustomerManagementWidget::onGiveDiscount()
{
    int currentRow = m_customerTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a customer to give discount.");
        return;
    }
    
    int customerId = m_customerTable->item(currentRow, 0)->text().toInt();
    QString customerName = m_customerTable->item(currentRow, 1)->text();
    
    bool ok;
    int discount = QInputDialog::getInt(this, "Give Discount", 
                                       QString("Enter discount percentage for %1:").arg(customerName),
                                       0, 0, 50, 1, &ok);
    
    if (ok) {
        try {
            m_hotelSystem->giveDiscountToCustomer(customerId, discount);
            QMessageBox::information(this, "Success", 
                QString("Discount of %1% given to customer %2 successfully!").arg(discount).arg(customerName));
            refreshData();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to give discount: %1").arg(e.what()));
        }
    }
}

void CustomerManagementWidget::onSearchCustomer()
{
    QString searchText = m_searchLineEdit->text().trimmed();
    if (searchText.isEmpty()) {
        refreshData();
        return;
    }
    
    // Filter table rows based on search text
    for (int row = 0; row < m_customerTable->rowCount(); ++row) {
        bool found = false;
        for (int col = 0; col < m_customerTable->columnCount(); ++col) {
            QTableWidgetItem *item = m_customerTable->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                found = true;
                break;
            }
        }
        m_customerTable->setRowHidden(row, !found);
    }
}

void CustomerManagementWidget::onFilterCustomers()
{
    QString filter = m_filterCombo->currentData().toString();
    
    if (filter == "all") {
        // Show all rows
        for (int row = 0; row < m_customerTable->rowCount(); ++row) {
            m_customerTable->setRowHidden(row, false);
        }
    } else {
        // Filter based on criteria
        for (int row = 0; row < m_customerTable->rowCount(); ++row) {
            bool show = false;
            
            if (filter == "active") {
                QTableWidgetItem *statusItem = m_customerTable->item(row, 7); // Status column
                if (statusItem && statusItem->text().toLower().contains("active")) {
                    show = true;
                }
            } else if (filter == "inactive") {
                QTableWidgetItem *statusItem = m_customerTable->item(row, 7); // Status column
                if (statusItem && statusItem->text().toLower().contains("inactive")) {
                    show = true;
                }
            } else if (filter == "discount") {
                QTableWidgetItem *discountItem = m_customerTable->item(row, 5); // Discount column
                if (discountItem && discountItem->text().toInt() > 0) {
                    show = true;
                }
            }
            
            m_customerTable->setRowHidden(row, !show);
        }
    }
    
    // Clear search if filtering
    if (filter != "all") {
        m_searchLineEdit->clear();
    }
}

void CustomerManagementWidget::onCustomerSelectionChanged()
{
    bool hasSelection = m_customerTable->currentRow() >= 0;
    m_removeCustomerBtn->setEnabled(hasSelection);
    m_viewDetailsBtn->setEnabled(hasSelection);
    m_viewHistoryBtn->setEnabled(hasSelection);
    m_giveDiscountBtn->setEnabled(hasSelection);
}

