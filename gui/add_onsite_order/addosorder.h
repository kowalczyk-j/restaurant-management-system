#ifndef ADDOSORDER_H
#define ADDOSORDER_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <vector>
#include <iostream>
#include <string>
#include "../../src/dish_menu/Menu.h"
#include "../add_dish/adddish.h"
#include "ui_addosorder.h"


class AddOsOrder : public QDialog
{
    Q_OBJECT
public:
	AddOsOrder(QWidget *parent = 0);
	~AddOsOrder(){delete ui;}
	void set_menu(Menu & m){menu = m;};
	QString get_number(){return ui->number->text();}
    QString get_table_id(){return ui->table_id->text();}
	vector<Dish> get_orderedDishes(){return order;}


private slots:


void on_addDishOrder_clicked(){
	std::cout<<"test";
	AddDish ad;
	ad.set_menu(menu);
	if(ad.exec() == QDialog::Accepted){
		order.push_back(ad.get_dish());
		ui->orderedDishes->clear();
		for(size_t i=0; i<order.size(); i++){
			ui->orderedDishes->addItem(QString::fromStdString(order[i].get_name()));
		}
	}
}
void on_removeDishOrder_clicked(){
	int position = ui->orderedDishes->currentRow();
	if(position != -1){
		order.erase(order.begin() + position);
	}
	ui->orderedDishes->clear();
	for(size_t i=0; i<order.size(); i++){
		ui->orderedDishes->addItem(QString::fromStdString(order[i].get_name()));
	}
}

private:
	Menu menu;
	std::vector<Dish> order;
	Ui::AddOsOrder *ui;
};
#endif