#include "Canvas.hpp"
#include "Point.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QGraphicsView(parent), currentTool("Select"), pointCounter(0)
{
    auto *scene = new QGraphicsScene(this);
    setScene(scene);
    setBackgroundBrush(Qt::white);
}

void Canvas::setToolMode(const QString &mode)
{
    currentTool = mode;
}

Point *Canvas::createPoint(const QPointF &position)
{
    QString id = generatePointId();
    auto *point = new Point(position, id);
    scene()->addItem(point);
    points.insert(id, point);
    return point;
}

void Canvas::deleteSelectedItems()
{
    QList<QGraphicsItem *> selectedItems = scene()->selectedItems();
    for (QGraphicsItem *item : selectedItems) {
        scene()->removeItem(item);
        Point *point = dynamic_cast<Point *>(item);
        if (point) {
            points.remove(point->id());
            delete point;
        } else {
            delete item;
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (currentTool == "Point" && event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        createPoint(scenePos);
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

QString Canvas::generatePointId()
{
    ++pointCounter;
    return "$p" + QString::number(pointCounter);
}

