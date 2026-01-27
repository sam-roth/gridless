#ifndef INSPECTORWIDGETFACTORY_HPP
#define INSPECTORWIDGETFACTORY_HPP

#include <QWidget>

class QGraphicsItem;
class InspectorWidget;
class QUndoStack;

class InspectorWidgetFactory
{
public:
    static InspectorWidget *create(QGraphicsItem *item, QUndoStack *undoStack, QWidget *parent = nullptr);
};

#endif // INSPECTORWIDGETFACTORY_HPP
