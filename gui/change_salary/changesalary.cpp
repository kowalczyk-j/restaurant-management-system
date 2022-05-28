#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changesalary.h"
#include "changesalary.h"

ChangeSalary::ChangeSalary(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::ChangeSalary;
        ui->setupUi(this);
}