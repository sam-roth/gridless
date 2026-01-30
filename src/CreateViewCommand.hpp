#ifndef CREATEVIEWCOMMAND_HPP
#define CREATEVIEWCOMMAND_HPP

#include <QUndoCommand>
#include <QPointF>

class Canvas;
class View;

class CreateViewCommand : public QUndoCommand
{
public:
    CreateViewCommand(Canvas *canvas, const QPointF &position);

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    QPointF position;
    View *view;
};

#endif // CREATEVIEWCOMMAND_HPP
