#include "ViewInspectorWidget.hpp"
#include "Canvas.hpp"
#include "View.hpp"
#include "UpdateViewCommand.hpp"

#include <QLineEdit>
#include <QPlainTextEdit>
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
    formulaEdit->clear();
    idEdit->setEnabled(false);
    formulaEdit->setEnabled(false);
}

void ViewInspectorWidget::updateUI()
{
    updating = true;

    idEdit->setStyleSheet(""); // Reset style

    if (view) {
        idEdit->setText(view->id());
        idEdit->setEnabled(true);

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
    QString newFormula = formulaEdit->toPlainText();

    if (!canvas->canSetViewId(view, newId)) {
        idEdit->setStyleSheet("QLineEdit { background-color: #ff9999; }");
        idEdit->setToolTip(tr("ID already in use"));
        return;
    }

    undoStack->push(new UpdateViewCommand(canvas, view, newId, newFormula));
    updateUI();
}
