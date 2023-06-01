#include "getweight.h"
#include "ui_getweight.h"

#include <QDebug>

GetWeight::GetWeight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetWeight)
{
    ui->setupUi(this);
    ui->btnWeight->setStyleSheet("background-color:" + QColor(126, 191, 103).name());
}

GetWeight::~GetWeight()
{
    delete ui;
}

void GetWeight::on_btnWeight_clicked()
{
   QString res = ui->inputWeight->toPlainText();
   weight = res.toInt();
   if (weight < 0) weight = abs(weight);
   accept();
}

