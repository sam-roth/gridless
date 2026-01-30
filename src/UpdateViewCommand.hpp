#ifndef UPDATEVIEWCOMMAND_HPP
#define UPDATEVIEWCOMMAND_HPP

#include <QUndoCommand>
#include <QString>
#include <QPointF>

class Canvas;
class View;

class UpdateViewCommand : public QUndoCommand
{
public:
    UpdateViewCommand(Canvas *canvas, View *view, const QString &newId, const QString &newFormula, const QPointF &newPosition);

    int id() const override;
    bool mergeWith(const QUndoCommand *other) override;

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    View *view;
    QString oldId;
    QString newId;
    QString oldFormula;
    QString newFormula;
    QPointF oldPosition;
    QPointF newPosition;
};

#endif // UPDATEVIEWCOMMAND_HPP
