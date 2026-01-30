#include "CreateViewCommand.hpp"
#include "Canvas.hpp"
#include "View.hpp"

CreateViewCommand::CreateViewCommand(Canvas *canvas, const QPointF &position)
    : QUndoCommand("Create View"), canvas(canvas), position(position), view(nullptr)
{
}

void CreateViewCommand::undo()
{
    if (view) {
        canvas->removeView(view);
        view = nullptr;
    }
}

void CreateViewCommand::redo()
{
    if (!view) {
        view = canvas->createView(position);
    } else {
        canvas->addView(view);
    }
}
