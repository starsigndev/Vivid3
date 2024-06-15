/********************************************************************************
** Form generated from reading UI file 'VPropEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VPROPEDITOR_H
#define UI_VPROPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VPropEditorClass
{
public:

    void setupUi(QWidget *VPropEditorClass)
    {
        if (VPropEditorClass->objectName().isEmpty())
            VPropEditorClass->setObjectName("VPropEditorClass");
        VPropEditorClass->resize(600, 400);

        retranslateUi(VPropEditorClass);

        QMetaObject::connectSlotsByName(VPropEditorClass);
    } // setupUi

    void retranslateUi(QWidget *VPropEditorClass)
    {
        VPropEditorClass->setWindowTitle(QCoreApplication::translate("VPropEditorClass", "VPropEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VPropEditorClass: public Ui_VPropEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VPROPEDITOR_H
