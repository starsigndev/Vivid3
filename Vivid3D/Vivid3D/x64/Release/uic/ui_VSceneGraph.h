/********************************************************************************
** Form generated from reading UI file 'VSceneGraph.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VSCENEGRAPH_H
#define UI_VSCENEGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VSceneGraphClass
{
public:

    void setupUi(QWidget *VSceneGraphClass)
    {
        if (VSceneGraphClass->objectName().isEmpty())
            VSceneGraphClass->setObjectName("VSceneGraphClass");
        VSceneGraphClass->resize(600, 400);

        retranslateUi(VSceneGraphClass);

        QMetaObject::connectSlotsByName(VSceneGraphClass);
    } // setupUi

    void retranslateUi(QWidget *VSceneGraphClass)
    {
        VSceneGraphClass->setWindowTitle(QCoreApplication::translate("VSceneGraphClass", "VSceneGraph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VSceneGraphClass: public Ui_VSceneGraphClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VSCENEGRAPH_H
