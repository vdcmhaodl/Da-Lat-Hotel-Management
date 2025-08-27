#include "add_customer_dialog.h"

AddCustomerDialog::AddCustomerDialog(HotelManagementSystem *hotelSystem, QWidget *parent)
    : QDialog(parent), m_hotelSystem(hotelSystem)
{
    setWindowTitle("Add New Customer");
    setModal(true);
    setFixedSize(480, 420); // Tăng 20%: 400*1.2=480, 350*1.2=420
    
    setupUI();
    connectSignals();
}

void AddCustomerDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Add New Customer");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Form layout
    QFormLayout *formLayout = new QFormLayout();
    
    // Customer information fields
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
    m_ageSpinBox->setRange(1, 120);
    m_ageSpinBox->setValue(25);
    formLayout->addRow("Age*:", m_ageSpinBox);
    
    m_genderCombo = new QComboBox();
    m_genderCombo->addItem("Male", true);
    m_genderCombo->addItem("Female", false);
    formLayout->addRow("Gender*:", m_genderCombo);
    
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
    
    m_addButton = new QPushButton("Add Customer");
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
        "QLineEdit, QSpinBox, QComboBox {"
        "    padding: 8px;"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    background-color: white;"
        "    color: black;"
        "    font-size: 14px;"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QComboBox:focus {"
        "    border-color: #3498db;"
        "}"
        "QLabel {"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "}"
    );
}

void AddCustomerDialog::connectSignals()
{
    connect(m_addButton, &QPushButton::clicked, this, &AddCustomerDialog::onAddCustomer);
    connect(m_cancelButton, &QPushButton::clicked, this, &AddCustomerDialog::onCancel);
    
    // Enable Enter to add customer
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &AddCustomerDialog::onAddCustomer);
    connect(m_phoneEdit, &QLineEdit::returnPressed, this, &AddCustomerDialog::onAddCustomer);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &AddCustomerDialog::onAddCustomer);
    
    m_addButton->setDefault(true);
}

bool AddCustomerDialog::validateInput()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter customer name.");
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
    
    return true;
}

void AddCustomerDialog::onAddCustomer()
{
    if (!validateInput()) {
        return;
    }
    
    try {
        QString name = m_nameEdit->text().trimmed();
        QString phone = m_phoneEdit->text().trimmed();
        QString email = m_emailEdit->text().trimmed();
        QString address = m_addressEdit->text().trimmed();
        int age = m_ageSpinBox->value();
        bool gender = m_genderCombo->currentData().toBool();
        QString password = m_passwordEdit->text().trimmed();
        
        // Add customer to the system
        if (m_hotelSystem && m_hotelSystem->addCustomer(name.toStdString(), phone.toStdString(), 
                                                        email.toStdString(), gender, password.toStdString())) {
            QMessageBox::information(this, "Success", 
                                   QString("Customer added successfully!\nName: %1\n\nNote: Customer data prepared but system integration pending.")
                                   .arg(name));
            
            emit customerAdded(); // Emit signal to refresh parent table
            accept(); // Close dialog with success
        } else {
            QMessageBox::critical(this, "Error", "Failed to add customer to system");
        }
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", 
                            QString("Failed to create customer: %1").arg(e.what()));
    }
}

void AddCustomerDialog::onCancel()
{
    reject(); // Close dialog without saving
}
