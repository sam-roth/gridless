#include "View.hpp"
#include <QPainter>
#include <QPainterPath>

View::View(const QPointF &position, const QString &id, const QString &formula, QGraphicsItem *parent)
    : QGraphicsItem(parent), _id(id), _formula(formula)
{
    setPos(position);

    // Make it selectable
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

QRectF View::boundingRect() const
{
    // View is represented as a small rectangle with an origin point indicator
    const qreal size = 10.0;
    return QRectF(-size/2, -size/2, size, size);
}

void View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    const qreal size = 10.0;
    const QRectF rect(-size/2, -size/2, size, size);

    // Draw the view as a small square with a cross marking the origin
    if (isSelected()) {
        painter->setBrush(QColor(100, 149, 237)); // Cornflower blue
        painter->setPen(QPen(Qt::darkBlue, 2));
    } else {
        painter->setBrush(QColor(176, 196, 222)); // Light steel blue
        painter->setPen(QPen(Qt::gray, 1));
    }

    painter->drawRect(rect);

    // Draw a cross at the origin to indicate the anchor point
    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(-size/2, 0, size/2, 0);
    painter->drawLine(0, -size/2, 0, size/2);
}
