#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_adddish.h"
#include "adddish.h"

AddDish::AddDish(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddDish;
        ui->setupUi(this);
}