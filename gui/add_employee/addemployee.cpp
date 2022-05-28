#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addemployee.h"
#include "addemployee.h"

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddEmployee;
        ui->setupUi(this);
}