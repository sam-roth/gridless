#ifndef POINT_HPP
#define POINT_HPP

#include <QGraphicsEllipseItem>
#include <QString>
#include <QPointF>

class Point : public QGraphicsEllipseItem
{
public:
    explicit Point(const QPointF &position, const QString &id, QGraphicsItem *parent = nullptr);

    const QString &id() const { return _id; }

private:
    QString _id;
};

#endif // POINT_HPP
