#ifndef ADEMPLOYEE_H
#define ADEMPLOYEE_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addemployee.h"


class AddEmployee : public QDialog
{
    Q_OBJECT
public:
	AddEmployee(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::AddEmployee *ui;
};
#endif