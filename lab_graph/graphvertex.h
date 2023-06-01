#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "edge.h"
static const int RADIUS = 40;
class graphVertex : public QGraphicsItem
{
    friend Edge::Edge(graphVertex *sourceVert, graphVertex *destVert);
    friend Edge::~Edge();
public:
    graphVertex(int);
    ~graphVertex();
    QList<Edge *> edges() const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;
    bool pressed() const;
    void setPressed(bool pressed);
    QString getContent();
    void setGraph(Graph*);
    int getNum();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);
private:
    QList<Edge *> edgeList;

    bool _pressed;
    QGraphicsItemGroup *drawing;
    Graph *graph;
    int num = 0;
    QString content = "V";


};
#endif // GRAPHVERTEX_H


