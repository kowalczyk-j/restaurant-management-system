#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_mainwindow.h"
#include "../src/restaurant/Restaurant.h"

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
	void on_orderList_itemClicked();
	void on_modifyDeliveryAddress_clicked();
private:
	Ui::MainWindow *ui;
	std::vector<Restaurant> restaurant_list;
	Restaurant *restaurant;
	Money m;
};
#endif