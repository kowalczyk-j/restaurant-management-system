#include "changeaddresswindow.h"
#include "ui_changeaddresswindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QStringList>
#include <QQuickItem>
#include <QString>
#include <QObject>
#include <QUrl>
#include <string>
#include <iostream>
#include <vector>
#include <QDebug>
#include <QDialog>

ChangeAddressWindow::ChangeAddressWindow(QWidget *parent) :
    QDialog(parent){
        ui = new Ui::Dialog;
        ui->setupUi(this);
    }

void ChangeAddressWindow::set_current_address(QString street, QString building, QString city, QString postal_code){
    ui->street->setText(street);
    ui->building->setText(building);
    ui->city->setText(city);
    ui->postalCode->setText(postal_code);
}

QString ChangeAddressWindow::get_city(){
    return(ui->city->text());
}

QString ChangeAddressWindow::get_street(){
    return(ui->street->text());
}

QString ChangeAddressWindow::get_building(){
    return(ui->building->text());
}

QString ChangeAddressWindow::get_postal_code(){
    return(ui->postalCode->text());
}