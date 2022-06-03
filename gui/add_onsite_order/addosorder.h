#ifndef ADDOSORDER_H
#define ADDOSORDER_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <vector>
#include <iostream>
#include <string>
#include "../add_dish/adddish.h"
#include "ui_addosorder.h"


class AddOsOrder : public QDialog
{
    Q_OBJECT
public:
	AddOsOrder(Restaurant& r, QWidget *parent = 0): QDialog(parent), res(r){
		ui = new Ui::AddOsOrder;
        ui->setupUi(this);
	};
	~AddOsOrder(){delete ui;}
    QString get_table_id(){return ui->table_id->text();}
	vector<unsigned int> get_orderedDishes(){return order;}


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
	Ui::AddOsOrder *ui;
};
#endif