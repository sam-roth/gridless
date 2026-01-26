#include "Canvas.hpp"
#include <QGraphicsScene>

Canvas::Canvas(QWidget *parent)
    : QGraphicsView(parent)
{
    auto *scene = new QGraphicsScene(this);
    setScene(scene);
    setBackgroundBrush(Qt::white);
}
