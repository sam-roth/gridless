#include "UpdatePointCommand.hpp"
#include "Point.hpp"

UpdatePointCommand::UpdatePointCommand(Point *point, const QString &newId, const QPointF &newPosition)
    : QUndoCommand("Update Point"),
      point(point),
      oldId(point->getId()),
      newId(newId),
      oldPosition(point->pos()),
      newPosition(newPosition)
{
}

void UpdatePointCommand::undo()
{
    point->setId(oldId);
    point->setPos(oldPosition);
}

void UpdatePointCommand::redo()
{
    point->setId(newId);
    point->setPos(newPosition);
}
