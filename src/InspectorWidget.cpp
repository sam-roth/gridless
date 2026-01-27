#include "InspectorWidget.hpp"
#include <QVBoxLayout>

InspectorWidget::InspectorWidget(QWidget *parent)
    : QWidget(parent), currentObject(nullptr)
{
    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    setLayout(layout);
}

void InspectorWidget::setObject(QGraphicsItem *item)
{
    currentObject = item;
}

void InspectorWidget::clear()
{
    currentObject = nullptr;
}

