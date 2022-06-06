#ifndef ADDINGRIDIENT_H
#define ADDINGRIDIENT_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QVariant>
#include <iostream>
#include <vector>
#include <string>
#include "../../src/restaurant/Restaurant.h"
#include "ui_addingridient.h"


class AddIng : public QDialog
{
    Q_OBJECT
public:
	AddIng(Restaurant & r, QWidget *parent = 0): QDialog(parent), res(r){
        ui = new Ui::AddIng;
        ui->setupUi(this);
        for(auto  product: res.get_all_prodcucts())
        {
            ui->ing->addItem( QString::fromStdString(product->get_name()), QVariant(product->get_id()));
        }
        ui->quantity->setValue(0);
        if(res.get_products_number() > 0) ui->unit->setText(QString::fromStdString(res.get_all_prodcucts()[0]->get_unit()));
    }
    ~AddIng(){delete ui;}

    Ingredient get_ing(){
        Ingredient ing = Ingredient(ui->ing->currentData().toInt(), ui->quantity->value());
        return ing;
    }



private slots:

    void on_ing_currentIndexChanged(){
        ui->quantity->setValue(0);
        ui->unit->setText(QString::fromStdString(res.get_product(ui->ing->currentData().toInt())->get_unit()));
    }


private:
    Restaurant & res;
	Ui::AddIng *ui;
};
#endif