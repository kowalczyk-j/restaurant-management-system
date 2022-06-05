#include "../add_dish/adddish.h"
#include "../add_order/addorder.h"
#include "../main_window/mainwindow.h"
#include "../add_employee/addemployee.h"
#include "../change_address/changeaddresswindow.h"
#include "../change_name/changename.h"
#include "../change_surname/changesurname.h"
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
#include <QMessageBox>
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

    /*
    ifstream ifs("file.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    Restaurant r1 = Restaurant::parse_from_json(obj);
*/
    Restaurant r1(0, "Magnoliowa", Addres("Warszawa", "00-000", "Plac Politechniki", "8", "Polska", "Mazowieckie", 102, 35));
    Restaurant r2(1, "Różana", Addres("Toruń", "87-100", "Szeroka", "10", "Polska", "Kujawsko-Pomorskie", 23, -34));
    restaurant_list.push_back(r1);
    restaurant_list.push_back(r2);

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
        ui->ordersNumber->setText(QString::number(restaurant->get_active_orders_number()));
        ui->menuPositionsNumber->setText(QString::number(restaurant->get_dishes_number()));
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
        ui->ordersNumber->setText(QString::number(restaurant->get_active_orders_number()));
        ui->menuPositionsNumber->setText(QString::number(restaurant->get_dishes_number()));

        ui->orderList->clear();
        ui->pantryList->clear();
        ui->employeeList->clear();

        ui->menuList->clear();

        ui->mainStack->setCurrentIndex(1);
    }
}
void MainWindow::on_movePantry_clicked(){
    ui->pantryList->clear();
    for(unsigned int i=0; i<restaurant->get_all_prodcucts().size(); i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_prodcucts()[i]->get_name()),
                                                   ui->pantryList,
                                                   restaurant->get_all_prodcucts()[i]->get_id());
    }
    ui->restaurantStack->setCurrentIndex(1);
    ui->pantryStack->setCurrentIndex(1);
}
void MainWindow::on_moveEmployee_clicked(){
    ui->employeeList->clear();
    ui->restaurantStack->setCurrentIndex(2);
    ui->employeeStack->setCurrentIndex(1);
    position1 = ui->selectRole->currentIndex();
    for(unsigned int i=0; i<restaurant->get_all_employees().size(); i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_employees()[i]->get_name() + " " + restaurant->get_all_employees()[i]->get_surname() + " (" + to_string(restaurant->get_all_employees()[i]->get_id()) + ")"),
                                                   ui->employeeList,
                                                   restaurant->get_all_employees()[i]->get_id());
    }
}
void MainWindow::on_moveMenu_clicked(){
    ui->menuList->clear();
    for(unsigned int i=0; i<restaurant->get_all_dishes().size() ; i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_dishes()[i]->get_name()),
                                                   ui->menuList,
                                                   restaurant->get_all_dishes()[i]->get_id());
        }
    ui->restaurantStack->setCurrentIndex(3);
    ui->menuStack->setCurrentIndex(1);
}
void MainWindow::on_moveOrders_clicked(){
    ui->orderList->clear();
    for(unsigned int i=0; i<restaurant->get_all_active_orders().size(); i++){
        new QListWidgetItem(QString::fromStdString("#"+to_string(restaurant->get_all_active_orders()[i]->get_id())),
                                                   ui->orderList,
                                                   restaurant->get_all_active_orders()[i]->get_id());
    }
    ui->restaurantStack->setCurrentIndex(4);
    ui->orderStack->setCurrentIndex(1);
}

void MainWindow::on_generateMenu_clicked(){
    if(restaurant->get_dishes_number() > 3){
        restaurant->generate_lunch_menu();
    }
}

void MainWindow::on_orderType_currentIndexChanged(){
        position1 = ui->orderType->currentIndex();
        ui->orderStack->setCurrentIndex(1);
        /* TODO
        ui->orderList->clear();
        if(position1==0){
            for(unsigned int i=0; i<restaurant->get_delivery_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+to_string(restaurant->get_delivery_orders()[i].get_id())));
            }
        }
        else {
            for(unsigned int i=0; i<restaurant->get_onsite_orders().size(); i++){
                ui->orderList->addItem(QString::fromStdString("#"+to_string(restaurant->get_onsite_orders()[i].get_id())));
            }
        }*/
}

void MainWindow::on_orderList_itemClicked(){
    current_id = ui->orderList->currentItem()->type();
    BaseOrder * order = restaurant->get_active_order(current_id);
    ui->orderedDishes->clear();
    ui->orderNumber->setText(QString::fromStdString("#"+to_string(current_id)));
    ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_active_order_value(current_id).to_string()));
    for(unsigned int i=0; i<order->get_ordered_dishes().size(); i++){
            ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_dish(order->get_ordered_dishes()[i])->get_name()));
    }
    if(order->get_order_type()==0){
        ui->orderDelivery->setText(QString::fromStdString(order->get_delivery_address().to_string()));
        ui->orderTypeStack->setCurrentIndex(0);
    }
    else{
        ui->orderTypeStack->setCurrentIndex(1);
    }
    ui->orderStack->setCurrentIndex(0);


}

void MainWindow::on_modifyDeliveryAddress_clicked(){
    BaseOrder * order = restaurant->get_active_order(current_id);

    ChangeAddress chaw;
    chaw.set_current_address(
        QString::fromStdString((order->get_delivery_address().get_street())),
        QString::fromStdString((order->get_delivery_address().get_building())),
        QString::fromStdString((order->get_delivery_address().get_city())),
        QString::fromStdString((order->get_delivery_address().get_postal_code()))
    );
    chaw.setModal(true);
    if (chaw.exec() == QDialog::Accepted)
    {
        std::string city = (chaw.get_city().toStdString());
        std::string street = (chaw.get_street().toStdString());
        std::string building = (chaw.get_building().toStdString());
        std::string postal_code = (chaw.get_postal_code().toStdString());
        order->get_delivery_address().set_city(city);
        order->get_delivery_address().set_street(street);
        order->get_delivery_address().set_building(building);
        order->get_delivery_address().set_postal_code(postal_code);
        ui->orderDelivery->setText(QString::fromStdString(order->get_delivery_address().to_string()));
    }

}

void MainWindow::on_removeDishOrder_clicked(){
    BaseOrder * order = restaurant->get_active_order(current_id);
    position1 = ui->orderedDishes->currentRow();
    restaurant->remove_dish_from_order(order->get_id(), position1);
    ui->orderedDishes->clear();
    for(unsigned int i=0; i<order->get_ordered_dishes().size(); i++){
        ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_dish(order->get_ordered_dishes()[i])->get_name()));
    }
}

void MainWindow::on_addDishOrder_clicked(){
    AddDish ad(*restaurant);
    BaseOrder * order = restaurant->get_active_order(current_id);
    ad.setModal(true);
    if(ad.exec() == QDialog::Accepted){
        try{
            restaurant->add_dish_to_order(order->get_id(), ad.get_dish_id());
            ui->orderTotalPrice->setText(QString::fromStdString(restaurant->get_active_order_value(current_id).to_string()));
            ui->orderedDishes->clear();
            for(unsigned int i=0; i<order->get_ordered_dishes().size(); i++){
                ui->orderedDishes->addItem(QString::fromStdString(restaurant->get_dish(order->get_ordered_dishes()[i])->get_name()));
            }
        }
        catch(restaurant_exception e){
            QMessageBox msgBox;
            msgBox.setText("Brak wystarczające ilości składników do realizacji zamówienia");
            msgBox.setWindowTitle("Nie można dodać!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }

    }
}

void MainWindow::on_removeOrder_clicked(){
    ui->orderStack->setCurrentIndex(1);
    ui->orderList->clear();
    restaurant->remove_active_order(current_id);
    for(unsigned int i=0; i<restaurant->get_all_active_orders().size(); i++){
        new QListWidgetItem(QString::fromStdString("#"+to_string(restaurant->get_all_active_orders()[i]->get_id())),
                            ui->orderList,
                            restaurant->get_all_active_orders()[i]->get_id());
    }
}

void MainWindow::on_addOrderD_clicked(){
    AddOrder ao(*restaurant);
    ao.setModal(true);
    if(ao.exec() == QDialog::Accepted){
        restaurant->add_delivery_order(ao.get_orderedDishes(), 0, Addres(ao.get_city().toStdString(), ao.get_postal_code().toStdString(), ao.get_street().toStdString(), ao.get_building().toStdString()));
        ui->orderList->clear();
        ui->orderType->setCurrentIndex(0);
        for(unsigned int i=0; i<restaurant->get_all_active_orders().size(); i++){
            new QListWidgetItem(QString::fromStdString("#"+to_string(restaurant->get_all_active_orders()[i]->get_id())),
                                ui->orderList,
                                restaurant->get_all_active_orders()[i]->get_id());
        }
    }
    else{
        for(auto dish:ao.get_orderedDishes()){
            for(auto ingredient:restaurant->get_dish(dish)->get_ingredients())
                restaurant->get_product(ingredient.stock_id)->release(ingredient.quantity);
        }
    }
}

void MainWindow::on_addOrderOS_clicked(){
    AddOsOrder ao(*restaurant);
    ao.setModal(true);
    if(ao.exec() == QDialog::Accepted){
        restaurant->add_on_site_order(ao.get_orderedDishes(), ao.get_table_id().toInt(), 0);
            ui->orderList->clear();
        for(unsigned int i=0; i<restaurant->get_all_active_orders().size(); i++){
            new QListWidgetItem(QString::fromStdString("#"+to_string(restaurant->get_all_active_orders()[i]->get_id())),
                                ui->orderList,
                                restaurant->get_all_active_orders()[i]->get_id());
        }
    }
    else{
        for(auto dish:ao.get_orderedDishes()){
            for(auto ingredient:restaurant->get_dish(dish)->get_ingredients())
                restaurant->get_product(ingredient.stock_id)->release(ingredient.quantity);
        }
    }
}

void MainWindow::on_markOrderAsDone_clicked(){
    restaurant->mark_order_as_done(current_id);
    ui->orderStack->setCurrentIndex(1);
    ui->orderList->clear();
    for(unsigned int i=0; i<restaurant->get_all_active_orders().size(); i++){
    new QListWidgetItem(QString::fromStdString("#"+to_string(restaurant->get_all_active_orders()[i]->get_id())),
                        ui->orderList,
                        restaurant->get_all_active_orders()[i]->get_id());
    }
}



void MainWindow::on_pantryList_itemClicked(){
    current_id = ui->pantryList->currentItem()->type();
    Product * product = restaurant->get_product(current_id);
    ui->productName->setText(QString::fromStdString(product->get_name()));
    ui->allergens->setText(QString::fromStdString(product->get_allergen()));
    ui->unit->setText(QString::fromStdString(product->get_unit()));
     ui->quantity->setText(QString::fromStdString(to_string(product->get_quantity())+" "+product->get_unit()));
    ui->pantryStack->setCurrentIndex(0);

}

void MainWindow::on_addProduct_clicked(){
    AddProduct ap;
    ap.setModal(true);
    if(ap.exec() == QDialog::Accepted){
        restaurant->add_product(ap.get_name().toStdString(), (units) ap.get_unit(), ap.get_allergens().toStdString(), ap.get_quantity());
    }
    ui->pantryList->clear();
    for(unsigned int i=0; i<restaurant->get_all_prodcucts().size(); i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_prodcucts()[i]->get_name()),
                                                   ui->pantryList,
                                                   restaurant->get_all_prodcucts()[i]->get_id());
    }
}

void MainWindow::on_addQuantitytoProduct_clicked(){
    Product * product = restaurant->get_product(current_id);
    int quantity = ui->addQuantity->value();
    *(product) += quantity;
    ui->quantity->setText(QString::fromStdString(to_string(product->get_quantity())+" "+product->get_unit()));
    ui->addQuantity->setValue(0);
}


void MainWindow::on_removeQuantityfromProduct_clicked(){
    Product * product = restaurant->get_product(current_id);
    int quantity = ui->addQuantity->value();
    *(product) -= quantity;
    ui->quantity->setText(QString::fromStdString(to_string(product->get_quantity())+" "+product->get_unit()));
    ui->addQuantity->setValue(0);
}

void MainWindow::on_removeProduct_clicked(){
    try{
        restaurant->remove_product(current_id);
        ui->pantryStack->setCurrentIndex(1);
        ui->pantryList->clear();
        for(unsigned int i=0; i<restaurant->get_all_prodcucts().size(); i++){
            new QListWidgetItem(QString::fromStdString(restaurant->get_all_prodcucts()[i]->get_name()),
                                                    ui->pantryList,
                                                    restaurant->get_all_prodcucts()[i]->get_id());
        }
    }
    catch(restaurant_exception e){
            QMessageBox msgBox;
            msgBox.setText("Produkt znajduje się w co najmniej jednym daniu w menu!");
            msgBox.setWindowTitle("Nie można usunąć!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
    }
}


void MainWindow::on_employeeList_itemClicked(){
    current_id = ui->employeeList->currentItem()->type();
    Employee * e = restaurant->get_employee(current_id);
    ui->employeeStack->setCurrentIndex(0);

    ui->position->setText(QString::fromStdString(e->get_position()));

    ui->titleName->setText(QString::fromStdString(e->get_name() + " " + e->get_surname()));
    ui->name->setText(QString::fromStdString(e->get_name()));
    ui->surname->setText(QString::fromStdString(e->get_surname()));
    ui->id->setText(QString::number(e->get_id()));
    ui->address->setText(QString::fromStdString(""));
    ui->email->setText(QString::fromStdString(""));
    ui->salary->setText(QString::fromStdString(e->get_salary().to_string()));
}

void MainWindow::on_selectRole_currentIndexChanged(){
/*
    ui->employeeList->clear();
    ui->employeeStack->setCurrentIndex(1);
    position1 = ui->selectRole->currentIndex();
    std::vector<Employee *> employees;
    if(position1 == 0){
        employees = restaurant->get_all_employees();
        for(unsigned int i=0; i<employees.size(); i++){
            new QListWidgetItem(QString::fromStdString(employees[i]->get_name() + " " + employees[i]->get_surname() + " (" + to_string(employees[i]->get_id()) + ")"),
                                ui->employeeList,
                                employees[i]->get_id());
        }
    }
    if(position1 == 1){
        employees = restaurant->get_all_cooks();
        for(size_t i=0; i<employees.size(); i++){
            new QListWidgetItem(QString::fromStdString(employees[i]->get_name() + " " + employees[i]->get_surname() + " (" + to_string(employees[i]->get_id()) + ")"),
                                ui->employeeList,
                                employees[i]->get_id());
        }
    }
    else if(position1 == 2){
        employees = restaurant->get_all_deliverers();
        for(size_t i=0; i<employees.size(); i++){
            new QListWidgetItem(QString::fromStdString(employees[i]->get_name() + " " + employees[i]->get_surname() + " (" + to_string(employees[i]->get_id()) + ")"),
                                ui->employeeList,
                                employees[i]->get_id());
        }
    }
    else if(position1 == 3){
        employees = restaurant->get_all_managers();
        for(size_t i=0; i<employees.size(); i++){
            new QListWidgetItem(QString::fromStdString(employees[i]->get_name() + " " + employees[i]->get_surname() + " (" + to_string(employees[i]->get_id()) + ")"),
                                ui->employeeList,
                                employees[i]->get_id());
        }
    }
    else {
        employees = restaurant->get_all_waiters();
        for(size_t i=0; i<employees.size(); i++){
            new QListWidgetItem(QString::fromStdString(employees[i]->get_name() + " " + employees[i]->get_surname() + " (" + to_string(employees[i]->get_id()) + ")"),
                                ui->employeeList,
                                employees[i]->get_id());
        }
    }
*/
}

void MainWindow::on_addEmployee_clicked(){
    AddEmployee ae;
    ae.setModal(true);
    if(ae.exec() == QDialog::Accepted){
        Addres a = Addres(ae.get_city().toStdString(), ae.get_postal_code().toStdString(), ae.get_street().toStdString(), ae.get_building().toStdString());
        Money m = Money(ae.get_salary_zlotys().toInt(), ae.get_salary_grosze().toInt());

        if(ae.get_role_index() == 0){
            restaurant->add_cook(ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m, 0);
        }
        else if(ae.get_role_index() == 1){
            restaurant->add_deliverer(ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
        }
        else if(ae.get_role_index() == 2){
            restaurant->add_manager(ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
        }
        else {
            restaurant->add_waiter(ae.get_name().toStdString(), ae.get_surname().toStdString(), a, m);
        }
        ui->employeeList->clear();
        ui->selectRole->setCurrentIndex(0);
        for(unsigned int i=0; i<restaurant->get_all_employees().size(); i++){
            new QListWidgetItem(QString::fromStdString(restaurant->get_all_employees()[i]->get_name() + " " + restaurant->get_all_employees()[i]->get_surname() + " (" + to_string(restaurant->get_all_employees()[i]->get_id()) + ")"),
                                                       ui->employeeList,
                                                       restaurant->get_all_employees()[i]->get_id());
        }
    }
}

void MainWindow::on_modifyName_clicked(){
    ChangeName chn;
    chn.set_name(ui->name->text());
    chn.setModal(true);
    if(chn.exec() == QDialog::Accepted){
        restaurant->get_employee(current_id)->set_name(chn.get_name().toStdString());
        ui->name->setText(chn.get_name());
        for(unsigned int i=0; i<restaurant->get_all_employees().size(); i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_employees()[i]->get_name() + " " + restaurant->get_all_employees()[i]->get_surname() + " (" + to_string(restaurant->get_all_employees()[i]->get_id()) + ")"),
                                                ui->employeeList,
                                                restaurant->get_all_employees()[i]->get_id());
        }
    }

}

void MainWindow::on_modifySurname_clicked(){
    ChangeSurname chs;
    chs.set_surname(ui->surname->text());
    chs.setModal(true);
    if(chs.exec() == QDialog::Accepted){
        restaurant->get_employee(current_id)->set_surname(chs.get_surnname().toStdString());
        ui->surname->setText(chs.get_surnname());
        for(unsigned int i=0; i<restaurant->get_all_employees().size(); i++){
        new QListWidgetItem(QString::fromStdString(restaurant->get_all_employees()[i]->get_name() + " " + restaurant->get_all_employees()[i]->get_surname() + " (" + to_string(restaurant->get_all_employees()[i]->get_id()) + ")"),
                                                ui->employeeList,
                                                restaurant->get_all_employees()[i]->get_id());
        }
    }
}

void MainWindow::on_modifySalary_clicked(){
    Employee * e =  restaurant->get_employee(current_id);
    ChangeSalary chs;
    chs.set_salary(QString::number(e->get_salary().get_zlotys()), QString::number(e->get_salary().get_cents()));
    chs.setModal(true);
    if(chs.exec() == QDialog::Accepted){
        e->set_salary(Money(chs.get_salary_zlotys().toInt(), chs.get_salary_grosze().toInt()));
    }
    ui->salary->setText(QString::fromStdString(e->get_salary().to_string()));

}

void MainWindow::on_removeEmployee_clicked(){
    try{
        restaurant->remove_employee(current_id);
        ui->employeeStack->setCurrentIndex(1);
        ui->employeeList->clear();
        for(unsigned int i=0; i<restaurant->get_all_employees().size(); i++){
            new QListWidgetItem(QString::fromStdString(restaurant->get_all_employees()[i]->get_name() + " " + restaurant->get_all_employees()[i]->get_surname() + " (" + to_string(restaurant->get_all_employees()[i]->get_id()) + ")"),
                                                    ui->employeeList,
                                                    restaurant->get_all_employees()[i]->get_id());
        }
    }
    catch(restaurant_exception){
            QMessageBox msgBox;
            msgBox.setText("Pracownik zajmuje się obecnie zamówieniem.");
            msgBox.setWindowTitle("Nie można usunąć!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
    }
}

void MainWindow::on_menuList_itemClicked(){

    current_id = ui->menuList->currentItem()->type();
    Dish * dish = restaurant->get_dish(current_id);
    ui->menuStack->setCurrentIndex(0);
    ui->dishName->setText(QString::fromStdString(dish->get_name()));
    ui->Price->setText(QString::fromStdString(dish->get_price().to_string()));
    ui->Category->setText(QString::fromStdString(dish->get_dish_type()));
    ui->DishIngrdidients->clear();
    for(size_t i=0; i<dish->get_ingredients().size(); i++){
            	ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_name()+" ("+to_string(dish->get_ingredients()[i].quantity)+restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_unit() +")"));
    }

}

void MainWindow::on_modifyPrice_clicked(){
    ChangeSalary mp;
    mp.setModal(true);
    Dish * dish = restaurant->get_dish(current_id);
    mp.set_salary(QString::number(dish->get_price().get_zlotys()), QString::number(dish->get_price().get_cents()));
    if(mp.exec() == QDialog::Accepted){
        dish->set_price(Money(mp.get_salary_zlotys().toInt(), mp.get_salary_grosze().toInt()));
    }
    ui->Price->setText(QString::fromStdString(dish->get_price().to_string()));
}

void MainWindow::on_modifyCategory_clicked(){
    ChangeCategory cc;
    cc.setModal(true);
    if(cc.exec() == QDialog::Accepted){
        restaurant->get_dish(current_id)->set_dish_type((dish_type) cc.get_category());
        ui->Category->setText(QString::fromStdString(restaurant->get_dish(current_id)->get_dish_type()));
    }
}

void MainWindow::on_addIngridient_clicked(){
    AddIng ac(*restaurant);
    ac.setModal(true);
    Dish * dish = restaurant->get_dish(current_id);
    if(ac.exec() == QDialog::Accepted){
        dish->add_ingiridnet(ac.get_ing());
        ui->DishIngrdidients->clear();
        for(size_t i=0; i<dish->get_ingredients().size(); i++){
            ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_name()+" ("+to_string(dish->get_ingredients()[i].quantity)+restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_unit() +")"));
        }
    }
}

void MainWindow::on_removeIngridient_clicked(){
    position1 = ui->DishIngrdidients->currentRow();
    Dish * dish = restaurant->get_dish(current_id);
    if(position1 != -1){
        dish->remove_ingridient(position1);
        ui->DishIngrdidients->setCurrentRow(-1);
        ui->DishIngrdidients->clear();
        for(size_t i=0; i<dish->get_ingredients().size(); i++){
            ui->DishIngrdidients->addItem(QString::fromStdString(restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_name()+" ("+to_string(dish->get_ingredients()[i].quantity)+restaurant->get_product(dish->get_ingredients()[i].stock_id)->get_unit() +")"));
        }
    }
}

void MainWindow::on_addMenuDish_clicked(){

    AddMenuDish amd(*restaurant);
    if(amd.exec() == QDialog::Accepted){
        restaurant->add_dish(0, amd.get_name().toStdString(), (dish_type) amd.get_category(), Money(amd.get_zlotys().toInt(), amd.get_grosze().toInt()), amd.get_vegan(), amd.get_ing());
        ui->menuStack->setCurrentIndex(1);
        ui->menuList->clear();
        for(unsigned int i=0; i<restaurant->get_all_dishes().size() ; i++){
            new QListWidgetItem(QString::fromStdString(restaurant->get_all_dishes()[i]->get_name()),
                                                       ui->menuList,
                                                       restaurant->get_all_dishes()[i]->get_id());
        }
    }

}

void MainWindow::on_removeMenuDish_clicked(){
    try{
        restaurant->remove_dish(current_id);
        ui->menuStack->setCurrentIndex(1);
        ui->menuList->clear();
        for(unsigned int i=0; i<restaurant->get_all_dishes().size() ; i++){
            new QListWidgetItem(QString::fromStdString(restaurant->get_all_dishes()[i]->get_name()),
                                                    ui->menuList,
                                                    restaurant->get_all_dishes()[i]->get_id());
        }
    }
    catch(restaurant_exception e){
            QMessageBox msgBox;
            msgBox.setText("Danie znajduje się w zamówieniu (aktywnym bądź w historii)");
            msgBox.setWindowTitle("Nie można usunąć!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {

    event->accept();

    std::ofstream file;
    file.open("rsc/restaurants.json");

    Json::Value res;
    res = restaurant->parse_to_json();
    Json::StyledWriter styledWriter;
    file << styledWriter.write(res);

    file.close();
}
