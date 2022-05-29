#ifndef ADDINGRIDIENT_H
#define ADDINGRIDIENT_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "../../src/pantry/Product.h"
#include "../../src/pantry/Pantry.h"
#include "ui_addingridient.h"


class AddIng : public QDialog
{
    Q_OBJECT
public:
	AddIng(QWidget *parent = 0);
    ~AddIng(){delete ui;}
    void set_products(Pantry & p){
        pan = p;
        for(auto const &dish : p.get_all_products())
        {
            ui->ing->addItem(QString::fromStdString(dish));
        }
        ui->quantity->setValue(0);
        ui->unit->setText(QString::fromStdString(p.get_product(ui->ing->currentText().toStdString()).get_unit()));
    }

    Product get_ing(){
        Product p = Product(pan.get_product(ui->ing->currentText().toStdString()));
        p.set_quantity(ui->quantity->value());
        return p;
    }



private slots:

    void on_ing_currentIndexChanged(){
        ui->quantity->setValue(0);
        ui->unit->setText(QString::fromStdString(pan.get_product(ui->ing->currentText().toStdString()).get_unit()));
    }


private:
    Pantry pan;
	Ui::AddIng *ui;
};
#endif