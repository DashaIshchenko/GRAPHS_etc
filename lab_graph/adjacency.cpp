#include "adjacency.h"
#include "ui_adjacency.h"

#include <QDebug>

Adjacency::Adjacency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adjacency)
{
    ui->setupUi(this);
}

Adjacency::~Adjacency()
{
    delete ui;
}

void Adjacency::setAdj(QVector<QVector<int>> adj)
{
    this->adj = adj;
}

void Adjacency::setSize(int size)
{
    this->size = size;
}

void Adjacency::rebuild(QVector<QString> verts)
{
    QStringList names;
    for (int i = 0; i < size; ++i ) {
        names << "V" + verts[i];
    }
    ui->tableAdj->setRowCount(size);
    ui->tableAdj->setColumnCount(size);
    ui->tableAdj->setVerticalHeaderLabels(names);
    ui->tableAdj->setHorizontalHeaderLabels(names);
    for (int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(adj[i][j]));
            ui->tableAdj->setItem(i, j, itm);
            ui->tableAdj->item(i, j)->setFlags(Qt::NoItemFlags);
            //ui->tableAdj->item(i,j)->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }
}

void Adjacency::setGraph(Graph * graph)
{
    this->graph = graph;
}

