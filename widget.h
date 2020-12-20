#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <CustomQGraphicsScene.h>
#include <QQueue>
#include <QGraphicsEllipseItem>
#include <MyGraphicsView.h>
#include <RBTree.h>
#include <AVLTree.h>
#include <CurevoTree.h>
#include <QtGui>
#include <QInputDialog>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    void drawTree(UnitedVertexForm* vertex, QPointF pos, bool L, bool rt = false);

    CustomQGraphicsScene* scene;
public slots:
    void delete_vertex(int elem);
private slots:
    void keyReleaseEvent(QKeyEvent *event);
    void on_add_range_released();
    void on_add_element_released();
    void on_next_tree_released();
//    void Mo

private:
    int tree_ind = 0;
    AVLTree avl;
    RBTree rb;
    CurevoTree curevo;
    qreal scale = 1;
    QQueue<UniVertex*> all_vertex;
    Ui::Widget *ui;
};

#endif // WIDGET_H
