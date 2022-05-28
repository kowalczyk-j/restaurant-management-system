#ifndef ADDORDER_H
#define ADDORDER_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addorder.h"


class AddOrder : public QDialog
{
    Q_OBJECT
public:
	AddOrder(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::AddOrder *ui;
};
#endif