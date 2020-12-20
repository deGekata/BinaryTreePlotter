#ifndef CUSTOMQGRAPHICSSCENE_H
#define CUSTOMQGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <univertex.h>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
class CustomQGraphicsScene : public QGraphicsScene
{

    Q_OBJECT

signals:
    void sig(int num);
public:
//    Widget* widj;
protected:
   bool pressed = false;
   QPointF prev;
   void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CUSTOMQGRAPHICSSCENE_H
