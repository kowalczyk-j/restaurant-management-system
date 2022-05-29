#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addproduct.h"


class AddProduct : public QDialog
{
    Q_OBJECT
public:
	AddProduct(QWidget *parent = 0);
	~AddProduct(){delete ui;}
	QString get_name(){return ui->name->text();}
	int get_quantity(){return ui->quantity->value();}
	int get_unit(){return ui->unit->currentIndex();}
	QString get_allergens(){return ui->allergens->text();}

private:
	Ui::AddProduct *ui;
};
#endif