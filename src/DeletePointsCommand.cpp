#include "DeletePointsCommand.hpp"
#include "Canvas.hpp"
#include "Point.hpp"

DeletePointsCommand::DeletePointsCommand(Canvas *canvas, const QList<Point *> &points)
    : QUndoCommand("Delete Points"), canvas(canvas), points(points), ownsPoints(false)
{
}

DeletePointsCommand::~DeletePointsCommand()
{
    if (ownsPoints) {
        for (auto *point : points) {
            delete point;
        }
    }
}

void DeletePointsCommand::undo()
{
    for (auto *point : points) {
        canvas->addPoint(point);
    }
    ownsPoints = false;
}

void DeletePointsCommand::redo()
{
    for (auto *point : points) {
        canvas->removePoint(point);
    }
    ownsPoints = true;
}
