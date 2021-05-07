#include "widget.h"
#include "ui_widget.h"
#include <univertex.h>
#include <CustomQGraphicsScene.h>
/* Function to get a random number in the range from minimum to maximum
 * */

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new CustomQGraphicsScene();
    //    scene->widj = this;
        scene->setSceneRect(5000, -5000, 10000, 10000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    UnitedVertexForm* vert;
    if(tree_ind == 0){
        vert = avl.get_unitedTree();
    } else if(tree_ind == 1){
        vert = rb.get_unitedTree();
    } else {
        vert = curevo.get_unitedTree();
    }

    qDebug() << vert;
    UnitedVertexForm::calc_size(vert);
//    UnitedVertexForm::prUniTree(vert);
    drawTree(vert, QPointF(20000, 0), 1, true);
//    ui->graphicsView->resetTransform();
//    ui->graphicsView->scale(scale, scale);

    //    scene->itemAt(
    //    this->resize(640,640);
    //    this->setFixedSize(640,640);
    //    scene = new GraphicsScene();   // Init graphics scene
    //    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //    ui->graphicsView->resize(600,600);
    //    ui->graphicsView->setScene(scene);
    //    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //    scene->setSceneRect(0,0,500,500);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Equal){
        if(scale < qreal(100)){
            ui->graphicsView->resetTransform();
            scale+=1;
            ui->graphicsView->scale(scale, scale);
            return;
        }
    } else if (event->key() == Qt::Key_Minus){
        if(scale > qreal(0.1)){
            scale-=0.01;
            ui->graphicsView->resetTransform();
            ui->graphicsView->scale(scale, scale);
            update();
            return;
        }
    }
}


void Widget::drawTree(UnitedVertexForm* vertex, QPointF pos, bool L, bool rt){
    if(vertex != nullptr){
        UniVertex* elem = new UniVertex(90, 90);
        elem->value = vertex->values;
        elem->setZValue(1);
        elem->color = vertex->color;
        if(L){
            elem->setPos(pos.rx() - vertex->rightsize * elem->width / 3 - elem->width,
                         pos.ry() + elem->height * 4 / 3);
        } else {
            elem->setPos(pos.rx() + vertex->leftsize * elem->width / 3 + elem->width ,
                         pos.ry() + elem->height * 4 / 3);
        }
        if(!rt){
            QGraphicsLineItem* ln = new QGraphicsLineItem(elem->pos().rx() + elem->width / 2, elem->pos().ry(),
                                                          pos.rx() + elem->width / 2, pos.ry() + elem->height);
            ln->setZValue(0);
            ln->setPen(QPen(QBrush("black"), 4));
            scene->addItem(ln);
        }
        scene->addItem(elem);
        drawTree(vertex->left, elem->pos(), 1);
        drawTree(vertex->right, elem->pos(), 0);
    }
}


void Widget::on_add_range_released(){
    bool ok;
    int i = QInputDialog::getInt(this, QString::fromUtf8("Enter range"),
                                 QString::fromUtf8("Max num:"), 25, 1, 1000000, 1, &ok);
    if (ok){
        std::random_device rd{};
        std::mt19937 engine{rd()};
        for(int iter = 0; iter < i; ++iter){
            int num = engine() % 4000000 - 2000000;
            avl.push(num);
            rb.push(num);
            curevo.push(num);
        }
        UnitedVertexForm* vert;
        if(tree_ind == 0){
            vert = avl.get_unitedTree();
        } else if(tree_ind == 1){
            vert = rb.get_unitedTree();
        } else {
            vert = curevo.get_unitedTree();
        }

        qDebug() << vert;
        UnitedVertexForm::calc_size(vert);
//        UnitedVertexForm::prUniTree(vert);
        ui->graphicsView->scene()->clear();
        drawTree(vert, QPointF(ui->graphicsView->scene()->width() / 2 + 2000 , ui->graphicsView->scene()->width() / 2), 1, true);
//        ui->graphicsView->resetTransform();
//        ui->graphicsView->scale(scale, scale);

    }

};

void Widget::on_add_element_released(){
    bool ok;
    ui->graphicsView->translate(100, 0);
    x+=100;
//    y+=100;
    /*
    int i = QInputDialog::getInt(this, QString::fromUtf8("Enter num"),
                                 QString::fromUtf8("Your num:"), 0, -2000000, 2000000, 1, &ok);
    if (ok){
        int num = i;
        avl.push(num);
        rb.push(num);
        curevo.push(num);
        UnitedVertexForm* vert;
        if(tree_ind == 0){
            vert = avl.get_unitedTree();
        } else if(tree_ind == 1){
            vert = rb.get_unitedTree();
        } else {
            vert = curevo.get_unitedTree();
        }

        qDebug() << vert;
        UnitedVertexForm::calc_size(vert);
        UnitedVertexForm::prUniTree(vert);
        ui->graphicsView->scene()->clear();
        drawTree(vert, QPointF(2000, 0), 1, true);
        ui->graphicsView->resetTransform();
        ui->graphicsView->scale(scale, scale);
    }
    */

};

void Widget::on_next_tree_released(){
    ++tree_ind;
    tree_ind %= 3;
    UnitedVertexForm* vert;
    if(tree_ind == 0){
        vert = avl.get_unitedTree();
    } else if(tree_ind == 1){
        vert = rb.get_unitedTree();
    } else {
        vert = curevo.get_unitedTree();
    }
    qDebug() << vert;
    UnitedVertexForm::calc_size(vert);
//    UnitedVertexForm::prUniTree(vert);
    ui->graphicsView->scene()->clear();

    drawTree(vert, QPointF(15000, 0), 1, true);
//    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(100, 100);
};



void Widget::delete_vertex(int elem){
    avl.pop(elem);
    rb.pop(elem);
    curevo.pop(elem);
    UnitedVertexForm* vert;
    if(tree_ind == 0){
        vert = avl.get_unitedTree();
    } else if(tree_ind == 1){
        vert = rb.get_unitedTree();
    } else {
        vert = curevo.get_unitedTree();
    }

    qDebug() << vert;
    UnitedVertexForm::calc_size(vert);
//    UnitedVertexForm::prUniTree(vert);
    ui->graphicsView->scene()->clear();
    drawTree(vert, QPointF(2000, 0), 1, true);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(scale, scale);
};
