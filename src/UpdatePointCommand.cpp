#include "UpdatePointCommand.hpp"
#include "commandIds.hpp"
#include "Canvas.hpp"
#include "Point.hpp"

UpdatePointCommand::UpdatePointCommand(Canvas *canvas, Point *point, const QString &newId, const QPointF &newPosition)
    : QUndoCommand("Update Point"),
      canvas(canvas),
      point(point),
      oldId(point->id()),
      newId(newId),
      oldPosition(point->pos()),
      newPosition(newPosition)
{
}

int UpdatePointCommand::id() const
{
    return UpdatePointCommandId;
}

bool UpdatePointCommand::mergeWith(const QUndoCommand *other)
{
    if (other->id() != id()) {
        return false;
    }

    const UpdatePointCommand *otherCmd = static_cast<const UpdatePointCommand *>(other);
    if (otherCmd->point != point) {
        return false;
    }

    // Merge by updating the newId and newPosition to those of the other command
    newId = otherCmd->newId;
    newPosition = otherCmd->newPosition;

    return true;
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
