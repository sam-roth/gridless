#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsView>
#include <QMap>
#include <QGraphicsItem>

class Point;
class View;
class QUndoStack;

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QUndoStack *undoStack, QWidget *parent = nullptr);

    void setToolMode(const QString &mode);
    Point *createPoint(const QPointF &position);
    void removePoint(Point *point);
    void addPoint(Point *point);

    View *createView(const QPointF &position);
    void removeView(View *view);
    void addView(View *view);

    void deleteSelectedItems();

    bool canSetPointId(Point *point, const QString &newId) const;
    void setPointId(Point *point, const QString &newId);

    bool canSetViewId(View *view, const QString &newId) const;
    void setViewId(View *view, const QString &newId);

signals:
    void selectionChanged(QGraphicsItem *item);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void notifySelectionChanged();

    QUndoStack *undoStack;
    QString currentTool;
    int pointCounter;
    int viewCounter;
    QMap<QString, Point *> points;
    QMap<QString, View *> views;

    QString generatePointId();
    QString generateViewId();
};

#endif // CANVAS_HPP

