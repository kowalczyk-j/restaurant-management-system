#include "../add_dish/adddish.h"
#include "../add_order/addorder.h"
#include "../main_window/mainwindow.h"
#include "../add_employee/addemployee.h"
#include "../change_address/changeaddresswindow.h"
#include "../change_name/changename.h"
#include "../change_surname/changesurname.h"
#include "../change_id/changeid.h"
#include "../change_salary/changesalary.h"
#include "../add_product/addproduct.h"
#include "../change_category/changecategory.h"
#include "../add_ingridient/addingridient.h"
#include "../add_menu_dish/addmenudish.h"
#include "../add_onsite_order/addosorder.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QStringList>
#include <QQuickItem>
#include <QString>
#include <QObject>
#include <QUrl>
#include <string>
#include <iostream>
#include <json/json.h>
#include <fstream>
#include <vector>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    ifstream ifs("file.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    Restaurant r1 = Restaurant::parse_from_json(obj);


    Product p = Product("Jabłko",670, g);
    Product p1 = Product("Mięso",500, g);
    Product p2 = Product("Sok Jabłkowy",1000, ml);
    Product p3 = Product("jajka",60, szt);
    Product p4  = Product("koperek",100, g);
    Product p5 = Product("ziemniaki",4000, g);

    Pantry pan;
    string s;
    pan.add_product("Jabłko", 6, g,  s);
    pan.add_product("Mięso",500, g, s);
    pan.add_product("Sok Jabłkowy",1000, ml, s);

    Addres a1 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.220154, 21.011968);
    Addres a2 = Addres( "Warszawa", "00-000", "Plac Politechniki", "1", "Polska", "Mazowieckie", 52.216184, 20.239073);
    std::vector< Product> map = {p};
    Dish d1 = Dish("zupa pomidorowa", przystawka, Money(500), 1, map);
    std::vector<Dish> dishes;
    dishes.push_back(d1);
    Menu m = Menu(dishes);
    Cook c = Cook(1, "Adam", "Wiśniewski", a1, Money(800000), 0);
    Waiter w = Waiter(2, "Alicja", "Polska", a1, Money(800000));
    Deliverer d = Deliverer(3, "Tomasz", "Niewierny", a1, Money(800000));
    Manager man = Manager(4, "Jan", "Nowak", a1, Money(800000));
    std::vector<Cook> vc;
    std::vector<Manager> vm;
    std::vector<Deliverer> vd;
    std::vector<Waiter> vw;
    vc.push_back(c);
    vw.push_back(w);
    vm.push_back(man);
    vd.push_back(d);


    DeliveryOrder os = DeliveryOrder(1, dishes, a1, 10);
    std::vector<DeliveryOrder> vde;
    std::vector<OnSiteOrder> vso;
    vde.push_back(os);
    //Restaurant r1 =  Restaurant(1, "Magnoliowa", a1, pan, m, vc, vd, vm, vw, vde, vso);
    Restaurant r2 =  Restaurant(2, "Różana", a2, pan, m, vc, vd, vm, vw, vde, vso);

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
    else{
        ui->restaurantStack->setCurrentIndex(0);
        ui->employeesNumber->setText(QString::number(restaurant->get_emoployee_number()));
        ui->ordersNumber->setText(QString::number(restaurant->get_orders_number()));
        ui->menuPositionsNumber->setText(QString::number(restaurant->get_menu().size()));
    }

}
void MainWindow::on_selectRestaurant_clicked(){
    if (ui->list1->currentRow() != -1){
        restaurant = & restaurant_list[ui->list1->currentRow()];

        QObject *object = ui->mapa->rootObject();
        object->setProperty("latitude", restaurant->get_address().get_latitude());
        object->setProperty("longitude", restaurant->get_address().get_longitude());

        ui->image->setPixmap(QString::fromStdString("rsc/"+restaurant->get_name()+".jpg"));
        ui->restaurantAddress->setText(QString::fromStdString(restaurant->get_address().to_string()));
        ui->restaurationName->setText(QString::fromStdString(restaurant->get_name()));
        ui->employeesNumber->setText(QString::number(restaurant->get_emoployee_number()));
        ui->ordersNumber->setText(QString::number(restaurant->get_orders_number()));
        ui->menuPositionsNumber->setText(QString::number(restaurant->get_menu().size()));

        ui->orderList->clear();
        ui->pantryList->clear();
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_pantry().get_all_products().size(); i++){
            ui->pantryList->addItem(QString::fromStdString(restaurant->get_pantry().get_all_products()[i]));
        }
        ui->menuList->clear();
        for(unsigned int i=0; i<restaurant->get_menu().get_dishes().size(); i++){
            ui->menuList->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[i].get_name()));
        }
        ui->mainStack->setCurrentIndex(1);
    }
}
void MainWindow::on_movePantry_clicked(){
    ui->restaurantStack->setCurrentIndex(1);
    ui->pantryStack->setCurrentIndex(1);
}
void MainWindow::on_moveEmployee_clicked(){
    ui->employeeList->clear();
    ui->restaurantStack->setCurrentIndex(2);
    ui->employeeStack->setCurrentIndex(1);
    position1 = ui->selectRole->currentIndex();
    ui->selectRole->setCurrentIndex(1);
    ui->selectRole->setCurrentIndex(0);
}
void MainWindow::on_moveMenu_clicked(){
    ui->restaurantStack->setCurrentIndex(3);
    ui->menuStack->setCurrentIndex(1);
}
void MainWindow::on_moveOrders_clicked(){
    ui->orderType->setCurrentIndex(1);
    ui->orderType->setCurrentIndex(0);
    ui->restaurantStack->setCurrentIndex(4);
    ui->orderStack->setCurrentIndex(1);
}

void MainWindow::on_selectRole_currentIndexChanged(){
    ui->employeeList->clear();
    ui->employeeStack->setCurrentIndex(1);
    position1 = ui->selectRole->currentIndex();
    if(position1 == 0){
        for(unsigned int i=0; i<restaurant->get_cooks().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_cooks()[i].get_name() + " " + restaurant->get_cooks()[i].get_surname() + " (" + to_string(restaurant->get_cooks()[i].get_employee_id()) + ")"));
        }
    }
    else if(position1 == 1){
        for(unsigned int i=0; i<restaurant->get_deliverers().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_deliverers()[i].get_name() + " " + restaurant->get_deliverers()[i].get_surname() + " (" + to_string(restaurant->get_deliverers()[i].get_employee_id()) + ")"));
        }
    }
    else if(position1 == 2){
        for(unsigned int i=0; i<restaurant->get_managers().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_managers()[i].get_name() + " " + restaurant->get_managers()[i].get_surname() + " (" + to_string(restaurant->get_managers()[i].get_employee_id()) + ")"));
        }
    }
    else {
        for(unsigned int i=0; i<restaurant->get_waiters().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_waiters()[i].get_name() + " " + restaurant->get_waiters()[i].get_surname() + " (" + to_string(restaurant->get_waiters()[i].get_employee_id()) + ")"));
        }
    }
}

void MainWindow::on_orderType_currentIndexChanged(){
        position1 = ui->orderType->currentIndex();
        ui->orderStack->setCurrentIndex(1);
        ui->orderList->clear();
        if(position1==0){
            for(unsigned int i=0; i<restaurant->get_delivery_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+to_string(restaurant->get_delivery_orders()[i].get_order_id())));
            }
        }
        else {
            for(unsigned int i=0; i<restaurant->get_onsite_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+to_string(restaurant->get_onsite_orders()[i].get_order_id())));
            }
        }
}

void MainWindow::on_orderList_itemClicked(){
    ui->orderedDishes->clear();
    size_t position = ui->orderList->currentRow();
    if(position1==0){
        ui->orderNumber->setText(QString::fromStdString("#"+to_string(restaurant->get_delivery_orders()[position].get_order_id())));
        ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_delivery_orders()[position].get_order_value().to_string()));
        ui->orderDelivery->setText(QString::fromStdString(restaurant->get_delivery_orders()[position].get_delivery_address().to_string()));
        for(unsigned int i=0; i<restaurant->get_delivery_orders()[position].get_ordered_dishes().size(); i++){
            ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_delivery_orders()[position].get_ordered_dishes()[i].get_name()));
        }
        ui->orderTypeStack->setCurrentIndex(0);
    }
    else{
        ui->orderNumber->setText(QString::fromStdString("#"+to_string(restaurant->get_onsite_orders()[position].get_order_id())));
        ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_onsite_orders()[position].get_order_value().to_string()));
        for(unsigned int i=0; i<restaurant->get_onsite_orders()[position].get_ordered_dishes().size(); i++){
            ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_onsite_orders()[position].get_ordered_dishes()[i].get_name()));
        }
        ui->orderTypeStack->setCurrentIndex(1);
    }

    ui->orderStack->setCurrentIndex(0);


}

void MainWindow::on_modifyDeliveryAddress_clicked(){
    size_t position = ui->orderList->currentRow();
    ChangeAddress chaw;
    chaw.set_current_address(
        QString::fromStdString((restaurant->get_delivery_orders()[position].get_delivery_address().get_street())),
        QString::fromStdString((restaurant->get_delivery_orders()[position].get_delivery_address().get_building())),
        QString::fromStdString((restaurant->get_delivery_orders()[position].get_delivery_address().get_city())),
        QString::fromStdString((restaurant->get_delivery_orders()[position].get_delivery_address().get_postal_code()))
    );
    chaw.setModal(true);
    if (chaw.exec() == QDialog::Accepted)
    {
        std::string city = (chaw.get_city().toStdString());
        std::string street = (chaw.get_street().toStdString());
        std::string building = (chaw.get_building().toStdString());
        std::string postal_code = (chaw.get_postal_code().toStdString());
        restaurant->get_delivery_orders()[position].get_delivery_address().set_city(city);
        restaurant->get_delivery_orders()[position].get_delivery_address().set_street(street);
        restaurant->get_delivery_orders()[position].get_delivery_address().set_building(building);
        restaurant->get_delivery_orders()[position].get_delivery_address().set_postal_code(postal_code);
        ui->orderDelivery->setText(QString::fromStdString(restaurant->get_delivery_orders()[position].get_delivery_address().to_string()));
    }


}

void MainWindow::on_addDishOrder_clicked(){
    int order_position = ui->orderList->currentRow();
    AddDish ad;
    ad.set_menu(restaurant->get_menu());
    ad.setModal(true);
    if(ad.exec() == QDialog::Accepted){
        if(position1==0){
            restaurant->get_delivery_orders()[order_position].add_dish(ad.get_dish());
            ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_delivery_orders()[order_position].get_order_value().to_string()));
            ui->orderedDishes->clear();
            for(unsigned int i=0; i<restaurant->get_delivery_orders()[order_position].get_ordered_dishes().size(); i++){
                ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_delivery_orders()[order_position].get_ordered_dishes()[i].get_name()));
            }
        }
        else{
            restaurant->get_onsite_orders()[order_position].add_dish(ad.get_dish());
        }
    }
}

void MainWindow::on_removeOrder_clicked(){
    int order_position = ui->orderList->currentRow();
    ui->orderStack->setCurrentIndex(1);
    ui->orderList->clear();
    if(order_position != -1){
        restaurant->remove_delivery_order(order_position);
        for(unsigned int i=0; i<restaurant->get_delivery_orders().size(); i++){
            ui->orderList->addItem(QString::fromStdString("#"+ to_string(restaurant->get_delivery_orders()[i].get_order_id())));
        }
    }
    else{
        restaurant->remove_on_site_order(order_position);
        for(unsigned int i=0; i<restaurant->get_onsite_orders().size(); i++){
            ui->orderList->addItem(QString::fromStdString("#"+ to_string(restaurant->get_onsite_orders()[i].get_order_id())));
        }
    }
}

void MainWindow::on_addOrderD_clicked(){
    AddOrder ao;
    ao.setModal(true);
    ao.set_menu(restaurant->get_menu());
    if(ao.exec() == QDialog::Accepted){
        restaurant->add_delivery_order(ao.get_number().toInt(), ao.get_orderedDishes(), Addres(ao.get_city().toStdString(), ao.get_postal_code().toStdString(), ao.get_street().toStdString(), ao.get_building().toStdString()), 0);
        if(position1 == 0){
            ui->orderList->clear();
            for(unsigned int i=0; i<restaurant->get_delivery_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+ to_string(restaurant->get_delivery_orders()[i].get_order_id())));
            }
        }
    }
}

void MainWindow::on_addOrderOS_clicked(){
    AddOsOrder ao;
    ao.setModal(true);
    ao.set_menu(restaurant->get_menu());
    if(ao.exec() == QDialog::Accepted){
        restaurant->add_on_site_order(ao.get_number().toInt(), ao.get_orderedDishes(), ao.get_table_id().toInt(), 0);
        if(position1 == 1){
            ui->orderList->clear();
            for(unsigned int i=0; i<restaurant->get_onsite_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+ to_string(restaurant->get_onsite_orders()[i].get_order_id())));
            }
        }
    }
}



void MainWindow::on_pantryList_itemClicked(){
    std::string product = restaurant->get_pantry().get_all_products()[ui->pantryList->currentRow()];
    ui->productName->setText(QString::fromStdString(product));
    ui->allergens->setText(QString::fromStdString(restaurant->get_pantry().get_product(product).get_allergen()));
    ui->unit->setText(QString::fromStdString(restaurant->get_pantry().get_product(product).get_unit()));
    ui->pantryStack->setCurrentIndex(0);
    ui->quantity->setText(QString::fromStdString(std::to_string(restaurant->get_pantry().get_product(product).get_quantity())+" "+restaurant->get_pantry().get_product(product).get_unit()));
}

void MainWindow::on_addProduct_clicked(){
    AddProduct ap;
    ap.setModal(true);
    if(ap.exec() == QDialog::Accepted){
        restaurant->get_pantry().add_product(ap.get_name().toStdString(), ap.get_quantity(), (units)ap.get_unit(), ap.get_allergens().toStdString());
    }
    ui->pantryList->clear();
    for(unsigned int i=0; i<restaurant->get_pantry().get_all_products().size(); i++){
            ui->pantryList->addItem(QString::fromStdString(restaurant->get_pantry().get_all_products()[i]));
    }
}

void MainWindow::on_addQuantitytoProduct_clicked(){
    std::string product = restaurant->get_pantry().get_all_products()[ui->pantryList->currentRow()];
    int quantity = ui->addQuantity->value();
    restaurant->get_pantry().add_quantity(product, quantity);
    ui->quantity->setText(QString::fromStdString(std::to_string(restaurant->get_pantry().get_product(product).get_quantity())+" "+restaurant->get_pantry().get_product(product).get_unit()));
    ui->addQuantity->setValue(0);
}


void MainWindow::on_removeQuantityfromProduct_clicked(){
    std::string product = restaurant->get_pantry().get_all_products()[ui->pantryList->currentRow()];
    int quantity = ui->addQuantity->value();
    restaurant->get_pantry().remove_quantity(product, quantity);
    ui->quantity->setText(QString::fromStdString(std::to_string(restaurant->get_pantry().get_product(product).get_quantity())+" "+restaurant->get_pantry().get_product(product).get_unit()));
    ui->addQuantity->setValue(0);
}

void MainWindow::on_removeProduct_clicked(){
    std::string product = restaurant->get_pantry().get_all_products()[ui->pantryList->currentRow()];
    restaurant->get_pantry().remove_product(product);
    ui->pantryStack->setCurrentIndex(1);
    ui->pantryList->clear();
    for(unsigned int i=0; i<restaurant->get_pantry().get_all_products().size(); i++){
            ui->pantryList->addItem(QString::fromStdString(restaurant->get_pantry().get_all_products()[i]));
    }
}


void MainWindow::on_employeeList_itemClicked(){
    position2 = ui->employeeList->currentRow();
    Employee e;
    if(position1 == 0){e = restaurant->get_cooks()[position2];}
    else if(position1 == 1){e = restaurant->get_deliverers()[position2];}
    else if(position1 == 2){e = restaurant->get_managers()[position2];}
    else {e = restaurant->get_waiters()[position2];}
    ui->position->setText(ui->selectRole->currentText());
    ui->employeeStack->setCurrentIndex(0);
    ui->titleName->setText(QString::fromStdString(e.get_name() + " " + e.get_surname()));
    ui->name->setText(QString::fromStdString(e.get_name()));
    ui->surname->setText(QString::fromStdString(e.get_surname()));
    ui->id->setText(QString::number(e.get_employee_id()));
    ui->address->setText(QString::fromStdString(""));
    ui->email->setText(QString::fromStdString(""));
    ui->salary->setText(QString::fromStdString(e.get_salary().to_string()));
}

void MainWindow::on_addEmployee_clicked(){
    AddEmployee ae;
    ae.setModal(true);
    if(ae.exec() == QDialog::Accepted){
        Addres a = Addres(ae.get_city().toStdString(), ae.get_postal_code().toStdString(), ae.get_street().toStdString(), ae.get_building().toStdString());
        Money m = Money(ae.get_salary_zlotys().toInt(), ae.get_salary_grosze().toInt());
        restaurant->add_and_check_employee_id(ae.get_id().toInt());
        if(ae.get_role_index() == 0){
            Cook c = Cook(ae.get_id().toInt(), ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m, 0);
            restaurant->get_cooks().employ(c);
            ui->employeeList->clear();
            if(position1 == 0){
                for(unsigned int i=0; i<restaurant->get_cooks().size(); i++){
                    ui->employeeList->addItem(QString::fromStdString(restaurant->get_cooks()[i].get_name() + " " + restaurant->get_cooks()[i].get_surname() + " (" + to_string(restaurant->get_cooks()[i].get_employee_id()) + ")"));
                }
            }

        }
        else if(ae.get_role_index() == 1){
            Deliverer d = Deliverer(ae.get_id().toInt(), ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
            restaurant->get_deliverers().employ(d);
            if(position1 == 1){
                for(unsigned int i=0; i<restaurant->get_deliverers().size(); i++){
                    ui->employeeList->addItem(QString::fromStdString(restaurant->get_deliverers()[i].get_name() + " " + restaurant->get_deliverers()[i].get_surname() + " (" + to_string(restaurant->get_deliverers()[i].get_employee_id()) + ")"));
                }
            }
        }
        else if(ae.get_role_index() == 2){
            Manager man = Manager(ae.get_id().toInt(), ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
            restaurant->get_managers().employ(man);
            ui->employeeList->clear();
            if(position1 == 2){
                for(unsigned int i=0; i<restaurant->get_managers().size(); i++){
                    ui->employeeList->addItem(QString::fromStdString(restaurant->get_managers()[i].get_name() + " " + restaurant->get_managers()[i].get_surname() + " (" + to_string(restaurant->get_managers()[i].get_employee_id()) + ")"));
                }
            }
        }
        else {
            Waiter w = Waiter(ae.get_id().toInt(), ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
            restaurant->get_waiters().employ(w);
            if(position1 == 3){
                for(unsigned int i=0; i<restaurant->get_waiters().size(); i++){
                    ui->employeeList->addItem(QString::fromStdString(restaurant->get_waiters()[i].get_name() + " " + restaurant->get_waiters()[i].get_surname() + " (" + to_string(restaurant->get_waiters()[i].get_employee_id()) + ")"));
                }
            }
        }
    }
}

void MainWindow::on_modifyName_clicked(){
    ChangeName chn;
    chn.set_name(ui->name->text());
    chn.setModal(true);
    if(chn.exec() == QDialog::Accepted){
        if(position1 == 0){restaurant->get_cooks()[position2].set_name(chn.get_name().toStdString());}
        else if(position1 == 1){restaurant->get_deliverers()[position2].set_name(chn.get_name().toStdString());}
        else if(position1 == 2){restaurant->get_managers()[position2].set_name(chn.get_name().toStdString());}
        else {restaurant->get_waiters()[position2].set_name(chn.get_name().toStdString());}
    }
    ui->name->setText(chn.get_name());
}

//można kiedyś dodaćprzeładowyanie listy
void MainWindow::on_modifySurname_clicked(){
    ChangeSurname chs;
    chs.set_surname(ui->surname->text());
    chs.setModal(true);
    if(chs.exec() == QDialog::Accepted){
        if(position1 == 0){restaurant->get_cooks()[position2].set_surname(chs.get_surnname().toStdString());}
        else if(position1 == 1){restaurant->get_deliverers()[position2].set_surname(chs.get_surnname().toStdString());}
        else if(position1 == 2){restaurant->get_managers()[position2].set_surname(chs.get_surnname().toStdString());}
        else {restaurant->get_waiters()[position2].set_surname(chs.get_surnname().toStdString());}
    }
    ui->surname->setText(chs.get_surnname());
}
void MainWindow::on_modifyId_clicked(){
    ChangeId chi;
    chi.set_id(ui->id->text());
    chi.setModal(true);
    if(chi.exec() == QDialog::Accepted){
        restaurant->add_and_check_employee_id(chi.get_id().toInt());
        if(position1 == 0){restaurant->get_cooks()[position2].set_employee_id(chi.get_id().toInt());}
        else if(position1 == 1){restaurant->get_deliverers()[position2].set_employee_id(chi.get_id().toInt());}
        else if(position1 == 2){restaurant->get_managers()[position2].set_employee_id(chi.get_id().toInt());}
        else {restaurant->get_waiters()[position2].set_employee_id(chi.get_id().toInt());}
    }
    ui->id->setText(chi.get_id());
}
void MainWindow::on_modifySalary_clicked(){

    Employee & e =  get_employee_refernece();
    ChangeSalary chs;
    chs.set_salary(QString::number(e.get_salary().get_zlotys()), QString::number(e.get_salary().get_cents()));
    chs.setModal(true);
    if(chs.exec() == QDialog::Accepted){
        Money m = Money(chs.get_salary_zlotys().toInt(), chs.get_salary_grosze().toInt());
        if(position1 == 0){restaurant->get_cooks()[position2].set_salary(m);}
        else if(position1 == 1){restaurant->get_deliverers()[position2].set_salary(m);}
        else if(position1 == 2){restaurant->get_managers()[position2].set_salary(m);}
        else {restaurant->get_waiters()[position2].set_salary(m);}
    }
    ui->salary->setText(QString::fromStdString(e.get_salary().to_string()));

}

void MainWindow::on_removeEmployee_clicked(){
    if(position1 == 0){
        restaurant->remove_emoloyee_id(restaurant->get_cooks()[position2].get_employee_id());
        restaurant->get_cooks().fire(position2);
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_cooks().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_cooks()[i].get_name() + " " + restaurant->get_cooks()[i].get_surname() + " (" + to_string(restaurant->get_cooks()[i].get_employee_id()) + ")"));
        }
    }
    else if(position1 == 1){
        restaurant->remove_emoloyee_id(restaurant->get_deliverers()[position2].get_employee_id());
        restaurant->get_deliverers().fire(position2);
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_deliverers().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_deliverers()[i].get_name() + " " + restaurant->get_deliverers()[i].get_surname() + " (" + to_string(restaurant->get_deliverers()[i].get_employee_id()) + ")"));
        }
    }
    else if(position1 == 2){
        restaurant->remove_emoloyee_id(restaurant->get_managers()[position2].get_employee_id());
        restaurant->get_managers().fire(position2);
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_managers().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_managers()[i].get_name() + " " + restaurant->get_managers()[i].get_surname() + " (" + to_string(restaurant->get_managers()[i].get_employee_id()) + ")"));
        }
    }
    else {
        restaurant->remove_emoloyee_id(restaurant->get_waiters()[position2].get_employee_id());
        restaurant->get_waiters().fire(position2);
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_waiters().size(); i++){
            ui->employeeList->addItem(QString::fromStdString(restaurant->get_waiters()[i].get_name() + " " + restaurant->get_waiters()[i].get_surname() + " (" + to_string(restaurant->get_waiters()[i].get_employee_id()) + ")"));
        }
    }
    ui->employeeStack->setCurrentIndex(1);
}

void MainWindow::on_menuList_itemClicked(){

    position1 = ui->menuList->currentRow();
    ui->menuStack->setCurrentIndex(0);
    ui->dishName->setText(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_name()));
    ui->Price->setText(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_price().to_string()));
    ui->Category->setText(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_dish_type()));
    ui->DishIngrdidients->clear();
    for(size_t i=0; i<restaurant->get_menu().get_dishes()[position1].get_ingredients().size(); i++){
            ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_name()+" ("+to_string(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_quantity())+restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_unit() +")"));
        }

}

void MainWindow::on_modifyPrice_clicked(){
    ChangeSalary mp;
    mp.setModal(true);
    mp.set_salary(QString::number(restaurant->get_menu().get_dishes()[position1].get_price().get_zlotys()), QString::number(restaurant->get_menu().get_dishes()[position1].get_price().get_cents()));
    if(mp.exec() == QDialog::Accepted){
        restaurant->get_menu().get_dishes()[position1].set_price(Money(mp.get_salary_zlotys().toInt(), mp.get_salary_grosze().toInt()));
    }
    ui->Price->setText(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_price().to_string()));
}

void MainWindow::on_modifyCategory_clicked(){
    ChangeCategory cc;
    cc.setModal(true);
    if(cc.exec() == QDialog::Accepted){
        std::cout << cc.get_category();
        restaurant->get_menu().get_dishes()[position1].set_dish_type((dish_type) cc.get_category());
        ui->Category->setText(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_dish_type()));
    }
}

void MainWindow::on_addIngridient_clicked(){
    AddIng ac;
    ac.setModal(true);
    ac.set_products(restaurant->get_pantry());
    if(ac.exec() == QDialog::Accepted){
        restaurant->get_menu().get_dishes()[position1].add_ingiridnet(ac.get_ing());
        ui->DishIngrdidients->clear();
        for(size_t i=0; i<restaurant->get_menu().get_dishes()[position1].get_ingredients().size(); i++){
            ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_name()+" ("+to_string(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_quantity())+restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_unit() +")"));
        }
    }
}

void MainWindow::on_removeIngridient_clicked(){
    position2 = ui->DishIngrdidients->currentRow();
    if(position2 != -1){
        restaurant->get_menu().get_dishes()[position1].remove_ingridient(position2);
        ui->DishIngrdidients->setCurrentRow(-1);
        ui->DishIngrdidients->clear();
        for(size_t i=0; i<restaurant->get_menu().get_dishes()[position1].get_ingredients().size(); i++){
            ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_name()+" ("+to_string(restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_quantity())+restaurant->get_menu().get_dishes()[position1].get_ingredients()[i].get_unit() +")"));
        }
    }
}

void MainWindow::on_addMenuDish_clicked(){
    AddMenuDish amd;
    amd.set_pantry(restaurant->get_pantry());
    if(amd.exec() == QDialog::Accepted){
        Dish dish_to_add = Dish(amd.get_name().toStdString(), (dish_type) amd.get_category(), Money(amd.get_zlotys().toInt(), amd.get_grosze().toInt()), amd.get_vegan(), amd.get_ing());
        restaurant->get_menu().add_dish(dish_to_add);
        ui->menuList->clear();
        for(unsigned int i=0; i<restaurant->get_menu().get_dishes().size(); i++){
            ui->menuList->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[i].get_name()));
        }
    }

}

void MainWindow::on_removeMenuDish_clicked(){
    restaurant->get_menu().remove_dish(position1);
    ui->menuStack->setCurrentIndex(1);
    ui->menuList->clear();
    for(unsigned int i=0; i<restaurant->get_menu().get_dishes().size(); i++){
        ui->menuList->addItem(QString::fromStdString(restaurant->get_menu().get_dishes()[i].get_name()));
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
    std::ofstream file;
    file.open("file.json");

    Json::Value res;
    res = restaurant->parse_to_json();
    Json::StyledWriter styledWriter;
    file << styledWriter.write(res);

    file.close();
}


Employee & MainWindow::get_employee_refernece(){
    if(position1 == 0){return restaurant->get_cooks()[position2];}
    else if(position1 == 1){return restaurant->get_deliverers()[position2];}
    else if(position1 == 2){return restaurant->get_managers()[position2];}
    else {return restaurant->get_waiters()[position2];}
}