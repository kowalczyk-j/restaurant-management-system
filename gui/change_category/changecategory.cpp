#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changecategory.h"
#include "changecategory.h"

ChangeCategory::ChangeCategory(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::ChangeCategory;
        ui->setupUi(this);
}