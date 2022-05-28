#ifndef ADDDISH_H
#define ADDDISH_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_adddish.h"


class AddDish : public QDialog
{
    Q_OBJECT
public:
	AddDish(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::AddDish *ui;
};
#endif