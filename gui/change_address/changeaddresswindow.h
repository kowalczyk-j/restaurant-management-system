#ifndef CHANGEADDRESSWINDOW_H
#define CHANGEADDRESSWINDOW_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changeaddresswindow.h"


class ChangeAddress: public QDialog
{
    Q_OBJECT
public:
	ChangeAddress(QWidget *parent = 0): QDialog(parent){
        ui = new Ui::ChangeAddress;
        ui->setupUi(this);
    };
	~ChangeAddress(){delete ui;};
	void set_current_address(QString street, QString building, QString city, QString postal_code){
		ui->street->setText(street);
		ui->building->setText(building);
		ui->city->setText(city);
		ui->postalCode->setText(postal_code);
	};
	QString get_city(){return ui->city->text();}
	QString get_street(){return ui->street->text();}
	QString get_building(){return ui->building->text();}
	QString get_postal_code(){return ui->postalCode->text();}

private:
	Ui::ChangeAddress *ui;
};
#endif