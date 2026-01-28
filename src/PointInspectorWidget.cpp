#include "PointInspectorWidget.hpp"
#include "Canvas.hpp"
#include "Point.hpp"
#include "UpdatePointCommand.hpp"

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QUndoStack>

PointInspectorWidget::PointInspectorWidget(Canvas *canvas, QUndoStack *undoStack, QWidget *parent)
    : InspectorWidget(parent), canvas(canvas), undoStack(undoStack), point(nullptr), updating(false)
{
    auto *layout = new QFormLayout(this);

    // ID property
    idEdit = new QLineEdit(this);
    layout->addRow(tr("ID"), idEdit);
    connect(idEdit, &QLineEdit::editingFinished, this, &PointInspectorWidget::onChanged);

    // X position
    xSpinBox = new QDoubleSpinBox(this);
    xSpinBox->setRange(-10000, 10000);
    layout->addRow(tr("X"), xSpinBox);
    connect(xSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &PointInspectorWidget::onChanged);

    // Y position
    ySpinBox = new QDoubleSpinBox(this);
    ySpinBox->setRange(-10000, 10000);
    layout->addRow(tr("Y"), ySpinBox);
    connect(ySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &PointInspectorWidget::onChanged);

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

    idEdit->setStyleSheet(""); // Reset style

    if (point) {
        idEdit->setText(point->id());
        idEdit->setEnabled(true);

        QPointF pos = point->pos();
        xSpinBox->setValue(pos.x());
        ySpinBox->setValue(pos.y());
        xSpinBox->setEnabled(true);
        ySpinBox->setEnabled(true);
        // validator->point = point;
    } else {
        clear();
    }

    updating = false;
}

void PointInspectorWidget::onChanged()
{
    if (!point || updating) {
        return;
    }

    QPointF newPos(xSpinBox->value(), ySpinBox->value());
    QString newId = idEdit->text();

    if (!canvas->canSetPointId(point, newId)) {
        idEdit->setStyleSheet("QLineEdit { background-color: #ff9999; }");
        idEdit->setToolTip(tr("ID already in use"));
        return;
    }

    undoStack->push(new UpdatePointCommand(canvas, point, newId, newPos));
    updateUI();
}
