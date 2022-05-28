#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addorder.h"
#include "addorder.h"

AddOrder::AddOrder(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddOrder;
        ui->setupUi(this);
}