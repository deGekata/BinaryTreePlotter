#include "widget.h"
#include <RBTree.h>
#include <AVLTree.h>
#include <CurevoTree.h>
#include <QApplication>
#include <iostream>
#include <QDebug>
using namespace std;
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    Widget* w = new Widget;
    QObject::connect(w->scene, SIGNAL(sig(int)), w, SLOT(delete_vertex(int)));
    w->show();
    return a.exec();
}
