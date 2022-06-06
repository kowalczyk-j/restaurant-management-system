#ifndef CHANGECATEGORY_H
#define CHANGECATEGORY_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changecategory.h"


class ChangeCategory : public QDialog
{
    Q_OBJECT
public:
	ChangeCategory(QWidget *parent = 0):QDialog(parent){
        ui = new Ui::ChangeCategory;
        ui->setupUi(this);
};
	~ChangeCategory(){delete ui;}
	int get_category(){return ui->newCategory->currentIndex();}

private:
	Ui::ChangeCategory *ui;
};
#endif