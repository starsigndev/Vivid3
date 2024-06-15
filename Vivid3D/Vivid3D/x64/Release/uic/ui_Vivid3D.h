/********************************************************************************
** Form generated from reading UI file 'Vivid3D.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIVID3D_H
#define UI_VIVID3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Vivid3DClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Vivid3DClass)
    {
        if (Vivid3DClass->objectName().isEmpty())
            Vivid3DClass->setObjectName("Vivid3DClass");
        Vivid3DClass->resize(600, 400);
        menuBar = new QMenuBar(Vivid3DClass);
        menuBar->setObjectName("menuBar");
        Vivid3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Vivid3DClass);
        mainToolBar->setObjectName("mainToolBar");
        Vivid3DClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Vivid3DClass);
        centralWidget->setObjectName("centralWidget");
        Vivid3DClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Vivid3DClass);
        statusBar->setObjectName("statusBar");
        Vivid3DClass->setStatusBar(statusBar);

        retranslateUi(Vivid3DClass);

        QMetaObject::connectSlotsByName(Vivid3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *Vivid3DClass)
    {
        Vivid3DClass->setWindowTitle(QCoreApplication::translate("Vivid3DClass", "Vivid3D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Vivid3DClass: public Ui_Vivid3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIVID3D_H
