#ifndef DIALOG_H
#define DIALOG_H

#include "graphvertex.h"
#include "graph.h"
#include "showinfo.h"

#include <adjacency.h>
#include <getweight.h>

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>


namespace Ui {
class Dialog;
}


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnAddVertex_clicked();

    void on_btnAdj_clicked();

    void on_btnAddEdge_clicked();

    void on_btnDelete_clicked();

    void on_btnBFS_clicked();

    void on_btnDFS_clicked();

    void on_btnDijkstra_clicked();

private:
    Ui::Dialog *ui;

    Adjacency *adj;

    QGraphicsScene * scene;

    Graph graph;

    graphVertex* vert;

    QVector<graphVertex*> vertices;

    Edge* edge;

    QVector<Edge*> edges;

    QQueue<graphVertex*> for_draw;

};

#endif // DIALOG_H
