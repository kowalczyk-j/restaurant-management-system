#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changeid.h"
#include "changeid.h"

ChangeId::ChangeId(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::ChangeId;
        ui->setupUi(this);
}