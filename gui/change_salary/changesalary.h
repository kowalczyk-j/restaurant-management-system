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

public:
	void set_salary(QString zl, QString gr){ui->zloty->setText(zl); ui->grosze->setText(gr);};
	QString get_salary_zlotys(){return ui->zloty->text();}
	QString get_salary_grosze(){return ui->grosze->text();}

private:
	Ui::ChangeSalary *ui;
};
#endif