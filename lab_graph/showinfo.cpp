#include "showinfo.h"
#include "ui_showinfo.h"

ShowInfo::ShowInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowInfo)
{
    ui->setupUi(this);
}

ShowInfo::~ShowInfo()
{
    delete ui;
}
void ShowInfo::setInfo(QString res)
{
    ui->label->setText(res);
}
