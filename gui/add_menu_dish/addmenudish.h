#ifndef ADDMENUDISH_H
#define ADDMENUDISH_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "../../src/pantry/Pantry.h"
#include "../add_ingridient/addingridient.h"
#include "ui_addmenudish.h"


class AddMenuDish : public QDialog
{
    Q_OBJECT
public:
	AddMenuDish(QWidget *parent = 0);
	~AddMenuDish(){delete ui;}
	QString get_name(){return ui->name->text();}
	QString get_zlotys(){return ui->zloty->text();}
	QString get_grosze(){return ui->grosze->text();}
	int get_category(){return ui->category->currentIndex();}
	bool get_vegan(){return ui->vegan->isChecked();}
	vector<Product> get_ing(){return pro;}

	void set_pantry(Pantry & p){pan = p;}



private slots:

	void on_addIngridient_clicked(){
		AddIng ai;
		ai.setModal(true);
    	ai.set_products(pan);
    	if(ai.exec() == QDialog::Accepted){
        	pro.push_back(ai.get_ing());
        	ui->DishIngrdidients->clear();
        	for(size_t i=0; i<pro.size(); i++){
            	ui->DishIngrdidients->addItem(QString::fromStdString(pro[i].get_name()+" ("+to_string(pro[i].get_quantity())+pro[i].get_unit() +")"));
        	}
    	}
	}
	void on_removeIngridient_clicked(){
		int position = ui->DishIngrdidients->currentRow();
		if(position != -1){
			ui->DishIngrdidients->setCurrentRow(-1);
			pro.erase(pro.begin() + position);
			ui->DishIngrdidients->clear();
        	for(size_t i=0; i<pro.size(); i++){
            	ui->DishIngrdidients->addItem(QString::fromStdString(pro[i].get_name()+" ("+to_string(pro[i].get_quantity())+pro[i].get_unit() +")"));
        	}
		}
	}

private:
	Ui::AddMenuDish *ui;
	std::vector<Product> pro;
	Pantry pan;
};
#endif