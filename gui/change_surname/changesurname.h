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

public:
	void set_surname(QString surname){ui->surname->setText(surname);};
	QString get_surnname(){return ui->surname->text();}

private:
	Ui::ChangeSurname *ui;
};
#endif