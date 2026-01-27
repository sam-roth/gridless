#include "UpdatePointCommand.hpp"
#include "Canvas.hpp"
#include "Point.hpp"

UpdatePointCommand::UpdatePointCommand(Canvas *canvas, Point *point, const QString &newId, const QPointF &newPosition)
    : QUndoCommand("Update Point"),
      canvas(canvas),
      point(point),
      oldId(point->getId()),
      newId(newId),
      oldPosition(point->pos()),
      newPosition(newPosition)
{
}

void UpdatePointCommand::undo()
{
    canvas->setPointId(point, oldId);
    point->setPos(oldPosition);
}

void UpdatePointCommand::redo()
{
    canvas->setPointId(point, newId);
    point->setPos(newPosition);
}
