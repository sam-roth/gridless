#include "UpdateViewCommand.hpp"
#include "Canvas.hpp"
#include "View.hpp"

UpdateViewCommand::UpdateViewCommand(Canvas *canvas, View *view, const QString &newId, const QString &newFormula)
    : QUndoCommand("Update View"),
      canvas(canvas),
      view(view),
      oldId(view->id()),
      newId(newId),
      oldFormula(view->formula()),
      newFormula(newFormula)
{
}

void UpdateViewCommand::undo()
{
    canvas->setViewId(view, oldId);
    view->setFormula(oldFormula);
}

void UpdateViewCommand::redo()
{
    canvas->setViewId(view, newId);
    view->setFormula(newFormula);
}
