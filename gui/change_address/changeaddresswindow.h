#ifndef CHANGEADDRESSWINDOW_H
#define CHANGEADDRESSWINDOW_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changeaddresswindow.h"


class ChangeAddressWindow : public QDialog
{
    Q_OBJECT
public:
	ChangeAddressWindow(QWidget *parent = 0);


private slots:

public:
void set_current_address(QString street, QString building, QString city, QString postal_code);
QString get_city();
QString get_street();
QString get_building();
QString get_postal_code();

private:
	Ui::Dialog *ui;
};
#endif