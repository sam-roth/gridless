#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsView>
#include <QMap>

class Point;

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void setToolMode(const QString &mode);
    Point *createPoint(const QPointF &position);

    void deleteSelectedItems();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString currentTool;
    int pointCounter;
    QMap<QString, Point *> points;

    QString generatePointId();
};

#endif // CANVAS_HPP

