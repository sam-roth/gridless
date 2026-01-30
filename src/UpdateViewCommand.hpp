#ifndef UPDATEVIEWCOMMAND_HPP
#define UPDATEVIEWCOMMAND_HPP

#include <QUndoCommand>
#include <QString>

class Canvas;
class View;

class UpdateViewCommand : public QUndoCommand
{
public:
    UpdateViewCommand(Canvas *canvas, View *view, const QString &newId, const QString &newFormula);

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    View *view;
    QString oldId;
    QString newId;
    QString oldFormula;
    QString newFormula;
};

#endif // UPDATEVIEWCOMMAND_HPP
