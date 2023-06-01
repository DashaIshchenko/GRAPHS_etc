#ifndef SHOWINFO_H
#define SHOWINFO_H

#include <QDialog>

namespace Ui {
class ShowInfo;
}

class ShowInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ShowInfo(QWidget *parent = nullptr);
    ~ShowInfo();
    void setInfo(QString);

private:
    Ui::ShowInfo *ui;
};

#endif // SHOWINFO_H
