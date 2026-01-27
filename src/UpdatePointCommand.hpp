#ifndef UPDATEPOINTCOMMAND_HPP
#define UPDATEPOINTCOMMAND_HPP

#include <QUndoCommand>
#include <QString>
#include <QPointF>

class Point;

class UpdatePointCommand : public QUndoCommand
{
public:
    UpdatePointCommand(Point *point, const QString &newId, const QPointF &newPosition);

    void undo() override;
    void redo() override;

private:
    Point *point;
    QString oldId;
    QString newId;
    QPointF oldPosition;
    QPointF newPosition;
};

#endif // UPDATEPOINTCOMMAND_HPP
