#include "CustomQGraphicsScene.h"
#include <QPainter>


void CustomQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    //qDebug() << "in";
    if (mouseEvent->button() == Qt::LeftButton)
    {

        QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());// it is your clicked item, you can do everything what you want. for example send it somewhere
        UniVertex *vert = dynamic_cast<UniVertex *>(item);
        if(vert != nullptr)
        {
            qDebug() << "   eeeeell" << vert->value;
              emit sig(vert->value);
//            vert->br->setColor("yellow");

        } else{
            pressed = true;
            prev = mouseEvent->pos();
            qDebug() << "  notffsdfa ell" << mouseEvent->scenePos();
        }
    }

}

void CustomQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(false){

        qreal dx, dy;
        dx = event->pos().rx() - prev.rx();
        dy = event->pos().ry() - prev.ry();
        QRectF rct = sceneRect();
                qDebug() << rct;
        rct.moveTo(0, 0);
        qDebug() << rct;
//        this->setSceneRect()
        this->setSceneRect(-180, -90, 360, 180);
        this->setSceneRect(0.0, 0.0, 600.0, 600.0);
//        this->sceneRect().setX(this->sceneRect().x() + dx);
//        this->sceneRect().setY(this->sceneRect().y() + dy);
    }
}

void CustomQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}
