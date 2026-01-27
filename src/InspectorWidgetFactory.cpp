#include "InspectorWidgetFactory.hpp"
#include "InspectorWidget.hpp"
#include "PointInspectorWidget.hpp"
#include "Point.hpp"

InspectorWidget *InspectorWidgetFactory::create(QGraphicsItem *item, QUndoStack *undoStack, QWidget *parent)
{
    if (dynamic_cast<Point *>(item)) {
        auto *widget = new PointInspectorWidget(undoStack, parent);
        widget->setObject(item);
        return widget;
    }

    // Return a default empty widget if type is not recognized
    return new InspectorWidget(parent);
}
