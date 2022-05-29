#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addmenudish.h"
#include "addmenudish.h"

AddMenuDish::AddMenuDish(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddMenuDish;
        ui->setupUi(this);
}