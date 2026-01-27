#ifndef POINTINSPECTORWIDGET_HPP
#define POINTINSPECTORWIDGET_HPP

#include "InspectorWidget.hpp"

class QLineEdit;
class QDoubleSpinBox;
class Point;
class QUndoStack;

class PointInspectorWidget : public InspectorWidget
{
    Q_OBJECT
public:
    explicit PointInspectorWidget(QUndoStack *undoStack, QWidget *parent = nullptr);

    void setObject(QGraphicsItem *item) override;
    void clear() override;

private slots:
    void onChanged();

private:
    void updateUI();

    QUndoStack *undoStack;
    Point *point;
    QLineEdit *idEdit;
    QDoubleSpinBox *xSpinBox;
    QDoubleSpinBox *ySpinBox;
    bool updating;
};

#endif // POINTINSPECTORWIDGET_HPP
