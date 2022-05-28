#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changesurname.h"
#include "changesurname.h"

ChangeSurname::ChangeSurname(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::ChangeSurname;
        ui->setupUi(this);
}