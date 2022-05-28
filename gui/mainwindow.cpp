#include "mainwindow.h"
#include "changeaddresswindow.h"
#include "addorder.h"
#include "adddish.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QStringList>
#include <QQuickItem>
#include <QString>
#include <QObject>
#include <QUrl>
#include <string>
#include <iostream>
#include <vector>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    Product p = Product("jablko",670, g);
    Product p1 = Product("mieso",500, g);
    Product p2 = Product("sok jablkowy",1000, ml);
    Product p3 = Product("jajka",60, szt);
    Product p4  = Product("koperek",100, g);
    Product p5 = Product("ziemniaki",4000, g);
    cout << p.get_name()<< " " << p.get_quantity() << " " << p.get_unit() << endl;


    Pantry pan;
    set<string> s;
    pan.add_product("jablko", 6, g,  s);
    pan.add_product("mieso",500, g, s);
    pan.add_product("sok jablkowy",1000, ml, s);

    Addres a1 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.220154, 21.011968);
    Addres a2 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.216184, 20.239073);
    std::map<std::string, Product> map = {{"jablko", p}};
    Dish d1 = Dish(1, "zupa pomidorowa", przystawka, Money(500), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    Cook c = Cook("Jan", "Kowalski", 1, 5, Money(800000), 0);
    std::vector<Employee> ve;
    ve.push_back(c);


    DeliveryOrder * os = new DeliveryOrder(1, dishes, a1, 10);
    std::vector<DeliveryOrder*> vd;
    vd.push_back(os);
    Restaurant r1 =  Restaurant(1, "Magnoliowa", a1, pan, m, ve, vd);
    Restaurant r2 =  Restaurant(2, "Różana", a2, pan, m, ve, vd);

    restaurant_list.push_back(r1);
    restaurant_list.push_back(r2);




    vector.push_back("Restauracj Magnoliowa");
    vector.push_back("Restauracja Różana");
    QString buff1;
    QStringList buff2;
    restaurant = & restaurant_list[0];
    ui = new Ui::MainWindow;
	ui->setupUi(this);
    ui->mapa->setSource(QUrl(QStringLiteral("rsc/qmlMap.qml")));
    ui->mapa->setResizeMode( QQuickWidget::SizeRootObjectToView );

    for(unsigned int i=0; i<restaurant_list.size(); i++){
        ui->list1->addItem(QString::fromStdString(restaurant_list[i].get_name()));
    }


}
void MainWindow::on_return_2_clicked(){
    if(ui->restaurantStack->currentIndex() == 0)
    ui->mainStack->setCurrentIndex(0);
    else ui->restaurantStack->setCurrentIndex(0);

}
void MainWindow::on_selectRestaurant_clicked(){
    if (ui->list1->currentRow() != -1){
        restaurant = & restaurant_list[ui->list1->currentRow()];

        QObject *object = ui->mapa->rootObject();
        object->setProperty("latitude", restaurant->get_address().get_latitude());
        object->setProperty("longitude", restaurant->get_address().get_longitude());

        ui->image->setPixmap(QString::fromStdString("rsc/"+restaurant->get_name()+".jpg"));
        ui->restaurationName->setText(QString::fromStdString(restaurant->get_name()));
        ui->employeesNumber->setText(QString::number(restaurant->get_employees().size()));
        ui->ordersNumber->setText(QString::number(restaurant->get_orders().size()));
        ui->menuPositionsNumber->setText(QString::number(restaurant->get_menu().size()));

        ui->orderList->clear();
        ui->pantryList->clear();
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_orders().size(); i++){
            ui->orderList->addItem(QString::number(restaurant->get_orders()[i]->get_order_id()));
        }
        for(unsigned int i=0; i<restaurant->get_pantry().get_all_products().size(); i++){
            ui->pantryList->addItem(QString::fromStdString(restaurant->get_pantry().get_all_products()[i]));
        }
        ui->mainStack->setCurrentIndex(1);

        for(unsigned int i=0; i<restaurant->get_employees().size(); i++){
        ui->employeeList->addItem(QString::fromStdString(restaurant->get_employees()[i].get_name() + " " + restaurant->get_employees()[i].get_surname() + " (" + to_string(restaurant->get_employees()[i].get_employee_id()) + ")"));
        }

        ui->mainStack->setCurrentIndex(1);
    }
}
void MainWindow::on_movePantry_clicked(){
    ui->restaurantStack->setCurrentIndex(1);
    ui->pantryStack->setCurrentIndex(1);
}
void MainWindow::on_moveEmployee_clicked(){
    ui->restaurantStack->setCurrentIndex(2);
    ui->employeeStack->setCurrentIndex(1);
}
void MainWindow::on_moveMenu_clicked(){
    ui->restaurantStack->setCurrentIndex(3);
    ui->menuStack->setCurrentIndex(1);
}
void MainWindow::on_moveOrders_clicked(){
    ui->restaurantStack->setCurrentIndex(4);
    ui->orderStack->setCurrentIndex(1);
}

void MainWindow::on_orderList_itemClicked(){
    ui->orderedDishesDelivery->clear();
    size_t position = ui->orderList->currentRow();
    restaurant->get_orders()[position];
    ui->orderNumber->setText(QString::fromStdString("#"+to_string(restaurant->get_orders()[position]->get_order_id())));
    ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_orders()[position]->get_order_value().to_string()));
    ui->orderDelivery->setText(QString::fromStdString(restaurant->get_orders()[position]->get_delivery_address().to_string()));
    for(unsigned int i=0; i<restaurant->get_orders()[position]->get_ordered_dishes().size(); i++){
        ui->orderedDishesDelivery->addItem(QString::fromStdString(restaurant->get_orders()[position]->get_ordered_dishes()[i].get_name()));
    }
    ui->orderStack->setCurrentIndex(2);

}

void MainWindow::on_modifyDeliveryAddress_clicked(){
    size_t position = ui->orderList->currentRow();
    ChangeAddressWindow chaw;
    chaw.set_current_address(
        QString::fromStdString((restaurant->get_orders()[position]->get_delivery_address().get_street())),
        QString::fromStdString((restaurant->get_orders()[position]->get_delivery_address().get_building())),
        QString::fromStdString((restaurant->get_orders()[position]->get_delivery_address().get_city())),
        QString::fromStdString((restaurant->get_orders()[position]->get_delivery_address().get_postal_code()))
    );
    chaw.setModal(true);
    if (chaw.exec() == QDialog::Accepted)
    {

        std::string city = (chaw.get_city().toStdString());
        std::string street = (chaw.get_street().toStdString());
        std::string building = (chaw.get_building().toStdString());
        std::string postal_code = (chaw.get_postal_code().toStdString());
        restaurant->get_orders()[position]->get_delivery_address().set_city(city);
        restaurant->get_orders()[position]->get_delivery_address().set_street(street);
        restaurant->get_orders()[position]->get_delivery_address().set_building(building);
        restaurant->get_orders()[position]->get_delivery_address().set_postal_code(postal_code);
        ui->orderDelivery->setText(QString::fromStdString(restaurant->get_orders()[position]->get_delivery_address().to_string()));
    }


}

void MainWindow::on_addDishDeliveryOrder_clicked(){
    AddDish ad;
    ad.setModal(true);
    ad.exec();
}

void MainWindow::on_removeDeliveryOrder_clicked(){
    int order_position = ui->orderList->currentRow();
    std::cout << order_position;
    if(order_position != -1){
        restaurant->remove_delivery_order(order_position);
        ui->orderStack->setCurrentIndex(1);
        ui->orderList->clear();
        for(unsigned int i=0; i<restaurant->get_orders().size(); i++){
            ui->orderList->addItem(QString::number(restaurant->get_orders()[i]->get_order_id()));
    }
    }
}

void MainWindow::on_addOrder_clicked(){
    AddOrder ao;
    ao.setModal(true);
    ao.exec();
}