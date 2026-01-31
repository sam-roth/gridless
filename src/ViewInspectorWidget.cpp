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
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QShortcut>

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

    auto *formulaWidget = new QWidget(this);
    auto *formulaLayout = new QVBoxLayout(formulaWidget);
    formulaLayout->setContentsMargins(0, 0, 0, 0);
    formulaLayout->addWidget(formulaEdit);

    auto *buttonLayout = new QHBoxLayout();
    commitFormulaButton = new QPushButton(tr("Commit"), this);
    commitFormulaButton->setToolTip(tr("Commit formula changes (Ctrl+Return)"));
    revertFormulaButton = new QPushButton(tr("Revert"), this);
    revertFormulaButton->setToolTip(tr("Revert formula changes (Esc)"));

    buttonLayout->addStretch();
    buttonLayout->addWidget(commitFormulaButton);
    buttonLayout->addWidget(revertFormulaButton);
    formulaLayout->addLayout(buttonLayout);

    layout->addRow(tr("Formula"), formulaWidget);
    connect(formulaEdit, &QPlainTextEdit::textChanged, this, &ViewInspectorWidget::updateFormulaButtonStates);
    connect(commitFormulaButton, &QPushButton::clicked, this, &ViewInspectorWidget::commitFormula);
    connect(revertFormulaButton, &QPushButton::clicked, this, &ViewInspectorWidget::revertFormula);

    // Keyboard shortcuts for formula editing
    auto *commitShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Return), this);
    connect(commitShortcut, &QShortcut::activated, this, &ViewInspectorWidget::commitFormula);

    auto *revertShortcut = new QShortcut(Qt::Key_Escape, formulaEdit);
    connect(revertShortcut, &QShortcut::activated, this, &ViewInspectorWidget::revertFormula);

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
    commitFormulaButton->setEnabled(false);
    revertFormulaButton->setEnabled(false);
    lastCommittedFormula.clear();
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

        lastCommittedFormula = view->formula();
        formulaEdit->setPlainText(lastCommittedFormula);
        formulaEdit->setEnabled(true);
        updateFormulaButtonStates();
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
    QString newFormula = lastCommittedFormula; // Use last committed formula, not the edited one

    if (!canvas->canSetViewId(view, newId)) {
        idEdit->setStyleSheet("QLineEdit { background-color: #ff9999; }");
        idEdit->setToolTip(tr("ID already in use"));
        return;
    }

    undoStack->push(new UpdateViewCommand(canvas, view, newId, newFormula, newPos));
    updateUI();
}

void ViewInspectorWidget::commitFormula()
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

void ViewInspectorWidget::revertFormula()
{
    if (!view) {
        return;
    }

    formulaEdit->setPlainText(lastCommittedFormula);
    updateFormulaButtonStates();
}

void ViewInspectorWidget::updateFormulaButtonStates()
{
    if (!view) {
        commitFormulaButton->setEnabled(false);
        revertFormulaButton->setEnabled(false);
        return;
    }

    QString currentFormula = formulaEdit->toPlainText();
    bool hasChanges = currentFormula != lastCommittedFormula;
    commitFormulaButton->setEnabled(hasChanges);
    revertFormulaButton->setEnabled(hasChanges);
}
