#ifndef ADJACENCY_H
#define ADJACENCY_H

#include <QWidget>
#include "graph.h"
namespace Ui {
class Adjacency;
}

class Adjacency : public QWidget
{
    Q_OBJECT

public:
    explicit Adjacency(QWidget *parent = nullptr);
    ~Adjacency();
    void setAdj(QVector<QVector<int>>);
    void setSize(int);
    void rebuild(QVector<QString>);
    void setGraph(Graph*);

private:
    Ui::Adjacency *ui;
    QVector<QVector<int>> adj;
    int size;
    Graph *graph;

};

#endif // ADJACENCY_H
