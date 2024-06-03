/********************************************************************************
** Form generated from reading UI file 'VPropertyEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VPROPERTYEDITOR_H
#define UI_VPROPERTYEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VPropertyEditorClass
{
public:

    void setupUi(QWidget *VPropertyEditorClass)
    {
        if (VPropertyEditorClass->objectName().isEmpty())
            VPropertyEditorClass->setObjectName("VPropertyEditorClass");
        VPropertyEditorClass->resize(600, 400);

        retranslateUi(VPropertyEditorClass);

        QMetaObject::connectSlotsByName(VPropertyEditorClass);
    } // setupUi

    void retranslateUi(QWidget *VPropertyEditorClass)
    {
        VPropertyEditorClass->setWindowTitle(QCoreApplication::translate("VPropertyEditorClass", "VPropertyEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VPropertyEditorClass: public Ui_VPropertyEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VPROPERTYEDITOR_H
