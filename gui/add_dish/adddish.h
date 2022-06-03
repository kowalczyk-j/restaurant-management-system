#ifndef ADDDISH_H
#define ADDDISH_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QListWidgetItem>
#include <iostream>
#include <string>
#include <vector>
#include "../../src/restaurant/Restaurant.h"
#include "ui_adddish.h"


class AddDish : public QDialog
{
    Q_OBJECT
public:
	AddDish(Restaurant & r, QWidget *parent = 0): QDialog(parent), res(r){
		ui = new Ui::AddDish;
        ui->setupUi(this);
		for(size_t i=0; i<res.get_all_dishes().size(); i++){
			new QListWidgetItem(QString::fromStdString(res.get_all_dishes()[i]->get_name()),
								ui->listWidget,
								res.get_all_dishes()[i]->get_id());
		}
	}
	~AddDish(){delete ui;}
	unsigned int get_dish_id(){
		return ui->listWidget->currentItem()->type();
	}

private:
	Restaurant & res;
	Ui::AddDish *ui;
};
#endif