#include "InspectorWidgetFactory.hpp"
#include "InspectorWidget.hpp"
#include "PointInspectorWidget.hpp"
#include "ViewInspectorWidget.hpp"
#include "Point.hpp"
#include "View.hpp"

InspectorWidget *createInspectorWidget(QGraphicsItem *item, Canvas *canvas, QUndoStack *undoStack, QWidget *parent)
{
    if (dynamic_cast<Point *>(item)) {
        auto *widget = new PointInspectorWidget(canvas, undoStack, parent);
        widget->setObject(item);
        return widget;
    }

    if (dynamic_cast<View *>(item)) {
        auto *widget = new ViewInspectorWidget(canvas, undoStack, parent);
        widget->setObject(item);
        return widget;
    }

    // Return a default empty widget if type is not recognized
    return new InspectorWidget(parent);
}
