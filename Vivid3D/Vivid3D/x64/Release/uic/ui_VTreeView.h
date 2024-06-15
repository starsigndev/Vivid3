/********************************************************************************
** Form generated from reading UI file 'VTreeView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTREEVIEW_H
#define UI_VTREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTreeViewClass
{
public:

    void setupUi(QWidget *VTreeViewClass)
    {
        if (VTreeViewClass->objectName().isEmpty())
            VTreeViewClass->setObjectName("VTreeViewClass");
        VTreeViewClass->resize(600, 400);

        retranslateUi(VTreeViewClass);

        QMetaObject::connectSlotsByName(VTreeViewClass);
    } // setupUi

    void retranslateUi(QWidget *VTreeViewClass)
    {
        VTreeViewClass->setWindowTitle(QCoreApplication::translate("VTreeViewClass", "VTreeView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTreeViewClass: public Ui_VTreeViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTREEVIEW_H
