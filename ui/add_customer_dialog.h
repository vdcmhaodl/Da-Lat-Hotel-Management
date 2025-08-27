#ifndef ADD_CUSTOMER_DIALOG_H
#define ADD_CUSTOMER_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "../include/HotelManagement.h"

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);

signals:
    void customerAdded();

private slots:
    void onAddCustomer();
    void onCancel();

private:
    void setupUI();
    void connectSignals();
    bool validateInput();

    HotelManagementSystem *m_hotelSystem;
    
    QLineEdit *m_nameEdit;
    QLineEdit *m_phoneEdit;
    QLineEdit *m_addressEdit;
    QLineEdit *m_emailEdit;
    QComboBox *m_genderCombo;
    QSpinBox *m_ageSpinBox;
    QLineEdit *m_passwordEdit;
    QPushButton *m_addButton;
    QPushButton *m_cancelButton;
};

#endif // ADD_CUSTOMER_DIALOG_H
