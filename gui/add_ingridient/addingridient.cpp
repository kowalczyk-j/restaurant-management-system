#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addingridient.h"
#include "addingridient.h"

AddIng::AddIng(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddIng;
        ui->setupUi(this);
}