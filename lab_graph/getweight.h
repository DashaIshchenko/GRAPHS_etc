#ifndef GETWEIGHT_H
#define GETWEIGHT_H

#include <QDialog>

namespace Ui {
class GetWeight;
}

class GetWeight : public QDialog
{
    Q_OBJECT

public:
    explicit GetWeight(QWidget *parent = nullptr);
    ~GetWeight();

    int weight = 1;

signals:
    void sendWeight(QString);

private slots:
    void on_btnWeight_clicked();

private:
    Ui::GetWeight *ui;
};

#endif // GETWEIGHT_H
