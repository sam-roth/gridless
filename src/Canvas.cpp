#include "Canvas.hpp"
#include "Point.hpp"
#include "CreatePointCommand.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QUndoStack>

Canvas::Canvas(QUndoStack *undoStack, QWidget *parent)
    : QGraphicsView(parent), undoStack(undoStack), currentTool("Select"), pointCounter(0)
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

void Canvas::removePoint(Point *point)
{
    scene()->removeItem(point);
    points.remove(point->getId());
    delete point;
}

void Canvas::addPoint(Point *point)
{
    scene()->addItem(point);
    points.insert(point->getId(), point);
}

void Canvas::deleteSelectedItems()
{
    auto selectedItems = scene()->selectedItems();

    for (auto *item : selectedItems) {
        scene()->removeItem(item);

        if (auto *point = dynamic_cast<Point *>(item)) {
            points.remove(point->getId());
        }

        delete item;
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (currentTool == "Point" && event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        undoStack->push(new CreatePointCommand(this, scenePos));
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

QString Canvas::generatePointId()
{
    ++pointCounter;
    return "$p" + QString::number(pointCounter);
}

