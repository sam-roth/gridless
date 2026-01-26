#include "Point.hpp"
#include <QPainter>

Point::Point(const QPointF &position, const QString &id, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), _id(id)
{
    // Create a small circle for the point
    const qreal radius = 5.0;
    setRect(-radius, -radius, radius * 2, radius * 2);
    setPos(position);

    // Set visual properties
    setBrush(Qt::blue);
    setPen(Qt::NoPen);

    // Make it selectable
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}
