#include "DeleteViewsCommand.hpp"
#include "Canvas.hpp"
#include "View.hpp"

DeleteViewsCommand::DeleteViewsCommand(Canvas *canvas, const QList<View *> &views)
    : QUndoCommand("Delete Views"), canvas(canvas), views(views), ownsViews(false)
{
}

DeleteViewsCommand::~DeleteViewsCommand()
{
    if (ownsViews) {
        for (auto *view : views) {
            delete view;
        }
    }
}

void DeleteViewsCommand::undo()
{
    for (auto *view : views) {
        canvas->addView(view);
    }
    ownsViews = false;
}

void DeleteViewsCommand::redo()
{
    for (auto *view : views) {
        canvas->removeView(view);
    }
    ownsViews = true;
}
