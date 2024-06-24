/********************************************************************************
** Form generated from reading UI file 'VCinemaEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCINEMAEDITOR_H
#define UI_VCINEMAEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VCinemaEditorClass
{
public:

    void setupUi(QWidget *VCinemaEditorClass)
    {
        if (VCinemaEditorClass->objectName().isEmpty())
            VCinemaEditorClass->setObjectName("VCinemaEditorClass");
        VCinemaEditorClass->resize(600, 400);

        retranslateUi(VCinemaEditorClass);

        QMetaObject::connectSlotsByName(VCinemaEditorClass);
    } // setupUi

    void retranslateUi(QWidget *VCinemaEditorClass)
    {
        VCinemaEditorClass->setWindowTitle(QCoreApplication::translate("VCinemaEditorClass", "VCinemaEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VCinemaEditorClass: public Ui_VCinemaEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCINEMAEDITOR_H
