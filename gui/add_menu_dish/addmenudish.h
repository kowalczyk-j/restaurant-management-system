#ifndef ADDMENUDISH_H
#define ADDMENUDISH_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "../add_ingridient/addingridient.h"
#include "../../src/restaurant/Restaurant.h"
#include "ui_addmenudish.h"


class AddMenuDish : public QDialog
{
    Q_OBJECT
public:
	AddMenuDish(Restaurant & r, QWidget *parent = 0): QDialog(parent), res(r) {
        ui = new Ui::AddMenuDish;
        ui->setupUi(this);
	}
	~AddMenuDish(){delete ui;}
	QString get_name(){return ui->name->text();}
	QString get_zlotys(){return ui->zloty->text();}
	QString get_grosze(){return ui->grosze->text();}
	int get_category(){return ui->category->currentIndex();}
	bool get_vegan(){return ui->vegan->isChecked();}
	vector<Ingredient> & get_ing(){return ingredient;}




private slots:

	void on_addIngridient_clicked(){
		AddIng ai(res);
		ai.setModal(true);
    	if(ai.exec() == QDialog::Accepted){
        	ingredient.push_back(ai.get_ing());
        	ui->DishIngrdidients->clear();
        	for(size_t i=0; i<ingredient.size(); i++){
            	ui->DishIngrdidients->addItem(QString::fromStdString(res.get_product(ingredient[i].stock_id)->get_name()+" ("+to_string(ingredient[i].quantity)+res.get_product(ingredient[i].stock_id)->get_unit() +")"));
        	}
    	}
	}

	void on_removeIngridient_clicked(){
		int position = ui->DishIngrdidients->currentRow();
		if(position != -1){
			ui->DishIngrdidients->setCurrentRow(-1);
			ingredient.erase(ingredient.begin() + position);
			ui->DishIngrdidients->clear();
        	for(size_t i=0; i<ingredient.size(); i++){
            	ui->DishIngrdidients->addItem(QString::fromStdString(res.get_product(ingredient[i].stock_id)->get_name()+" ("+to_string(ingredient[i].quantity)+res.get_product(ingredient[i].stock_id)->get_unit() +")"));
        	}
		}
	}

private:
	Ui::AddMenuDish *ui;
	vector<Ingredient> ingredient;
	Restaurant & res;
};
#endif