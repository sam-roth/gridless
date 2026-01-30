#ifndef DELETEVIEWSCOMMAND_HPP
#define DELETEVIEWSCOMMAND_HPP

#include <QUndoCommand>
#include <QList>

class Canvas;
class View;

class DeleteViewsCommand : public QUndoCommand
{
public:
    DeleteViewsCommand(Canvas *canvas, const QList<View *> &views);
    ~DeleteViewsCommand();

    void undo() override;
    void redo() override;

private:
    Canvas *canvas;
    QList<View *> views;
    bool ownsViews;
};

#endif // DELETEVIEWSCOMMAND_HPP
