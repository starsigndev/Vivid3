/********************************************************************************
** Form generated from reading UI file 'VMainMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMAINMENU_H
#define UI_VMAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VMainMenuClass
{
public:

    void setupUi(QWidget *VMainMenuClass)
    {
        if (VMainMenuClass->objectName().isEmpty())
            VMainMenuClass->setObjectName("VMainMenuClass");
        VMainMenuClass->resize(600, 400);

        retranslateUi(VMainMenuClass);

        QMetaObject::connectSlotsByName(VMainMenuClass);
    } // setupUi

    void retranslateUi(QWidget *VMainMenuClass)
    {
        VMainMenuClass->setWindowTitle(QCoreApplication::translate("VMainMenuClass", "VMainMenu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VMainMenuClass: public Ui_VMainMenuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMAINMENU_H
