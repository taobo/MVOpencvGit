/********************************************************************************
** Form generated from reading UI file 'myclass.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLASS_H
#define UI_MYCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyClassClass
{
public:
    QWidget *centralWidget;
    QPushButton *OpenImage;
    QPushButton *ProcessImage;
    QLabel *Original;
    QLabel *Process;
    QSlider *horizontalSlider;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyClassClass)
    {
        if (MyClassClass->objectName().isEmpty())
            MyClassClass->setObjectName(QString::fromUtf8("MyClassClass"));
        MyClassClass->resize(1050, 700);
        centralWidget = new QWidget(MyClassClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OpenImage = new QPushButton(centralWidget);
        OpenImage->setObjectName(QString::fromUtf8("OpenImage"));
        OpenImage->setGeometry(QRect(130, 60, 220, 90));
        ProcessImage = new QPushButton(centralWidget);
        ProcessImage->setObjectName(QString::fromUtf8("ProcessImage"));
        ProcessImage->setGeometry(QRect(680, 60, 220, 90));
        Original = new QLabel(centralWidget);
        Original->setObjectName(QString::fromUtf8("Original"));
        Original->setGeometry(QRect(20, 210, 480, 360));
        Process = new QLabel(centralWidget);
        Process->setObjectName(QString::fromUtf8("Process"));
        Process->setGeometry(QRect(550, 210, 480, 360));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 580, 1010, 30));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(1000);
        horizontalSlider->setOrientation(Qt::Horizontal);
        MyClassClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyClassClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1050, 30));
        MyClassClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyClassClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyClassClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyClassClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyClassClass->setStatusBar(statusBar);

        retranslateUi(MyClassClass);
        QObject::connect(OpenImage, SIGNAL(clicked()), MyClassClass, SLOT(on_OpenImage_clicked()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), MyClassClass, SLOT(on_SliderValue_changed(int)));
        QObject::connect(ProcessImage, SIGNAL(clicked()), MyClassClass, SLOT(on_ProcessImage_changed()));

        QMetaObject::connectSlotsByName(MyClassClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyClassClass)
    {
        MyClassClass->setWindowTitle(QApplication::translate("MyClassClass", "MyClass", 0, QApplication::UnicodeUTF8));
        OpenImage->setText(QApplication::translate("MyClassClass", "Open Image", 0, QApplication::UnicodeUTF8));
        ProcessImage->setText(QApplication::translate("MyClassClass", "Process Image", 0, QApplication::UnicodeUTF8));
        Original->setText(QString());
        Process->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyClassClass: public Ui_MyClassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLASS_H
