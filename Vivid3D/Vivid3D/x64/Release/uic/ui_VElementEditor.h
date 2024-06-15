/********************************************************************************
** Form generated from reading UI file 'VElementEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VELEMENTEDITOR_H
#define UI_VELEMENTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VElementEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VElementEditorClass)
    {
        if (VElementEditorClass->objectName().isEmpty())
            VElementEditorClass->setObjectName("VElementEditorClass");
        VElementEditorClass->resize(600, 400);
        menuBar = new QMenuBar(VElementEditorClass);
        menuBar->setObjectName("menuBar");
        VElementEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VElementEditorClass);
        mainToolBar->setObjectName("mainToolBar");
        VElementEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(VElementEditorClass);
        centralWidget->setObjectName("centralWidget");
        VElementEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VElementEditorClass);
        statusBar->setObjectName("statusBar");
        VElementEditorClass->setStatusBar(statusBar);

        retranslateUi(VElementEditorClass);

        QMetaObject::connectSlotsByName(VElementEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *VElementEditorClass)
    {
        VElementEditorClass->setWindowTitle(QCoreApplication::translate("VElementEditorClass", "VElementEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VElementEditorClass: public Ui_VElementEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VELEMENTEDITOR_H
