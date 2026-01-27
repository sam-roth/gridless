#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP

#include <QWidget>

class QGraphicsItem;
class QUndoStack;

class Canvas;
class InspectorWidget;

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(Canvas *canvas, QUndoStack *undoStack, QWidget *parent = nullptr);

public slots:
    void setSelectedObject(QGraphicsItem *item);

private:
    Canvas *canvas;
    QUndoStack *undoStack;
    InspectorWidget *currentInspectorWidget;
};

#endif // INSPECTOR_HPP
