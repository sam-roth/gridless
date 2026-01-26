#ifndef POINT_HPP
#define POINT_HPP

#include <QGraphicsEllipseItem>
#include <QString>
#include <QPointF>

class Point : public QGraphicsEllipseItem
{
public:
    explicit Point(const QPointF &position, const QString &id, QGraphicsItem *parent = nullptr);

    QString getId() const { return id; }
    QPointF getPosition() const { return pos(); }

private:
    QString id;
};

#endif // POINT_HPP
