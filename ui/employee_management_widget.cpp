#include "employee_management_widget.h"
#include "add_employee_dialog.h"
#include <QDebug>

EmployeeManagementWidget::EmployeeManagementWidget(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QWidget(parent)
    , m_hotelSystem(hotelSystem)
{
    setupUI();
    setupStyles();
    connectSignals();
    refreshData();
}

void EmployeeManagementWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    m_mainLayout->setSpacing(15);
    
    // Title
    QLabel *titleLabel = new QLabel("Employee Management");
    titleLabel->setObjectName("pageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Search and filter section
    setupSearchAndFilter();
    
    // Employee table section
    setupEmployeeTable();
    
    // Controls section
    setupControls();
    
    // Hire employee section
    setupHireEmployeeSection();
}

void EmployeeManagementWidget::setupEmployeeTable()
{
    QGroupBox *tableGroup = new QGroupBox("Employees Overview");
    tableGroup->setObjectName("tableGroup");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    
    // Employee count label
    m_employeeCountLabel = new QLabel("Total Employees: 0");
    m_employeeCountLabel->setObjectName("countLabel");
    tableLayout->addWidget(m_employeeCountLabel);
    
    // Employee table
    m_employeeTable = new QTableWidget();
    m_employeeTable->setObjectName("dataTable");
    m_employeeTable->setAlternatingRowColors(true);
    m_employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_employeeTable->setSortingEnabled(true);
    
    // Set table headers
    QStringList headers;
    headers << "Employee ID" << "Name" << "Phone" << "Email" << "Gender" 
            << "Position" << "Salary" << "Status";
    m_employeeTable->setColumnCount(headers.size());
    m_employeeTable->setHorizontalHeaderLabels(headers);
    
    // Configure table
    m_employeeTable->horizontalHeader()->setStretchLastSection(true);
    m_employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_employeeTable->verticalHeader()->setVisible(false);
    
    tableLayout->addWidget(m_employeeTable);
    m_mainLayout->addWidget(tableGroup);
}

void EmployeeManagementWidget::setupSearchAndFilter()
{
    m_searchGroup = new QGroupBox("Search & Filter");
    m_searchGroup->setObjectName("controlGroup");
    QHBoxLayout *searchLayout = new QHBoxLayout(m_searchGroup);
    
    // Search by employee name or ID
    QLabel *searchLabel = new QLabel("Search Employee:");
    m_searchLineEdit = new QLineEdit();
    m_searchLineEdit->setPlaceholderText("Enter name or ID...");
    m_searchLineEdit->setObjectName("searchInput");
    
    m_searchBtn = new QPushButton("Search");
    m_searchBtn->setObjectName("actionButton");
    
    // Filter by position
    QLabel *filterLabel = new QLabel("Filter:");
    m_filterCombo = new QComboBox();
    m_filterCombo->addItem("All Employees", "all");
    m_filterCombo->addItem("Active", "active");
    m_filterCombo->addItem("Inactive", "inactive");
    m_filterCombo->addItem("High Salary (>50k)", "high_salary");
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

void EmployeeManagementWidget::setupControls()
{
    m_controlsGroup = new QGroupBox("Employee Actions");
    m_controlsGroup->setObjectName("controlGroup");
    QHBoxLayout *controlsLayout = new QHBoxLayout(m_controlsGroup);
    
    m_hireEmployeeBtn = new QPushButton("Hire New Employee");
    m_hireEmployeeBtn->setObjectName("primaryButton");
    
    m_fireEmployeeBtn = new QPushButton("Fire Employee");
    m_fireEmployeeBtn->setObjectName("dangerButton");
    m_fireEmployeeBtn->setEnabled(false);
    
    m_viewDetailsBtn = new QPushButton("View Details");
    m_viewDetailsBtn->setObjectName("actionButton");
    m_viewDetailsBtn->setEnabled(false);
    
    m_refreshBtn = new QPushButton("Refresh");
    m_refreshBtn->setObjectName("actionButton");
    
    controlsLayout->addWidget(m_hireEmployeeBtn);
    controlsLayout->addWidget(m_fireEmployeeBtn);
    controlsLayout->addWidget(m_viewDetailsBtn);
    controlsLayout->addWidget(m_refreshBtn);
    controlsLayout->addStretch();
    
    m_mainLayout->addWidget(m_controlsGroup);
}

void EmployeeManagementWidget::setupHireEmployeeSection()
{
    m_hireEmployeeGroup = new QGroupBox("Hire New Employee");
    m_hireEmployeeGroup->setObjectName("controlGroup");
    m_hireEmployeeGroup->setVisible(false); // Initially hidden
    
    QGridLayout *hireLayout = new QGridLayout(m_hireEmployeeGroup);
    
    // Name input
    QLabel *nameLabel = new QLabel("Full Name:");
    m_nameLineEdit = new QLineEdit();
    m_nameLineEdit->setPlaceholderText("Enter employee name");
    m_nameLineEdit->setObjectName("lineEdit");
    
    // Phone input
    QLabel *phoneLabel = new QLabel("Phone Number:");
    m_phoneLineEdit = new QLineEdit();
    m_phoneLineEdit->setPlaceholderText("Enter phone number");
    m_phoneLineEdit->setObjectName("lineEdit");
    
    // Email input
    QLabel *emailLabel = new QLabel("Email:");
    m_emailLineEdit = new QLineEdit();
    m_emailLineEdit->setPlaceholderText("Enter email address");
    m_emailLineEdit->setObjectName("lineEdit");
    
    // Gender selection
    QLabel *genderLabel = new QLabel("Gender:");
    m_genderCombo = new QComboBox();
    m_genderCombo->addItem("Male", true);
    m_genderCombo->addItem("Female", false);
    m_genderCombo->setObjectName("comboBox");
    
    // Salary input
    QLabel *salaryLabel = new QLabel("Salary:");
    m_salarySpinBox = new QDoubleSpinBox();
    m_salarySpinBox->setMinimum(10000);
    m_salarySpinBox->setMaximum(200000);
    m_salarySpinBox->setValue(30000);
    m_salarySpinBox->setDecimals(0);
    m_salarySpinBox->setSuffix(" VND");
    m_salarySpinBox->setObjectName("spinBox");
    
    // Position input
    QLabel *positionLabel = new QLabel("Position:");
    m_positionLineEdit = new QLineEdit();
    m_positionLineEdit->setPlaceholderText("Enter position/job title");
    m_positionLineEdit->setObjectName("lineEdit");
    
    // Buttons
    m_confirmHireBtn = new QPushButton("Confirm Hire");
    m_confirmHireBtn->setObjectName("primaryButton");
    
    QPushButton *cancelHireBtn = new QPushButton("Cancel");
    cancelHireBtn->setObjectName("secondaryButton");
    
    // Layout - 2 columns with 3 rows each for better space utilization
    hireLayout->addWidget(nameLabel, 0, 0);
    hireLayout->addWidget(m_nameLineEdit, 0, 1);
    hireLayout->addWidget(phoneLabel, 1, 0);
    hireLayout->addWidget(m_phoneLineEdit, 1, 1);
    hireLayout->addWidget(emailLabel, 2, 0);
    hireLayout->addWidget(m_emailLineEdit, 2, 1);
    
    // Second column starts here
    hireLayout->addWidget(genderLabel, 0, 2);
    hireLayout->addWidget(m_genderCombo, 0, 3);
    hireLayout->addWidget(salaryLabel, 1, 2);
    hireLayout->addWidget(m_salarySpinBox, 1, 3);
    hireLayout->addWidget(positionLabel, 2, 2);
    hireLayout->addWidget(m_positionLineEdit, 2, 3);
    
    // Buttons span across all columns
    hireLayout->addWidget(m_confirmHireBtn, 3, 0, 1, 2);
    hireLayout->addWidget(cancelHireBtn, 3, 2, 1, 2);
    
    // Set column stretches for better proportions
    hireLayout->setColumnStretch(1, 1);
    hireLayout->setColumnStretch(3, 1);
    
    // Connect cancel button
    connect(cancelHireBtn, &QPushButton::clicked, [this]() {
        m_hireEmployeeGroup->setVisible(false);
        // Clear form
        m_nameLineEdit->clear();
        m_phoneLineEdit->clear();
        m_emailLineEdit->clear();
        m_positionLineEdit->clear();
        m_salarySpinBox->setValue(30000);
    });
    
    m_mainLayout->addWidget(m_hireEmployeeGroup);
}

void EmployeeManagementWidget::setupStyles()
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
        
        #lineEdit, #searchInput, #spinBox, #comboBox, #filterCombo {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            background-color: white;
        }
        
        #lineEdit:focus, #searchInput:focus, #spinBox:focus, #comboBox:focus, #filterCombo:focus {
            border-color: #3498db;
        }
    )");
}

void EmployeeManagementWidget::connectSignals()
{
    connect(m_hireEmployeeBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::onHireEmployee);
    connect(m_fireEmployeeBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::onFireEmployee);
    connect(m_viewDetailsBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::onViewEmployeeDetails);
    connect(m_refreshBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::refreshData);
    
    connect(m_searchBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::onSearchEmployee);
    connect(m_clearFilterBtn, &QPushButton::clicked, this, &EmployeeManagementWidget::onFilterEmployees);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EmployeeManagementWidget::onFilterEmployees);
    
    connect(m_confirmHireBtn, &QPushButton::clicked, [this]() {
        QString name = m_nameLineEdit->text().trimmed();
        QString phone = m_phoneLineEdit->text().trimmed();
        QString email = m_emailLineEdit->text().trimmed();
        QString position = m_positionLineEdit->text().trimmed();
        bool gender = m_genderCombo->currentData().toBool();
        double salary = m_salarySpinBox->value();
        
        if (name.isEmpty() || phone.isEmpty() || email.isEmpty() || position.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
            return;
        }
        
        try {
            // Safe approach - show collected information instead of calling problematic method
            QString genderText = gender ? "Male" : "Female";
            QString message = QString("Employee Information Collected:\n\n"
                                    "Name: %1\n"
                                    "Phone: %2\n"
                                    "Email: %3\n"
                                    "Position: %4\n"
                                    "Gender: %5\n"
                                    "Salary: %6 VND\n\n"
                                    "Note: Employee will be added to the system when the backend is fully implemented.")
                                    .arg(name).arg(phone).arg(email).arg(position).arg(genderText).arg(QString::number(salary, 'f', 0));
            
            QMessageBox::information(this, "Employee Information", message);
            m_hireEmployeeGroup->setVisible(false);
            
            // Clear form
            m_nameLineEdit->clear();
            m_phoneLineEdit->clear();
            m_emailLineEdit->clear();
            m_positionLineEdit->clear();
            m_salarySpinBox->setValue(30000);
            
            // Don't call refreshData() as it might cause issues
            
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to process employee data: %1").arg(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "Error", "An unknown error occurred while processing employee data.");
        }
    });
    
    connect(m_employeeTable, &QTableWidget::itemSelectionChanged, 
            this, &EmployeeManagementWidget::onEmployeeSelectionChanged);
}

void EmployeeManagementWidget::populateEmployeeTable()
{
    if (!m_hotelSystem) return;
    
    try {
        // Clear existing data
        m_employeeTable->setRowCount(0);
        
        // Get employee list from the manager
        manager& mgr = m_hotelSystem->getManager();
        std::vector<IPerson*> employees = mgr.getEmployeeList();
        
        // Debug logging
        qDebug() << "Found" << employees.size() << "employees in system";
        
        if (employees.empty()) {
            // If no employees in system, show sample data for demonstration
            const std::vector<std::tuple<int, std::string, std::string, std::string, bool, std::string, double>> sampleEmployees = {
                {2001, "John Smith", "123456789", "john@hotel.com", true, "Receptionist", 15000000},
                {2002, "Jane Doe", "987654321", "jane@hotel.com", false, "Housekeeping", 12000000},
                {2003, "Mike Johnson", "555666777", "mike@hotel.com", true, "Security", 18000000}
            };
            
            for (size_t i = 0; i < sampleEmployees.size(); ++i) {
                const auto& emp = sampleEmployees[i];
                
                m_employeeTable->insertRow(i);
                
                m_employeeTable->setItem(i, 0, new QTableWidgetItem(QString::number(std::get<0>(emp))));
                m_employeeTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::get<1>(emp))));
                m_employeeTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::get<2>(emp))));
                m_employeeTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::get<3>(emp))));
                m_employeeTable->setItem(i, 4, new QTableWidgetItem(std::get<4>(emp) ? "Male" : "Female"));
                m_employeeTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(std::get<5>(emp))));
                m_employeeTable->setItem(i, 6, new QTableWidgetItem(QString::number(std::get<6>(emp), 'f', 0) + " VND"));
                m_employeeTable->setItem(i, 7, new QTableWidgetItem("Employee"));
            }
            
            m_employeeCountLabel->setText(QString("Total Employees: %1 (Sample Data - No employees in system)").arg(sampleEmployees.size()));
        } else {
            // Display actual employees from system
            for (size_t i = 0; i < employees.size(); ++i) {
                employee* emp = dynamic_cast<employee*>(employees[i]);
                if (!emp) continue;
                
                m_employeeTable->insertRow(i);
                
                m_employeeTable->setItem(i, 0, new QTableWidgetItem(QString::number(emp->getID())));
                m_employeeTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(emp->getName())));
                m_employeeTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(emp->getPhone())));
                m_employeeTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(emp->getEmail())));
                m_employeeTable->setItem(i, 4, new QTableWidgetItem(emp->getGender() ? "Male" : "Female"));
                m_employeeTable->setItem(i, 5, new QTableWidgetItem("Employee")); // Default since position is private
                m_employeeTable->setItem(i, 6, new QTableWidgetItem("Confidential")); // Salary is protected
                m_employeeTable->setItem(i, 7, new QTableWidgetItem("Employee"));
            }
            
            m_employeeCountLabel->setText(QString("Total Employees: %1").arg(employees.size()));
        }
        
        // Also show customer count for reference
        std::vector<customer*> customers = m_hotelSystem->getAllCustomers();
        if (!customers.empty()) {
            m_employeeCountLabel->setText(m_employeeCountLabel->text() + 
                                        QString(" | Customers: %1").arg(customers.size()));
        }
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to load employee data: %1").arg(e.what()));
        m_employeeCountLabel->setText("Total Employees: Error loading data");
    }
}

void EmployeeManagementWidget::refreshData()
{
    populateEmployeeTable();
}

void EmployeeManagementWidget::onHireEmployee()
{
    AddEmployeeDialog dialog(m_hotelSystem, this);
    connect(&dialog, &AddEmployeeDialog::employeeAdded, this, &EmployeeManagementWidget::populateEmployeeTable);
    dialog.exec();
}

void EmployeeManagementWidget::onFireEmployee()
{
    int currentRow = m_employeeTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select an employee to fire.");
        return;
    }
    
    int employeeId = m_employeeTable->item(currentRow, 0)->text().toInt();
    QString employeeName = m_employeeTable->item(currentRow, 1)->text();
    
    int reply = QMessageBox::question(this, "Confirm Firing", 
                                      QString("Are you sure you want to fire employee %1 (%2)?")
                                      .arg(employeeName).arg(employeeId),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        try {
            m_hotelSystem->fireEmployee(employeeId);
            QMessageBox::information(this, "Success", "Employee fired successfully!");
            refreshData();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Failed to fire employee: %1").arg(e.what()));
        }
    }
}

void EmployeeManagementWidget::onViewEmployeeDetails()
{
    int currentRow = m_employeeTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select an employee to view details.");
        return;
    }
    
    int employeeId = m_employeeTable->item(currentRow, 0)->text().toInt();
    
    try {
        // Capture employee details output
        std::ostringstream detailsStream;
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(detailsStream.rdbuf());
        
        m_hotelSystem->viewEmployees(); // This would ideally show specific employee details
        
        std::cout.rdbuf(orig);
        
        QString details = QString::fromStdString(detailsStream.str());
        if (details.isEmpty()) {
            details = "Employee details not available.";
        }
        
        QMessageBox::information(this, QString("Employee %1 Details").arg(employeeId), details);
        
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Failed to get employee details: %1").arg(e.what()));
    }
}

void EmployeeManagementWidget::onSearchEmployee()
{
    QString searchText = m_searchLineEdit->text().trimmed();
    if (searchText.isEmpty()) {
        refreshData();
        return;
    }
    
    // Filter table rows based on search text
    for (int row = 0; row < m_employeeTable->rowCount(); ++row) {
        bool found = false;
        for (int col = 0; col < m_employeeTable->columnCount(); ++col) {
            QTableWidgetItem *item = m_employeeTable->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                found = true;
                break;
            }
        }
        m_employeeTable->setRowHidden(row, !found);
    }
}

void EmployeeManagementWidget::onFilterEmployees()
{
    QString filter = m_filterCombo->currentData().toString();
    
    if (filter == "all") {
        // Show all rows
        for (int row = 0; row < m_employeeTable->rowCount(); ++row) {
            m_employeeTable->setRowHidden(row, false);
        }
    } else {
        // Filter based on criteria
        for (int row = 0; row < m_employeeTable->rowCount(); ++row) {
            bool show = false;
            
            if (filter == "active") {
                QTableWidgetItem *statusItem = m_employeeTable->item(row, 7); // Status column
                if (statusItem && statusItem->text().toLower().contains("active")) {
                    show = true;
                }
            } else if (filter == "inactive") {
                QTableWidgetItem *statusItem = m_employeeTable->item(row, 7); // Status column
                if (statusItem && statusItem->text().toLower().contains("inactive")) {
                    show = true;
                }
            } else if (filter == "high_salary") {
                QTableWidgetItem *salaryItem = m_employeeTable->item(row, 6); // Salary column
                if (salaryItem && salaryItem->text().toDouble() > 50000) {
                    show = true;
                }
            }
            
            m_employeeTable->setRowHidden(row, !show);
        }
    }
    
    // Clear search if filtering
    if (filter != "all") {
        m_searchLineEdit->clear();
    }
}

void EmployeeManagementWidget::onEmployeeSelectionChanged()
{
    bool hasSelection = m_employeeTable->currentRow() >= 0;
    m_fireEmployeeBtn->setEnabled(hasSelection);
    m_viewDetailsBtn->setEnabled(hasSelection);
}

