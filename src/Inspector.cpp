#include "Inspector.hpp"
#include "InspectorWidgetFactory.hpp"
#include "InspectorWidget.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QUndoStack>

Inspector::Inspector(QUndoStack *undoStack, QWidget *parent)
    : QWidget(parent), undoStack(undoStack), currentInspectorWidget(nullptr)
{
    auto *layout = new QVBoxLayout(this);

    auto *titleLabel = new QLabel(tr("Inspector"), this);
    auto font = titleLabel->font();
    font.setBold(true);
    titleLabel->setFont(font);
    layout->addWidget(titleLabel);

    // Create a default empty inspector widget
    currentInspectorWidget = new InspectorWidget(this);
    layout->addWidget(currentInspectorWidget);

    layout->addStretch();

    setLayout(layout);
    setMaximumWidth(250);
}

void Inspector::setSelectedObject(QGraphicsItem *item)
{
    // Remove old widget
    if (currentInspectorWidget) {
        currentInspectorWidget->deleteLater();
    }

    // Create new widget based on item type
    currentInspectorWidget = InspectorWidgetFactory::create(item, undoStack, this);

    auto *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        // Clear and rebuild
        while (layout->count() > 0) {
            layout->takeAt(0);
        }

        auto *titleLabel = new QLabel(tr("Inspector"), this);
        auto font = titleLabel->font();
        font.setBold(true);
        titleLabel->setFont(font);
        layout->addWidget(titleLabel);

        layout->addWidget(currentInspectorWidget);
        layout->addStretch();
    }
}

