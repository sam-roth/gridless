#include "PointInspectorWidget.hpp"
#include "Point.hpp"
#include "UpdatePointCommand.hpp"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QUndoStack>

PointInspectorWidget::PointInspectorWidget(QUndoStack *undoStack, QWidget *parent)
    : InspectorWidget(parent), undoStack(undoStack), point(nullptr), updating(false)
{
    auto *layout = new QFormLayout(this);

    // ID property
    idEdit = new QLineEdit(this);
    layout->addRow(tr("ID"), idEdit);
    connect(idEdit, &QLineEdit::editingFinished, this, &PointInspectorWidget::onIdChanged);

    // X position
    xSpinBox = new QDoubleSpinBox(this);
    xSpinBox->setRange(-10000, 10000);
    layout->addRow(tr("X"), xSpinBox);
    connect(xSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &PointInspectorWidget::onPositionChanged);

    // Y position
    ySpinBox = new QDoubleSpinBox(this);
    ySpinBox->setRange(-10000, 10000);
    layout->addRow(tr("Y"), ySpinBox);
    connect(ySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &PointInspectorWidget::onPositionChanged);

    setLayout(layout);
}

void PointInspectorWidget::setObject(QGraphicsItem *item)
{
    point = dynamic_cast<Point *>(item);
    updateUI();
}

void PointInspectorWidget::clear()
{
    point = nullptr;
    idEdit->clear();
    xSpinBox->setValue(0);
    ySpinBox->setValue(0);
    idEdit->setEnabled(false);
    xSpinBox->setEnabled(false);
    ySpinBox->setEnabled(false);
}

void PointInspectorWidget::updateUI()
{
    updating = true;

    if (point) {
        idEdit->setText(point->getId());
        idEdit->setEnabled(true);

        QPointF pos = point->pos();
        xSpinBox->setValue(pos.x());
        ySpinBox->setValue(pos.y());
        xSpinBox->setEnabled(true);
        ySpinBox->setEnabled(true);
    } else {
        clear();
    }

    updating = false;
}

void PointInspectorWidget::onIdChanged()
{
    if (!point || updating) {
        return;
    }

    QString newId = idEdit->text();
    if (newId != point->getId()) {
        undoStack->push(new UpdatePointCommand(point, newId, point->pos()));
        updateUI();
    }
}

void PointInspectorWidget::onPositionChanged()
{
    if (!point || updating) {
        return;
    }

    QPointF newPos(xSpinBox->value(), ySpinBox->value());
    if (newPos != point->pos()) {
        undoStack->push(new UpdatePointCommand(point, point->getId(), newPos));
        updateUI();
    }
}
