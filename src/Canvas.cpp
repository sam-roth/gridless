#include "Canvas.hpp"
#include "Point.hpp"
#include "CreatePointCommand.hpp"
#include "DeletePointsCommand.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QUndoStack>

Canvas::Canvas(QUndoStack *undoStack, QWidget *parent)
    : QGraphicsView(parent), undoStack(undoStack), currentTool("Select"), pointCounter(0)
{
    auto *scene = new QGraphicsScene(this);
    setScene(scene);
    setBackgroundBrush(Qt::white);
    setRenderHint(QPainter::Antialiasing, true);
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
    points.remove(point->id());
}

void Canvas::addPoint(Point *point)
{
    scene()->addItem(point);
    points.insert(point->id(), point);
}

void Canvas::deleteSelectedItems()
{
    auto selectedItems = scene()->selectedItems();

    if (selectedItems.isEmpty()) {
        return;
    }

    QList<Point *> pointsToDelete;
    for (auto *item : selectedItems) {
        if (auto *point = dynamic_cast<Point *>(item)) {
            pointsToDelete.append(point);
        }
    }

    if (!pointsToDelete.isEmpty()) {
        undoStack->push(new DeletePointsCommand(this, pointsToDelete));
    }
}

bool Canvas::canSetPointId(Point *point, const QString &newId) const
{
    if (point->id() == newId) {
        return true; // No change needed
    }

    return !points.contains(newId);
}

void Canvas::setPointId(Point *point, const QString &newId)
{
    if (point->_id == newId) {
        // ID is the same, no change needed
        return;
    }

    Q_ASSERT(!points.contains(newId));

    points.remove(point->id());
    point->_id = newId;
    points.insert(newId, point);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (currentTool == "Point" && event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        undoStack->push(new CreatePointCommand(this, scenePos));
        return;
    }

    QGraphicsView::mousePressEvent(event);

    notifySelectionChanged();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    // Ensure position of item is correct in the inspector after move.
    notifySelectionChanged();
    QGraphicsView::mouseReleaseEvent(event);
}

void Canvas::notifySelectionChanged()
{
    auto selectedItems = scene()->selectedItems();
    if (selectedItems.isEmpty()) {
        emit selectionChanged(nullptr);
    } else {
        emit selectionChanged(selectedItems.first());
    }
}

QString Canvas::generatePointId()
{
    ++pointCounter;
    return "$p" + QString::number(pointCounter);
}

