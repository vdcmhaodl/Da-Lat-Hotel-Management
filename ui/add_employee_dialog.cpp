#include "add_employee_dialog.h"

AddEmployeeDialog::AddEmployeeDialog(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QDialog(parent), m_hotelSystem(hotelSystem)
{
    setWindowTitle("Add New Employee");
    setModal(true);
    setFixedSize(400, 400);
    
    setupUI();
    connectSignals();
}

void AddEmployeeDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Add New Employee");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Form layout
    QFormLayout *formLayout = new QFormLayout();
    
    // Employee information fields
    m_nameEdit = new QLineEdit();
    m_nameEdit->setPlaceholderText("Enter full name");
    formLayout->addRow("Full Name*:", m_nameEdit);
    
    m_phoneEdit = new QLineEdit();
    m_phoneEdit->setPlaceholderText("Enter phone number");
    formLayout->addRow("Phone*:", m_phoneEdit);
    
    m_emailEdit = new QLineEdit();
    m_emailEdit->setPlaceholderText("Enter email address");
    formLayout->addRow("Email:", m_emailEdit);
    
    m_addressEdit = new QLineEdit();
    m_addressEdit->setPlaceholderText("Enter address");
    formLayout->addRow("Address:", m_addressEdit);
    
    m_ageSpinBox = new QSpinBox();
    m_ageSpinBox->setRange(18, 65);
    m_ageSpinBox->setValue(25);
    formLayout->addRow("Age*:", m_ageSpinBox);
    
    m_genderCombo = new QComboBox();
    m_genderCombo->addItem("Male", true);
    m_genderCombo->addItem("Female", false);
    formLayout->addRow("Gender*:", m_genderCombo);
    
    m_salarySpinBox = new QDoubleSpinBox();
    m_salarySpinBox->setRange(0, 999999);
    m_salarySpinBox->setValue(15000000); // Default salary
    m_salarySpinBox->setSuffix(" VND");
    formLayout->addRow("Salary*:", m_salarySpinBox);
    
    m_positionCombo = new QComboBox();
    m_positionCombo->addItem("Receptionist", "Receptionist");
    m_positionCombo->addItem("Housekeeping", "Housekeeping");
    m_positionCombo->addItem("Security", "Security");
    m_positionCombo->addItem("Maintenance", "Maintenance");
    m_positionCombo->addItem("Food Service", "Food Service");
    m_positionCombo->addItem("Supervisor", "Supervisor");
    formLayout->addRow("Position*:", m_positionCombo);
    
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("Enter password");
    formLayout->addRow("Password*:", m_passwordEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Note
    QLabel *noteLabel = new QLabel("* Required fields");
    noteLabel->setStyleSheet("color: #e74c3c; font-size: 12px; font-style: italic;");
    mainLayout->addWidget(noteLabel);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    m_addButton = new QPushButton("Add Employee");
    m_addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #27ae60;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2ecc71;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #229954;"
        "}"
    );
    
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #95a5a6;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #bdc3c7;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #7f8c8d;"
        "}"
    );
    
    buttonLayout->addWidget(m_cancelButton);
    buttonLayout->addWidget(m_addButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Set form styles
    setStyleSheet(
        "QDialog {"
        "    background-color: #ecf0f1;"
        "}"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "    padding: 8px;"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    background-color: white;"
        "    color: black;"
        "    font-size: 14px;"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {"
        "    border-color: #3498db;"
        "}"
        "QLabel {"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "}"
    );
}

void AddEmployeeDialog::connectSignals()
{
    connect(m_addButton, &QPushButton::clicked, this, &AddEmployeeDialog::onAddEmployee);
    connect(m_cancelButton, &QPushButton::clicked, this, &AddEmployeeDialog::onCancel);
    
    // Enable Enter to add employee
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &AddEmployeeDialog::onAddEmployee);
    connect(m_phoneEdit, &QLineEdit::returnPressed, this, &AddEmployeeDialog::onAddEmployee);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &AddEmployeeDialog::onAddEmployee);
    
    m_addButton->setDefault(true);
}

bool AddEmployeeDialog::validateInput()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter employee name.");
        m_nameEdit->setFocus();
        return false;
    }
    
    if (m_phoneEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter phone number.");
        m_phoneEdit->setFocus();
        return false;
    }
    
    if (m_passwordEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter password.");
        m_passwordEdit->setFocus();
        return false;
    }
    
    if (m_salarySpinBox->value() <= 0) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid salary.");
        m_salarySpinBox->setFocus();
        return false;
    }
    
    return true;
}

void AddEmployeeDialog::onAddEmployee()
{
    if (!validateInput()) {
        return;
    }
    
    try {
        QString name = m_nameEdit->text().trimmed();
        QString phone = m_phoneEdit->text().trimmed();
        QString email = m_emailEdit->text().trimmed();
        QString address = m_addressEdit->text().trimmed();
        bool gender = m_genderCombo->currentData().toBool();
        QString password = m_passwordEdit->text().trimmed();
        double salary = m_salarySpinBox->value();
        QString position = m_positionCombo->currentData().toString();
        
        // Add employee to the system
        if (m_hotelSystem && m_hotelSystem->addEmployee(name.toStdString(), phone.toStdString(), 
                                                        email.toStdString(), gender, salary, 
                                                        position.toStdString(), password.toStdString())) {
            QMessageBox::information(this, "Employee Information",
                                   QString("Employee Information Collected:\n\n"
                                          "Name: %1\n"
                                          "Phone: %2\n"
                                          "Email: %3\n"
                                          "Position: %4\n"
                                          "Gender: %5\n"
                                          "Salary: %6 VND\n\n"
                                          "Note: Employee will be added to the system when the backend is fully implemented.")
                                   .arg(name)
                                   .arg(phone)
                                   .arg(email)
                                   .arg(position)
                                   .arg(gender ? "Male" : "Female")
                                   .arg(QString::number(salary, 'f', 0)));
            
            emit employeeAdded(); // Emit signal to refresh parent table
            accept(); // Close dialog with success
        } else {
            QMessageBox::critical(this, "Error", "Failed to add employee to system");
        }
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", 
                            QString("Failed to create employee: %1").arg(e.what()));
    }
}

void AddEmployeeDialog::onCancel()
{
    reject(); // Close dialog without saving
}
