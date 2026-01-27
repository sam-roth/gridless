#ifndef INSPECTORWIDGET_HPP
#define INSPECTORWIDGET_HPP

#include <QWidget>

class QGraphicsItem;

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    virtual ~InspectorWidget() = default;

    virtual void setObject(QGraphicsItem *item);
    virtual void clear();

protected:
    QGraphicsItem *currentObject;
};

#endif // INSPECTORWIDGET_HPP
