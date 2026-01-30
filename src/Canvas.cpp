#include "Canvas.hpp"
#include "Point.hpp"
#include "View.hpp"
#include "CreatePointCommand.hpp"
#include "CreateViewCommand.hpp"
#include "DeletePointsCommand.hpp"
#include "DeleteViewsCommand.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QUndoStack>

Canvas::Canvas(QUndoStack *undoStack, QWidget *parent)
    : QGraphicsView(parent), undoStack(undoStack), currentTool("Select"), pointCounter(0), viewCounter(0)
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

View *Canvas::createView(const QPointF &position)
{
    QString id = generateViewId();
    auto *view = new View(position, id);
    scene()->addItem(view);
    views.insert(id, view);
    return view;
}

void Canvas::removeView(View *view)
{
    scene()->removeItem(view);
    views.remove(view->id());
}

void Canvas::addView(View *view)
{
    scene()->addItem(view);
    views.insert(view->id(), view);
}

void Canvas::deleteSelectedItems()
{
    auto selectedItems = scene()->selectedItems();

    if (selectedItems.isEmpty()) {
        return;
    }

    QList<Point *> pointsToDelete;
    QList<View *> viewsToDelete;
    for (auto *item : selectedItems) {
        if (auto *point = dynamic_cast<Point *>(item)) {
            pointsToDelete.append(point);
        } else if (auto *view = dynamic_cast<View *>(item)) {
            viewsToDelete.append(view);
        }
    }

    if (!pointsToDelete.isEmpty()) {
        undoStack->push(new DeletePointsCommand(this, pointsToDelete));
    }

    if (!viewsToDelete.isEmpty()) {
        undoStack->push(new DeleteViewsCommand(this, viewsToDelete));
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

bool Canvas::canSetViewId(View *view, const QString &newId) const
{
    if (view->id() == newId) {
        return true; // No change needed
    }

    return !views.contains(newId);
}

void Canvas::setViewId(View *view, const QString &newId)
{
    if (view->_id == newId) {
        // ID is the same, no change needed
        return;
    }

    Q_ASSERT(!views.contains(newId));

    views.remove(view->id());
    view->_id = newId;
    views.insert(newId, view);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (currentTool == "Point" && event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        undoStack->push(new CreatePointCommand(this, scenePos));
        return;
    }

    if (currentTool == "View" && event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        undoStack->push(new CreateViewCommand(this, scenePos));
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
    return "p" + QString::number(pointCounter);
}

QString Canvas::generateViewId()
{
    ++viewCounter;
    return "v" + QString::number(viewCounter);
}
