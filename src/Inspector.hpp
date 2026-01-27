#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP

#include <QWidget>

class QGraphicsItem;
class InspectorWidget;
class QUndoStack;

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QUndoStack *undoStack, QWidget *parent = nullptr);

public slots:
    void setSelectedObject(QGraphicsItem *item);

private:
    QUndoStack *undoStack;
    InspectorWidget *currentInspectorWidget;
};

#endif // INSPECTOR_HPP
