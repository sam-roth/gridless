#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsView>
#include <QMap>

class Point;
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

    void deleteSelectedItems();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QUndoStack *undoStack;
    QString currentTool;
    int pointCounter;
    QMap<QString, Point *> points;

    QString generatePointId();
};

#endif // CANVAS_HPP

