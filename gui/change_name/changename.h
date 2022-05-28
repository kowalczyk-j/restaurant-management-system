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

public:
	void set_name(QString name){ui->name->setText(name);};
	QString get_name(){return ui->name->text();}

private:
	Ui::ChangeName *ui;
};
#endif