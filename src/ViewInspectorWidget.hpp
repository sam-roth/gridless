#ifndef VIEWINSPECTORWIDGET_HPP
#define VIEWINSPECTORWIDGET_HPP

#include "InspectorWidget.hpp"

class QLineEdit;
class QPlainTextEdit;
class QUndoStack;

class Canvas;
class View;

class ViewInspectorWidget : public InspectorWidget
{
    Q_OBJECT
public:
    explicit ViewInspectorWidget(Canvas *canvas, QUndoStack *undoStack, QWidget *parent = nullptr);

    void setObject(QGraphicsItem *item) override;
    void clear() override;

private slots:
    void onChanged();

private:
    void updateUI();

    Canvas *canvas;
    QUndoStack *undoStack;
    View *view;
    QLineEdit *idEdit;
    QPlainTextEdit *formulaEdit;
    bool updating;
};

#endif // VIEWINSPECTORWIDGET_HPP
