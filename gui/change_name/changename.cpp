#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changename.h"
#include "changename.h"

ChangeName::ChangeName(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::ChangeName;
        ui->setupUi(this);
}