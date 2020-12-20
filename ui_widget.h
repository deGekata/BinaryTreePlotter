/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGraphicsView *graphicsView;
    QWidget *horizontalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *next_tree;
    QPushButton *add_element;
    QPushButton *add_range;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(909, 610);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(9, 9, 711, 601));
        graphicsView->setMouseTracking(true);
        graphicsView->setMidLineWidth(0);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setInteractive(true);
        graphicsView->setSceneRect(QRectF(0, 0, 300, 303));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemShape);
        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(730, 10, 171, 331));
        verticalLayout = new QVBoxLayout(horizontalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        next_tree = new QPushButton(horizontalLayoutWidget);
        next_tree->setObjectName(QString::fromUtf8("next_tree"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(next_tree->sizePolicy().hasHeightForWidth());
        next_tree->setSizePolicy(sizePolicy);
        next_tree->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-style:solid;\n"
"	font-size: 10pt;\n"
"	background-color: #5557CF;\n"
"	color:#fff;\n"
"	border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	color:#fff;\n"
"	font-size: 10pt;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(50, 51, 122, 255), stop:0.505682 rgba(20, 20, 50, 255), stop:1 rgba(50, 51, 122, 255));\n"
"	border-color:#2d89ef;\n"
"	border-width:2px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	font-size: 8pt;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"}"));

        verticalLayout->addWidget(next_tree);

        add_element = new QPushButton(horizontalLayoutWidget);
        add_element->setObjectName(QString::fromUtf8("add_element"));
        sizePolicy.setHeightForWidth(add_element->sizePolicy().hasHeightForWidth());
        add_element->setSizePolicy(sizePolicy);
        add_element->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-size: 10pt;\n"
"border-style:solid;\n"
"\n"
"background-color:#3d3d3d;\n"
"color:#fff;\n"
"border-radius:7px;\n"
"}\n"
"QPushButton:hover{\n"
"color:#ccc;\n"
"font-size: 10pt;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(45, 45, 45, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"	border-color:#2d89ef;\n"
"border-width:2px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"font-size: 8pt;\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"}"));

        verticalLayout->addWidget(add_element);

        add_range = new QPushButton(horizontalLayoutWidget);
        add_range->setObjectName(QString::fromUtf8("add_range"));
        add_range->setEnabled(true);
        sizePolicy.setHeightForWidth(add_range->sizePolicy().hasHeightForWidth());
        add_range->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        add_range->setFont(font);
        add_range->setAutoFillBackground(false);
        add_range->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-style:solid;\n"
"	font-size:12pt;\n"
"	background-color:#8C2F30;\n"
"	color: #fff;\n"
"	border-radius:7px;\n"
"}\n"
"QPushButton:hover{\n"
"	color:#fff;\n"
"	font-size:12pt;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(67, 21, 21, 255), stop:0.505682 rgba(87, 24, 24, 255), stop:1 rgba(67, 21, 21, 255));\n"
"	border-color:#2d89ef;\n"
"	border-width:2px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	font-size:10pt;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"}"));
        add_range->setAutoDefault(false);
        add_range->setFlat(false);

        verticalLayout->addWidget(add_range);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        next_tree->setText(QApplication::translate("Widget", "Next tree", nullptr));
        add_element->setText(QApplication::translate("Widget", "Add element", nullptr));
        add_range->setText(QApplication::translate("Widget", "Add random range", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
