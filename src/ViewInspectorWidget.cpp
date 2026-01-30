#include "ViewInspectorWidget.hpp"
#include "Canvas.hpp"
#include "View.hpp"
#include "UpdateViewCommand.hpp"

#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QUndoStack>

ViewInspectorWidget::ViewInspectorWidget(Canvas *canvas, QUndoStack *undoStack, QWidget *parent)
    : InspectorWidget(parent), canvas(canvas), undoStack(undoStack), view(nullptr), updating(false)
{
    auto *layout = new QFormLayout(this);

    // ID property
    idEdit = new QLineEdit(this);
    layout->addRow(tr("ID"), idEdit);
    connect(idEdit, &QLineEdit::editingFinished, this, &ViewInspectorWidget::onChanged);

    // X position
    xSpinBox = new QDoubleSpinBox(this);
    xSpinBox->setRange(-10000, 10000);
    layout->addRow(tr("X"), xSpinBox);
    connect(xSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &ViewInspectorWidget::onChanged);

    // Y position
    ySpinBox = new QDoubleSpinBox(this);
    ySpinBox->setRange(-10000, 10000);
    layout->addRow(tr("Y"), ySpinBox);
    connect(ySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &ViewInspectorWidget::onChanged);

    // Formula property
    formulaEdit = new QPlainTextEdit(this);
    formulaEdit->setMaximumHeight(100);
    layout->addRow(tr("Formula"), formulaEdit);
    connect(formulaEdit, &QPlainTextEdit::textChanged, this, &ViewInspectorWidget::onChanged);

    setLayout(layout);
}

void ViewInspectorWidget::setObject(QGraphicsItem *item)
{
    view = dynamic_cast<View *>(item);
    updateUI();
}

void ViewInspectorWidget::clear()
{
    view = nullptr;
    idEdit->clear();
    xSpinBox->setValue(0);
    ySpinBox->setValue(0);
    formulaEdit->clear();
    idEdit->setEnabled(false);
    xSpinBox->setEnabled(false);
    ySpinBox->setEnabled(false);
    formulaEdit->setEnabled(false);
}

void ViewInspectorWidget::updateUI()
{
    updating = true;

    idEdit->setStyleSheet(""); // Reset style

    if (view) {
        idEdit->setText(view->id());
        idEdit->setEnabled(true);

        QPointF pos = view->pos();
        xSpinBox->setValue(pos.x());
        ySpinBox->setValue(pos.y());
        xSpinBox->setEnabled(true);
        ySpinBox->setEnabled(true);

        formulaEdit->setPlainText(view->formula());
        formulaEdit->setEnabled(true);
    } else {
        clear();
    }

    updating = false;
}

void ViewInspectorWidget::onChanged()
{
    if (!view || updating) {
        return;
    }

    QString newId = idEdit->text();
    QPointF newPos(xSpinBox->value(), ySpinBox->value());
    QString newFormula = formulaEdit->toPlainText();

    if (!canvas->canSetViewId(view, newId)) {
        idEdit->setStyleSheet("QLineEdit { background-color: #ff9999; }");
        idEdit->setToolTip(tr("ID already in use"));
        return;
    }

    undoStack->push(new UpdateViewCommand(canvas, view, newId, newFormula, newPos));
    updateUI();
}
