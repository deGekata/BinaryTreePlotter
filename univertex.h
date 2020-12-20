#ifndef UNIVERTEX_H
#define UNIVERTEX_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <Tree.h>
#include <QBrush>
class UniVertex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    UniVertex();
    int height, width, value, color;
    QBrush* br = new QBrush("red");
    QRectF boundingRect() const override;
    UniVertex(int w, int h): height(h), width(w){};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // UNIVERTEX_H
