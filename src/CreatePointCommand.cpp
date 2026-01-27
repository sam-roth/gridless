#include "CreatePointCommand.hpp"
#include "Canvas.hpp"
#include "Point.hpp"

CreatePointCommand::CreatePointCommand(Canvas *canvas, const QPointF &position)
    : QUndoCommand("Create Point"), canvas(canvas), position(position), point(nullptr)
{
}

void CreatePointCommand::undo()
{
    if (point) {
        canvas->removePoint(point);
        point = nullptr;
    }
}

void CreatePointCommand::redo()
{
    if (!point) {
        point = canvas->createPoint(position);
    } else {
        canvas->addPoint(point);
    }
}
