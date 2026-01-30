#ifndef UPDATEPOINTCOMMAND_HPP
#define UPDATEPOINTCOMMAND_HPP

#include <QUndoCommand>
#include <QString>
#include <QPointF>

class Canvas;
class Point;

class UpdatePointCommand : public QUndoCommand
{
public:
    UpdatePointCommand(Canvas *canvas, Point *point, const QString &newId, const QPointF &newPosition);

    int id() const override;
    bool mergeWith(const QUndoCommand *other) override;

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    Point *point;
    QString oldId;
    QString newId;
    QPointF oldPosition;
    QPointF newPosition;
};

#endif // UPDATEPOINTCOMMAND_HPP
