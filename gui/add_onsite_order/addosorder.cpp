#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addosorder.h"
#include "addosorder.h"

AddOsOrder::AddOsOrder(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddOsOrder;
        ui->setupUi(this);
}