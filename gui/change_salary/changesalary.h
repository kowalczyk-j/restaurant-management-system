#ifndef CHANGESALARY_H
#define CHANGESALARY_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changesalary.h"


class ChangeSalary : public QDialog
{
    Q_OBJECT
public:
	ChangeSalary(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::ChangeSalary *ui;
};
#endif