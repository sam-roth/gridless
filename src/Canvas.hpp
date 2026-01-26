#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsView>

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
};

#endif // CANVAS_HPP
