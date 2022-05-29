#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_mainwindow.h"
#include "../../src/restaurant/Restaurant.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow(){delete ui;}

	std::vector <std::string> vector;

private slots:
	void on_return_2_clicked();
	void on_selectRestaurant_clicked();
	void on_movePantry_clicked();
	void on_moveEmployee_clicked();
	void on_moveMenu_clicked();
	void on_moveOrders_clicked();

	void on_selectRole_currentIndexChanged();

	void on_orderType_currentIndexChanged();
	void on_orderList_itemClicked();
	void on_modifyDeliveryAddress_clicked();
	void on_addDishOrder_clicked();
	void on_removeOrder_clicked();
	void on_addOrderD_clicked();
	void on_addOrderOS_clicked();

	void on_pantryList_itemClicked();
	void on_addProduct_clicked();
	void on_addQuantitytoProduct_clicked();
	void on_removeQuantityfromProduct_clicked();
	void on_removeProduct_clicked();

	void on_employeeList_itemClicked();
	void on_addEmployee_clicked();
	void on_modifyName_clicked();
	void on_modifySurname_clicked();
	void on_modifyId_clicked();
	void on_modifySalary_clicked();
	void on_removeEmployee_clicked();

	void on_menuList_itemClicked();
	void on_modifyPrice_clicked();
	void on_modifyCategory_clicked();
	void on_addIngridient_clicked();
	void on_removeIngridient_clicked();
	void on_addMenuDish_clicked();
	void on_removeMenuDish_clicked();


	Employee & get_employee_refernece();

protected:
    void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindow *ui;
	std::vector<Restaurant> restaurant_list;
	Restaurant *restaurant;
	Money m;
	int position1;
	int position2;
};
#endif
