/********************************************************************************
** Form generated from reading UI file 'VTools.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTOOLS_H
#define UI_VTOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VToolsClass
{
public:

    void setupUi(QWidget *VToolsClass)
    {
        if (VToolsClass->objectName().isEmpty())
            VToolsClass->setObjectName("VToolsClass");
        VToolsClass->resize(600, 400);

        retranslateUi(VToolsClass);

        QMetaObject::connectSlotsByName(VToolsClass);
    } // setupUi

    void retranslateUi(QWidget *VToolsClass)
    {
        VToolsClass->setWindowTitle(QCoreApplication::translate("VToolsClass", "VTools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VToolsClass: public Ui_VToolsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTOOLS_H
