#ifndef ADDDISH_H
#define ADDDISH_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "../../src/dish_menu/Menu.h"
#include "ui_adddish.h"


class AddDish : public QDialog
{
    Q_OBJECT
public:
	AddDish(QWidget *parent = 0);
	~AddDish(){delete ui;}
	void set_menu(Menu & m){
		menu = m;
		for(size_t i=0; i<menu.get_dishes().size(); i++){
			ui->listWidget->addItem(QString::fromStdString(menu.get_dishes()[i].get_name()));
		}
	}
	Dish & get_dish(){
		return menu.get_dishes()[ui->listWidget->currentRow()];
	}

private:
	Menu menu;
	Ui::AddDish *ui;
};
#endif