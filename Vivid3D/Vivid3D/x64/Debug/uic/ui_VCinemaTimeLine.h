/********************************************************************************
** Form generated from reading UI file 'VCinemaTimeLine.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCINEMATIMELINE_H
#define UI_VCINEMATIMELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VCinemaTimeLineClass
{
public:

    void setupUi(QWidget *VCinemaTimeLineClass)
    {
        if (VCinemaTimeLineClass->objectName().isEmpty())
            VCinemaTimeLineClass->setObjectName("VCinemaTimeLineClass");
        VCinemaTimeLineClass->resize(600, 400);

        retranslateUi(VCinemaTimeLineClass);

        QMetaObject::connectSlotsByName(VCinemaTimeLineClass);
    } // setupUi

    void retranslateUi(QWidget *VCinemaTimeLineClass)
    {
        VCinemaTimeLineClass->setWindowTitle(QCoreApplication::translate("VCinemaTimeLineClass", "VCinemaTimeLine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VCinemaTimeLineClass: public Ui_VCinemaTimeLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCINEMATIMELINE_H
