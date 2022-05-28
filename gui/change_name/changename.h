#ifndef CHANGENAME_H
#define CHANGENAME_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changename.h"


class ChangeName : public QDialog
{
    Q_OBJECT
public:
	ChangeName(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::ChangeName *ui;
};
#endif