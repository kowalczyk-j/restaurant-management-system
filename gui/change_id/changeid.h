#ifndef CHANGEID_H
#define CHANGEID_h
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changeid.h"


class ChangeId : public QDialog
{
    Q_OBJECT
public:
	ChangeId(QWidget *parent = 0);


private slots:

public slots:


private:
	Ui::ChangeId *ui;
};
#endif