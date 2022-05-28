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

	std::vector <std::string> vector;

private slots:
	void on_return_2_clicked();
	void on_selectRestaurant_clicked();
	void on_movePantry_clicked();
	void on_moveEmployee_clicked();
	void on_moveMenu_clicked();
	void on_moveOrders_clicked();

	void on_selectRole_currentIndexChanged();

	void on_orderList_itemClicked();
	void on_modifyDeliveryAddress_clicked();
	void on_addDishDeliveryOrder_clicked();
	void on_removeDeliveryOrder_clicked();
	void on_addOrder_clicked();

	void on_pantryList_itemClicked();

	void on_employeeList_itemClicked();
	void on_addEmployee_clicked();
	void on_modifyName_clicked();
	void on_modifySurname_clicked();
	void on_modifyId_clicked();
	void on_modifySalary_clicked();
	void on_removeEmployee_clicked();


	Employee & get_employee_refernece();

private:
	Ui::MainWindow *ui;
	std::vector<Restaurant> restaurant_list;
	Restaurant *restaurant;
	Money m;
	int position1;
	int position2;
};
#endif
