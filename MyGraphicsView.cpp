#include "MyGraphicsView.h"
    #include "widget.h"
#include <QPointF>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(0, 0, 400, 400);
    this->setScene(scene);

}

void MyGraphicsView::mousePressEvent(QMouseEvent * e) {
    QPointF point = mapToScene(e->pos());
    qDebug() << "x~=" << point.x () << " y=" << point.y ();
}
void MyGraphicsView::mouseMoveEvent (QMouseEvent *move)
{
    QPointF movment;
    movment = mapToScene (move->pos ());
    emit sendMousePoint (movment);
    qDebug() << "x=" << movment.x () << " y=" << movment.y ();
    delete (&movment);

}
