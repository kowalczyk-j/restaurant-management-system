#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QUrl>
#include <string>
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    vector.push_back("Restauracj Magnoliowa");
    vector.push_back("Restauracja Różana");
    QString buff1;
    QStringList buff2;
    ui = new Ui::MainWindow;
	ui->setupUi(this);
    ui->mapa->setSource(QUrl(QStringLiteral("qmlMap.qml")));
    ui->mapa->setResizeMode( QQuickWidget::SizeRootObjectToView );
    for(unsigned int i=0; i<vector.size(); i++){
        ui->list1->addItem(QString::fromStdString(vector[i]));
    }


}
void MainWindow::on_return_2_clicked(){
    if(ui->restaurantStack->currentIndex() == 0)
    ui->mainStack->setCurrentIndex(0);
    else ui->restaurantStack->setCurrentIndex(0);
}
void MainWindow::on_selectRestaurant_clicked(){
    ui->mainStack->setCurrentIndex(1);
}
void MainWindow::on_movePantry_clicked(){
    ui->restaurantStack->setCurrentIndex(1);
}
void MainWindow::on_moveEmployee_clicked(){
    ui->restaurantStack->setCurrentIndex(2);
}
void MainWindow::on_moveMenu_clicked(){
    ui->restaurantStack->setCurrentIndex(3);
}
void MainWindow::on_moveOrders_clicked(){
    ui->restaurantStack->setCurrentIndex(4);
}