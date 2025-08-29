#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QStackedWidget>
#include <QFrame>
#include <QPixmap>
#include <QIcon>
#include <memory>
#include "../include/HotelManagement.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onLoginTypeChanged(int index);
    void showRegisterForm();
    void showLoginForm();

private:
    void setupUI();
    void setupLoginForm();
    void setupRegisterForm();
    void setupStyles();
    void connectSignals();
    
    // UI Components
    QWidget *m_centralWidget;
    QStackedWidget *m_stackedWidget;
    
    // Login form
    QWidget *m_loginWidget;
    QComboBox *m_loginTypeCombo;
    QLineEdit *m_idLineEdit;
    QLineEdit *m_passwordLineEdit;
    QPushButton *m_loginButton;
    QPushButton *m_showRegisterButton;
    
    // Register form
    QWidget *m_registerWidget;
    QLineEdit *m_nameLineEdit;
    QLineEdit *m_phoneLineEdit;
    QLineEdit *m_emailLineEdit;
    QLineEdit *m_registerPasswordLineEdit;
    QComboBox *m_genderCombo;
    QPushButton *m_registerButton;
    QPushButton *m_showLoginButton;
    
    // Title and logo
    QLabel *m_titleLabel;
    QLabel *m_logoLabel;
    
    // Hotel Management System
    std::unique_ptr<HotelManagementSystem> m_hotelSystem;
};
