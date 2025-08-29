#include "login_window.h"
#include "manager_window.h"
#include "employee_window.h"
#include "customer_window.h"
#include <QApplication>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_stackedWidget(nullptr)
{
    
    // Initialize hotel system
    m_hotelSystem = std::make_unique<HotelManagementSystem>(
        5, "Huynh Thai Hoang", "0983824401", "manager@hotel.com", 1, 1, 60000, "Manager"
    );
    m_hotelSystem->loadSystemState();
    
    setupUI();
    setupStyles();
    connectSignals();
    
    // Window properties
    setWindowTitle("Hotel Management System - Login");
    setMinimumSize(800, 600);
    resize(1000, 700);
    
    // Center the window
    setWindowIcon(QIcon(":/icons/hotel.png")); // You can add an icon resource later
}

LoginWindow::~LoginWindow()
{
    if (m_hotelSystem) {
        m_hotelSystem->saveSystemState();
    }
}

void LoginWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(50, 30, 50, 30);
    
    // Title section
    QWidget *titleWidget = new QWidget();
    QVBoxLayout *titleLayout = new QVBoxLayout(titleWidget);
    titleLayout->setAlignment(Qt::AlignCenter);
    
    m_titleLabel = new QLabel("Da Lat Hotel Management System");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setObjectName("titleLabel");
    
    QLabel *subtitleLabel = new QLabel("Welcome to our luxury hotel management platform");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setObjectName("subtitleLabel");
    
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addWidget(subtitleLabel);
    
    // Stacked widget for login/register forms
    m_stackedWidget = new QStackedWidget();
    setupLoginForm();
    setupRegisterForm();
    
    // Add widgets to main layout
    mainLayout->addWidget(titleWidget);
    mainLayout->addWidget(m_stackedWidget, 1);
    mainLayout->addStretch();
}

void LoginWindow::setupLoginForm()
{
    m_loginWidget = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(m_loginWidget);
    loginLayout->setAlignment(Qt::AlignCenter);
    loginLayout->setSpacing(20);
    
    // Login form frame
    QFrame *loginFrame = new QFrame();
    loginFrame->setObjectName("loginFrame");
    loginFrame->setMaximumWidth(400);
    loginFrame->setMinimumWidth(350);
    
    QVBoxLayout *frameLayout = new QVBoxLayout(loginFrame);
    frameLayout->setSpacing(15);
    frameLayout->setContentsMargins(30, 30, 30, 30);
    
    // Form title
    QLabel *formTitle = new QLabel("Login to Your Account");
    formTitle->setAlignment(Qt::AlignCenter);
    formTitle->setObjectName("formTitle");
    frameLayout->addWidget(formTitle);
    
    // Login type selection
    QLabel *typeLabel = new QLabel("Login as:");
    m_loginTypeCombo = new QComboBox();
    m_loginTypeCombo->addItem("Manager", 1);
    m_loginTypeCombo->addItem("Employee", 2);
    m_loginTypeCombo->addItem("Customer", 3);
    m_loginTypeCombo->setObjectName("comboBox");
    
    frameLayout->addWidget(typeLabel);
    frameLayout->addWidget(m_loginTypeCombo);
    
    // ID input
    QLabel *idLabel = new QLabel("ID:");
    m_idLineEdit = new QLineEdit();
    m_idLineEdit->setPlaceholderText("Enter your ID");
    m_idLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(idLabel);
    frameLayout->addWidget(m_idLineEdit);
    
    // Password input
    QLabel *passwordLabel = new QLabel("Password:");
    m_passwordLineEdit = new QLineEdit();
    m_passwordLineEdit->setPlaceholderText("Enter your password");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_passwordLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(passwordLabel);
    frameLayout->addWidget(m_passwordLineEdit);
    
    // Login button
    m_loginButton = new QPushButton("Login");
    m_loginButton->setObjectName("primaryButton");
    m_loginButton->setMinimumWidth(120);
    m_loginButton->setMinimumHeight(40);
    frameLayout->addWidget(m_loginButton);
    
    // Register link
    m_showRegisterButton = new QPushButton("Don't have an account? Register here");
    m_showRegisterButton->setObjectName("linkButton");
    frameLayout->addWidget(m_showRegisterButton);
    
    loginLayout->addWidget(loginFrame);
    m_stackedWidget->addWidget(m_loginWidget);
}

void LoginWindow::setupRegisterForm()
{
    m_registerWidget = new QWidget();
    QVBoxLayout *registerLayout = new QVBoxLayout(m_registerWidget);
    registerLayout->setAlignment(Qt::AlignCenter);
    registerLayout->setSpacing(15);
    registerLayout->setContentsMargins(20, 20, 20, 20);
    
    // Register form frame
    QFrame *registerFrame = new QFrame();
    registerFrame->setObjectName("loginFrame");
    registerFrame->setMaximumWidth(480);
    registerFrame->setMinimumWidth(450);
    
    QVBoxLayout *frameLayout = new QVBoxLayout(registerFrame);
    frameLayout->setSpacing(8);
    frameLayout->setContentsMargins(40, 25, 40, 25);
    
    // Form title
    QLabel *formTitle = new QLabel("Create New Customer Account");
    formTitle->setAlignment(Qt::AlignCenter);
    formTitle->setObjectName("formTitle");
    formTitle->setWordWrap(true);
    formTitle->setMinimumHeight(40);
    frameLayout->addWidget(formTitle);
    
    // Add some space after title
    frameLayout->addSpacing(20);
    
    // Name input (no label, just placeholder)
    m_nameLineEdit = new QLineEdit();
    m_nameLineEdit->setPlaceholderText("Full Name");
    m_nameLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(m_nameLineEdit);
    frameLayout->addSpacing(10);
    
    // Phone input (no label, just placeholder)
    m_phoneLineEdit = new QLineEdit();
    m_phoneLineEdit->setPlaceholderText("Phone Number");
    m_phoneLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(m_phoneLineEdit);
    frameLayout->addSpacing(10);
    
    // Email input (no label, just placeholder)
    m_emailLineEdit = new QLineEdit();
    m_emailLineEdit->setPlaceholderText("Email Address");
    m_emailLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(m_emailLineEdit);
    frameLayout->addSpacing(10);
    
    // Password input (no label, just placeholder)
    m_registerPasswordLineEdit = new QLineEdit();
    m_registerPasswordLineEdit->setPlaceholderText("Password");
    m_registerPasswordLineEdit->setEchoMode(QLineEdit::Password);
    m_registerPasswordLineEdit->setObjectName("lineEdit");
    
    frameLayout->addWidget(m_registerPasswordLineEdit);
    frameLayout->addSpacing(10);
    
    // Gender selection (no label, just placeholder in combobox)
    m_genderCombo = new QComboBox();
    m_genderCombo->addItem("Select Gender", QVariant());
    m_genderCombo->addItem("Male", true);
    m_genderCombo->addItem("Female", false);
    m_genderCombo->setObjectName("comboBox");
    
    frameLayout->addWidget(m_genderCombo);
    
    // Add space before button
    frameLayout->addSpacing(20);
    
    // Register button
    m_registerButton = new QPushButton("Register");
    m_registerButton->setObjectName("primaryButton");
    frameLayout->addWidget(m_registerButton);
    
    // Login link
    m_showLoginButton = new QPushButton("Already have an account? Login here");
    m_showLoginButton->setObjectName("linkButton");
    frameLayout->addWidget(m_showLoginButton);
    
    registerLayout->addWidget(registerFrame);
    m_stackedWidget->addWidget(m_registerWidget);
}

void LoginWindow::setupStyles()
{
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                                      stop: 0 #2c3e50, stop: 1 #34495e);
        }
        
        #titleLabel {
            font-size: 32px;
            font-weight: bold;
            color: #ecf0f1;
            margin-bottom: 10px;
        }
        
        #subtitleLabel {
            font-size: 16px;
            color: #bdc3c7;
            margin-bottom: 20px;
        }
        
        #loginFrame {
            background-color: rgba(255, 255, 255, 0.95);
            border-radius: 15px;
            border: 2px solid #3498db;
        }
        
        #formTitle {
            font-size: 18px;
            font-weight: bold;
            color: #2c3e50;
            margin: 8px 0px;
            padding: 8px 10px;
            line-height: 1.3;
        }
        
        QLabel {
            color: #2c3e50;
            font-weight: bold;
            font-size: 12px;
        }
        
        #fieldLabel {
            color: #2c3e50;
            font-weight: bold;
            font-size: 13px;
            margin-bottom: 3px;
            margin-top: 1px;
            padding-bottom: 1px;
        }
        
        #lineEdit {
            padding: 12px;
            border: 2px solid #bdc3c7;
            border-radius: 8px;
            font-size: 14px;
            background-color: white;
            color: black;
            margin-bottom: 2px;
            min-height: 18px;
        }
        
        #lineEdit::placeholder {
            color: #7f8c8d;
            font-style: italic;
        }
        
        #lineEdit:focus {
            border-color: #3498db;
            outline: none;
            background-color: white;
            color: black;
        }
        
        #comboBox {
            padding: 12px;
            border: 2px solid #bdc3c7;
            border-radius: 8px;
            font-size: 14px;
            background-color: white;
            color: black;
            margin-bottom: 2px;
            min-height: 18px;
        }
        
        #comboBox:focus {
            border-color: #3498db;
            background-color: white;
            color: black;
        }
        
        #comboBox QAbstractItemView {
            background-color: white;
            color: black;
            selection-background-color: #3498db;
            selection-color: white;
        }
        
        #primaryButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 14px;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            margin-top: 8px;
            min-height: 20px;
        }
        
        #primaryButton:hover {
            background-color: #2980b9;
        }
        
        #primaryButton:pressed {
            background-color: #21618c;
        }
        
        #linkButton {
            background: none;
            border: none;
            color: #3498db;
            font-size: 12px;
            text-decoration: underline;
            margin-top: 10px;
        }
        
        #linkButton:hover {
            color: #2980b9;
        }
        
        QMessageBox {
            background-color: white;
            color: black;
        }
        
        QMessageBox QLabel {
            color: black;
            background-color: white;
        }
        
        QMessageBox QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
            min-width: 60px;
        }
        
        QMessageBox QPushButton:hover {
            background-color: #2980b9;
        }
        
        QMessageBox QPushButton:pressed {
            background-color: #21618c;
        }
    )");
}

void LoginWindow::connectSignals()
{
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(m_registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
    connect(m_showRegisterButton, &QPushButton::clicked, this, &LoginWindow::showRegisterForm);
    connect(m_showLoginButton, &QPushButton::clicked, this, &LoginWindow::showLoginForm);
    connect(m_loginTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &LoginWindow::onLoginTypeChanged);
    
    // Enable Enter key for login
    connect(m_idLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
    connect(m_passwordLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
    
    // Set login button as default
    m_loginButton->setDefault(true);
}

void LoginWindow::onLoginClicked()
{
    int loginType = m_loginTypeCombo->currentData().toInt();
    QString id = m_idLineEdit->text().trimmed();
    QString password = m_passwordLineEdit->text();
    
    if (id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both ID and password.");
        return;
    }
    
    try {
        switch (loginType) {
        case 1: // Manager
            if (m_hotelSystem->checkPassManager(password.toStdString())) {
                hide();
                ManagerWindow *managerWindow = new ManagerWindow(m_hotelSystem.get());
                managerWindow->show();
                connect(managerWindow, &QMainWindow::destroyed, this, &QWidget::show);
            } else {
                QMessageBox::warning(this, "Login Failed", "Invalid manager password.");
            }
            break;
            
        case 2: // Employee
        {
            int empId = id.toInt();
            if (m_hotelSystem->isEmployee(empId) && 
                m_hotelSystem->checkPassEmployee(empId, password.toStdString())) {
                hide();
                EmployeeWindow *employeeWindow = new EmployeeWindow(m_hotelSystem.get(), empId);
                employeeWindow->show();
                connect(employeeWindow, &QMainWindow::destroyed, this, &QWidget::show);
            } else {
                QMessageBox::warning(this, "Login Failed", "Employee not found or invalid password.");
            }
            break;
        }
        
        case 3: // Customer
        {
            int custId = id.toInt();
            qDebug() << "Attempting customer login with ID:" << custId;
            
            try {
                if (m_hotelSystem->checkPassCustomer(custId, password.toStdString())) {
                    qDebug() << "Password check passed";
                    customer *cust = m_hotelSystem->getCustomerById(custId);
                    if (cust) {
                        qDebug() << "Customer found, attempting to get name...";
                        try {
                            QString customerName = QString::fromStdString(cust->getName());
                            qDebug() << "Customer name:" << customerName;
                        } catch (const std::exception& e) {
                            qDebug() << "Error getting customer name:" << e.what();
                            QMessageBox::critical(this, "Error", QString("Failed to access customer data: %1").arg(e.what()));
                            return;
                        }
                        
                        hide();
                        try {
                            qDebug() << "Creating CustomerWindow...";
                            CustomerWindow *customerWindow = new CustomerWindow(m_hotelSystem.get(), cust);
                            qDebug() << "CustomerWindow created successfully";
                            customerWindow->show();
                            connect(customerWindow, &QMainWindow::destroyed, this, &QWidget::show);
                        } catch (const std::exception &e) {
                            qDebug() << "Exception creating CustomerWindow:" << e.what();
                            QMessageBox::critical(this, "Error", QString("Failed to open customer window: %1").arg(e.what()));
                            show();
                        }
                    } else {
                        qDebug() << "Customer not found with ID:" << custId;
                        QMessageBox::warning(this, "Login Failed", "Error retrieving customer information.");
                    }
                } else {
                    qDebug() << "Password check failed for customer ID:" << custId;
                    QMessageBox::warning(this, "Login Failed", "Customer not found or invalid password.");
                }
            } catch (const std::exception &e) {
                qDebug() << "Exception during customer login:" << e.what();
                QMessageBox::critical(this, "Error", QString("Login error: %1").arg(e.what()));
            }
            break;
        }
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Login error: %1").arg(e.what()));
    }
    
    // Clear password field for security
    m_passwordLineEdit->clear();
}

void LoginWindow::onRegisterClicked()
{
    QString name = m_nameLineEdit->text().trimmed();
    QString phone = m_phoneLineEdit->text().trimmed();
    QString email = m_emailLineEdit->text().trimmed();
    QString password = m_registerPasswordLineEdit->text().trimmed();
    bool gender = m_genderCombo->currentData().toBool();
    
    if (name.isEmpty() || phone.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }
    
    try {
        // Use the version with parameters to avoid console input
        bool success = m_hotelSystem->addCustomer(
            name.toStdString(), 
            phone.toStdString(), 
            email.toStdString(), 
            gender, 
            password.toStdString()
        );
        
        if (success) {
            // Get the newly created customer ID (assuming it's the last one added)
            auto customers = m_hotelSystem->getAllCustomers();
            if (!customers.empty()) {
                int newCustomerID = customers.back()->getID();
                QMessageBox::information(this, "Registration Successful", 
                    QString("Account created successfully!\nYour Customer ID is: %1\nPassword: %2\n\nPlease remember your ID and password for login.")
                    .arg(newCustomerID).arg(password));
            } else {
                QMessageBox::information(this, "Registration Successful", 
                    QString("Account created successfully!\nPassword: %1\n\nPlease remember your password for login.")
                    .arg(password));
            }
            
            // Clear form and switch to login
            m_nameLineEdit->clear();
            m_phoneLineEdit->clear();
            m_emailLineEdit->clear();
            m_registerPasswordLineEdit->clear();
            showLoginForm();
        } else {
            QMessageBox::warning(this, "Registration Failed", "Failed to create customer account.");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Registration error: %1").arg(e.what()));
    }
}

void LoginWindow::onLoginTypeChanged(int index)
{
    Q_UNUSED(index)
    int loginType = m_loginTypeCombo->currentData().toInt();
    
    if (loginType == 1) { // Manager
        m_idLineEdit->setPlaceholderText("Manager ID (leave empty)");
        m_passwordLineEdit->setPlaceholderText("Manager password");
    } else if (loginType == 2) { // Employee
        m_idLineEdit->setPlaceholderText("Employee ID");
        m_passwordLineEdit->setPlaceholderText("Employee password");
    } else { // Customer
        m_idLineEdit->setPlaceholderText("Customer ID");
        m_passwordLineEdit->setPlaceholderText("Customer password");
    }
}

void LoginWindow::showRegisterForm()
{
    m_stackedWidget->setCurrentWidget(m_registerWidget);
}

void LoginWindow::showLoginForm()
{
    m_stackedWidget->setCurrentWidget(m_loginWidget);
}

