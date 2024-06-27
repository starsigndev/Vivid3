/********************************************************************************
** Form generated from reading UI file 'VTrackTimeLine.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTRACKTIMELINE_H
#define UI_VTRACKTIMELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTrackTimeLineClass
{
public:

    void setupUi(QWidget *VTrackTimeLineClass)
    {
        if (VTrackTimeLineClass->objectName().isEmpty())
            VTrackTimeLineClass->setObjectName("VTrackTimeLineClass");
        VTrackTimeLineClass->resize(600, 400);

        retranslateUi(VTrackTimeLineClass);

        QMetaObject::connectSlotsByName(VTrackTimeLineClass);
    } // setupUi

    void retranslateUi(QWidget *VTrackTimeLineClass)
    {
        VTrackTimeLineClass->setWindowTitle(QCoreApplication::translate("VTrackTimeLineClass", "VTrackTimeLine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTrackTimeLineClass: public Ui_VTrackTimeLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTRACKTIMELINE_H
