#ifndef CHANGESURNAME_H
#define CHANGESURNAME_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changesurname.h"


class ChangeSurname : public QDialog
{
    Q_OBJECT
public:
	ChangeSurname(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::ChangeSurname *ui;
};
#endif