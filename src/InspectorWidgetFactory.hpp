#ifndef INSPECTORWIDGETFACTORY_HPP
#define INSPECTORWIDGETFACTORY_HPP

#include <QWidget>

class QGraphicsItem;
class QUndoStack;

class Canvas;
class InspectorWidget;

InspectorWidget *createInspectorWidget(QGraphicsItem *item, Canvas *canvas, QUndoStack *undoStack, QWidget *parent = nullptr);

#endif // INSPECTORWIDGETFACTORY_HPP
