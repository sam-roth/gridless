#include "UpdateViewCommand.hpp"
#include "commandIds.hpp"
#include "Canvas.hpp"
#include "View.hpp"

UpdateViewCommand::UpdateViewCommand(Canvas *canvas, View *view, const QString &newId, const QString &newFormula, const QPointF &newPosition)
    : QUndoCommand("Update View"),
      canvas(canvas),
      view(view),
      oldId(view->id()),
      newId(newId),
      oldFormula(view->formula()),
      newFormula(newFormula),
      oldPosition(view->pos()),
      newPosition(newPosition)
{
}

int UpdateViewCommand::id() const
{
    return UpdateViewCommandId;
}

bool UpdateViewCommand::mergeWith(const QUndoCommand *other)
{
    if (other->id() != id()) {
        return false;
    }

    const UpdateViewCommand *otherCmd = static_cast<const UpdateViewCommand *>(other);
    if (otherCmd->view != view) {
        return false;
    }

    // Merge by updating the new values to those of the other command
    newId = otherCmd->newId;
    newFormula = otherCmd->newFormula;
    newPosition = otherCmd->newPosition;

    return true;
}

void UpdateViewCommand::undo()
{
    canvas->setViewId(view, oldId);
    view->setFormula(oldFormula);
    view->setPos(oldPosition);
}

void UpdateViewCommand::redo()
{
    canvas->setViewId(view, newId);
    view->setFormula(newFormula);
    view->setPos(newPosition);
}
