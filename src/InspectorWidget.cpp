#include "InspectorWidget.hpp"
#include <QVBoxLayout>

InspectorWidget::InspectorWidget(QWidget *parent)
    : QWidget(parent), currentObject(nullptr)
{
}

void InspectorWidget::setObject(QGraphicsItem *item)
{
    currentObject = item;
}

void InspectorWidget::clear()
{
    currentObject = nullptr;
}

