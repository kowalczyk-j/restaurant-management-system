#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addproduct.h"
#include "addproduct.h"

AddProduct::AddProduct(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::AddProduct;
        ui->setupUi(this);
}