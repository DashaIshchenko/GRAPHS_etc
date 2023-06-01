#include "dialog.h"
#include "ui_dialog.h"

#include "graph.h"

#include <QDebug>
#include <QMouseEvent>

#include <QGraphicsEllipseItem>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog())
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->btnAddEdge->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnAddVertex->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnAdj->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnDelete->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnBFS->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnDFS->setStyleSheet("background-color:" + QColor(165, 118, 222).name());
    ui->btnDijkstra->setStyleSheet("background-color:" + QColor(165, 118, 222).name());

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnAddVertex_clicked() {
    int num = vertices.size();
    vert = new graphVertex(num);
    vert->setGraph(&graph);
    vertices.push_back(vert);
    scene->addItem(vert);
    if (graph.insertVertex(num)) qDebug() << "success!";
}


void Dialog::on_btnAdj_clicked()
{

    adj = new Adjacency;
    adj->setWindowTitle("Матрица смежности ._.");
    QPalette Pal(QColor(146, 248, 252));
    adj->setPalette(Pal);
    adj->setAutoFillBackground(true);
    adj->setAdj(graph.getAdj());
    adj->setSize(graph.getVertexList().size());
    QVector<QString> names;
    for (auto elem : graph.getVertexList()){
        names.push_back(QString::number(elem));
    }
    adj->rebuild(names);
    adj->show();

}


void Dialog::on_btnAddEdge_clicked()
{

    graphVertex *node1, *node2;
    int vert1, vert2;

    if (ui->graphicsView->scene()->selectedItems().size() == 1) {
        node1 = dynamic_cast<graphVertex *> (ui->graphicsView->scene()->selectedItems().at(0));
        node1->setPressed(true);
        if (for_draw.isEmpty()) for_draw.push_back(node1);
        else if (for_draw.front() != node1 && for_draw.front() != nullptr) {
            /// ВЫЗОВ ДИАЛОГОВОГО ОКНА ///
            int result = 1;
            GetWeight gw;
            gw.setWindowTitle("Вес ребра^^");
            QPalette Pal(QColor(173, 252, 146));
            gw.setPalette(Pal);
            gw.setAutoFillBackground(true);
            if (gw.exec()) result = gw.weight;
            if (result == 0) result = 1;

            node2 = for_draw.front();
            vert1 = node1->getNum(); vert2 = node2->getNum();
            graph.InsertEdge(vert2, vert1, result); graph.InsertEdge(vert1, vert2, result);
            edge = new Edge(node1, node2);
            edge->setGraph(&graph);
            if (node1->pressed() == true) node1->setPressed(false);
            if (node2->pressed() == true) node2->setPressed(false);
            edge->setContent(result);
            scene->addItem(edge);
            edges.push_back(edge);
            for_draw.pop_back();
        }

    }
    ui->graphicsView->scene()->clearSelection();
}

void Dialog::on_btnDelete_clicked()
{
    if (ui->graphicsView->scene()->selectedItems().size()!=0){
        int last = ui->graphicsView->scene()->selectedItems().size()-1;
        auto current = ui->graphicsView->scene()->selectedItems().at(last);
        delete current;
    }

}



void Dialog::on_btnBFS_clicked()
{
    int current = 0;
    GetWeight gw;
    QPalette Pal1(QColor(173, 252, 146));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("С какой вершины начнём?^^");
    if (gw.exec()) current = gw.weight;
    if (current < graph.getVertexList().size()){
        ShowInfo info;
        QPalette Pal(QColor(252, 173, 146));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = "";
        QVector<bool> visited(graph.getVertexList().size());
        for (auto it = visited.begin(); it !=visited.end(); ++it) *it = false;
        graph.BFS(current, visited, res);
        info.setInfo(res);
        if (!info.exec()) qDebug() << "Error";
    }

}


void Dialog::on_btnDFS_clicked()
{
    int current = 0;
    GetWeight gw;
    QPalette Pal1(QColor(173, 252, 146));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("С какой вершины начнём?^^");
    if (gw.exec()) current = gw.weight;
    if (current < graph.getVertexList().size()){
        ShowInfo info;
        QPalette Pal(QColor(252, 173, 146));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = "";
        QVector<bool> visited(graph.getVertexList().size());
        for (auto it = visited.begin(); it !=visited.end(); ++it) *it = false;
        graph.DFS(current, visited, res);
        info.setInfo(res);
        if (!info.exec()) qDebug() << "Error";
    }
}



void Dialog::on_btnDijkstra_clicked()
{

    int current = 0;
    GetWeight gw;
    QPalette Pal1(QColor(173, 252, 146));
    gw.setPalette(Pal1);
    gw.setAutoFillBackground(true);
    gw.setWindowTitle("С какой вершины начнём?^^");
    if (gw.exec()) current = gw.weight;
    if (current < graph.getVertexList().size()){
        ShowInfo info;
        QPalette Pal(QColor(252, 173, 146));
        info.setPalette(Pal);
        info.setAutoFillBackground(true);
        QString res = "";
        graph.Dijkstra(current, res);
        info.setInfo(res);
        if (!info.exec()) qDebug() << "Error";
    }

}

