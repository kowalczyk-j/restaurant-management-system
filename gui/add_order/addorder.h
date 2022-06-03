#ifndef ADDORDER_H
#define ADDORDER_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QListWidgetItem>
#include <vector>
#include <iostream>
#include <string>
#include "../add_dish/adddish.h"
#include "../../src/restaurant/Restaurant.h"
#include "ui_addorder.h"


class AddOrder : public QDialog
{
    Q_OBJECT
public:
	AddOrder(Restaurant & r, QWidget *parent = 0):  QDialog(parent), res(r){
		ui = new Ui::AddOrder;
        ui->setupUi(this);
	}
	~AddOrder(){delete ui;}
	QString get_number(){return ui->number->text();}
	QString get_city(){return ui->city->text();}
	QString get_street(){return ui->street->text();}
	QString get_building(){return ui->building->text();}
	QString get_postal_code(){return ui->postal_code->text();}
	std::vector<unsigned int> get_orderedDishes(){return order;}


private slots:


void on_addDishOrder_clicked(){
	AddDish ad(res);
	if(ad.exec() == QDialog::Accepted){
		order.push_back(ad.get_dish_id());
		ui->orderedDishes->clear();
		for(size_t i=0; i<order.size(); i++){
			ui->orderedDishes->addItem(QString::fromStdString(res.get_dish(order[i])->get_name()));
		}
	}
}
void on_removeDishOrder_clicked(){
	int position = ui->orderedDishes->currentRow();
	if(position != -1){
		order.erase(order.begin() + position);
		ui->orderedDishes->clear();
		for(size_t i=0; i<order.size(); i++){
			ui->orderedDishes->addItem(QString::fromStdString(res.get_dish(order[i])->get_name()));
		}
	}
}


private:
	Restaurant & res;
	std::vector<unsigned int> order;
	Ui::AddOrder *ui;
};
#endif