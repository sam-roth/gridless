#ifndef DELETEPOINTSCOMMAND_HPP
#define DELETEPOINTSCOMMAND_HPP

#include <QUndoCommand>
#include <QList>

class Canvas;
class Point;

class DeletePointsCommand : public QUndoCommand
{
public:
    DeletePointsCommand(Canvas *canvas, const QList<Point *> &points);
    ~DeletePointsCommand();

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    QList<Point *> points;
    bool ownsPoints;
};

#endif // DELETEPOINTSCOMMAND_HPP
