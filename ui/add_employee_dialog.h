#ifndef ADD_EMPLOYEE_DIALOG_H
#define ADD_EMPLOYEE_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTime>
#include "../include/HotelManagement.h"

class AddEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeDialog(HotelManagementSystem *hotelSystem, QWidget *parent = nullptr);

signals:
    void employeeAdded();

private slots:
    void onAddEmployee();
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
    QDoubleSpinBox *m_salarySpinBox;
    QComboBox *m_positionCombo;
    QPushButton *m_addButton;
    QPushButton *m_cancelButton;
};

#endif // ADD_EMPLOYEE_DIALOG_H
