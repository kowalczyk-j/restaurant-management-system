#ifndef CHANGEID_H
#define CHANGEID_H
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include "ui_changeid.h"


class ChangeId : public QDialog
{
    Q_OBJECT
public:
	ChangeId(QWidget *parent = 0);


private slots:

public :
	void set_id(QString id){ui->id->setText(id);};
	QString get_id(){return ui->id->text();}

private:
	Ui::ChangeId *ui;
};
#endif