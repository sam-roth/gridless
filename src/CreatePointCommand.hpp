#ifndef CREATEPOINTCOMMAND_HPP
#define CREATEPOINTCOMMAND_HPP

#include <QUndoCommand>
#include <QPointF>

class Canvas;
class Point;

class CreatePointCommand : public QUndoCommand
{
public:
    CreatePointCommand(Canvas *canvas, const QPointF &position);

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    QPointF position;
    Point *point;
};

#endif // CREATEPOINTCOMMAND_HPP
