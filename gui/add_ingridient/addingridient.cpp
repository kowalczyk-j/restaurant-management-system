#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addingridient.h"
#include "addingridient.h"

AddIngridient::AddIngridient(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddIngridient;
        ui->setupUi(this);
}