#ifndef VIEW_HPP
#define VIEW_HPP

#include <QGraphicsItem>
#include <QString>
#include <QPointF>

class View : public QGraphicsItem
{
    friend class Canvas;
public:
    explicit View(const QPointF &position, const QString &id, const QString &formula = "", QGraphicsItem *parent = nullptr);

    const QString &id() const { return _id; }
    const QString &formula() const { return _formula; }
    void setFormula(const QString &newFormula) { _formula = newFormula; }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString _id;
    QString _formula;
};

#endif // VIEW_HPP
