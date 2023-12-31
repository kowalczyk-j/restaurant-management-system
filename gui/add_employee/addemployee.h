#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H
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
	AddEmployee(QWidget *parent = 0): QDialog(parent){
		ui = new Ui::AddEmployee;
        ui->setupUi(this);
	};
	~AddEmployee(){delete ui;}
	QString get_name(){return ui->name->text();}
	QString get_surname(){return ui->surname->text();}
	QString get_street(){return ui->street->text();}
	QString get_building(){return ui->building->text();}
	QString get_city(){return ui->city->text();}
	QString get_postal_code(){return ui->postal_code->text();}
	QString get_salary_zlotys(){return ui->zloty->text();}
	QString get_salary_grosze(){return ui->grosze->text();}
	int get_role_index(){return ui->role->currentIndex();}


private:
	Ui::AddEmployee *ui;
};
#endif