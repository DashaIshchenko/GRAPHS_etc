#include "graphvertex.h"

#include <QFontDatabase>


graphVertex::graphVertex(int num)
{
    this->num = num;
    _pressed = false;
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    //drawing = new QGraphicsItemGroup;
}

graphVertex::~graphVertex()
{
    while (!edgeList.isEmpty())
            delete edgeList.takeFirst();
    graph->eraseVertex(num);

}

QRectF graphVertex::boundingRect() const
{
    return shape().boundingRect(); //QRectF(0,0,40,40);
}

bool graphVertex::pressed() const
{
    return _pressed;
}

void graphVertex::setPressed(bool pressed)
{
    _pressed = pressed;
    update();
}

QString graphVertex::getContent()
{
    return content;
}

void graphVertex::setGraph(Graph *graph)
{
    this->graph = graph;
}

int graphVertex::getNum()
{
    return num;
}

QPainterPath graphVertex::shape() const
{
    QPainterPath path;
    path.addEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
    return path;
}

void graphVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
    QBrush brush(Qt::blue);
    if (pressed()) brush.setColor(QColor(240, 118, 108));
    else brush.setColor(QColor(135, 121, 242));
    painter->setBrush(brush);
    painter->setPen(QPen(pressed() ? QColor(173, 68, 59) : QColor(94, 83, 184), 2));
    painter->drawEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
    content = "V" + QString::number(num);
    painter->drawText(boundingRect(), Qt::AlignCenter, content);
}

QVariant graphVertex::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionHasChanged:
            foreach (Edge *edge, edgeList)
                edge->adjust();
            break;
        default:
            break;
        };

        return QGraphicsItem::itemChange(change, value);
}

void graphVertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void graphVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    _pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void graphVertex::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void graphVertex::removeEdge(Edge *edge)
{
    edgeList.removeOne(edge);
}
