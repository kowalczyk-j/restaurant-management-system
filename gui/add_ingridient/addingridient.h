#ifndef ADDINGRIDIENT_H
#define ADDINGRIDIENT_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_addingridient.h"
//#include "../../src/pantry/Product.h"


class AddIngridient : public QDialog
{
    Q_OBJECT
public:
	AddIngridient(QWidget *parent = 0);


private slots:

public:
	void set_products(vetcor<Product> vp){
		for(size_t i= 0; i<vp.size(); i++){
			ui->name->addItem(QString::fromStdString(vp[i].get_name()));
		}
	}


private:
	Ui::AddIngridient *ui;
};
#endif