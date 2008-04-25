/********************************************************************************
** Form generated from reading ui file 'ValuesDialog.ui'
**
** Created: Fri Apr 25 15:22:18 2008
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VALUESDIALOG_H
#define UI_VALUESDIALOG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>

/// Base class for ValuesDialog, originally created by uic (thus the ugliness)
class Ui_ValuesDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QHBoxLayout *hboxLayout3;
    QHBoxLayout *hboxLayout4;
    QHBoxLayout *hboxLayout5;
    QHBoxLayout *hboxLayout6;
    QHBoxLayout *hboxLayout7;
    QHBoxLayout *hboxLayout8;
    QHBoxLayout *hboxLayout9;
    QHBoxLayout *hboxLayout10;
    QHBoxLayout *hboxLayout11;
    QHBoxLayout *hboxLayout13;
    QHBoxLayout *hboxLayout14;
    QHBoxLayout *hboxLayout15;
    QHBoxLayout *hboxLayout16;
    QHBoxLayout *hboxLayout17;
    QHBoxLayout *hboxLayout18;
    QHBoxLayout *hboxLayout19;
    QLabel *gridLabel;
    QLabel *TLabel;
    QSlider *TSlider;
    QLabel *TSteps;
    QLabel *TMinLabel;
    QLineEdit *TMin;
    QLabel *TMaxLabel;
    QLineEdit *TMax;
    QLabel *ULabel;
    QSlider *USlider;
    QLabel *USteps;
    QLabel *UMinLabel;
    QLineEdit *UMin;
    QLabel *UMaxLabel;
    QLineEdit *UMax;
    QLabel *VLabel;
    QSlider *VSlider;
    QLabel *VSteps;
    QLabel *VMinLabel;
    QLineEdit *VMin;
    QLabel *VMaxLabel;
    QLineEdit *VMax;
    QLabel *functionLabel;
    QLabel *ParameterLabel[4];
    QLineEdit *Parameter[4];

    QPushButton *buttonApply;

    void setupUi(QDialog *ValuesDialog)
    {
    if (ValuesDialog->objectName().isEmpty())
        ValuesDialog->setObjectName(QString::fromUtf8("ValuesDialog"));
    ValuesDialog->resize(343, 410);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ValuesDialog->sizePolicy().hasHeightForWidth());
    ValuesDialog->setSizePolicy(sizePolicy);
    ValuesDialog->setSizeGripEnabled(false);
    gridLayout = new QGridLayout(ValuesDialog);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    gridLabel = new QLabel(ValuesDialog);
    gridLabel->setObjectName(QString::fromUtf8("gridLabel"));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    gridLabel->setFont(font);
    gridLabel->setAlignment(Qt::AlignCenter);

    vboxLayout->addWidget(gridLabel);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    TLabel = new QLabel(ValuesDialog);
    TLabel->setObjectName(QString::fromUtf8("TLabel"));

    hboxLayout->addWidget(TLabel);

    TSlider = new QSlider(ValuesDialog);
    TSlider->setObjectName(QString::fromUtf8("TSlider"));
    TSlider->setMinimum(1);
    TSlider->setMaximum(50);
    TSlider->setPageStep(5);
    TSlider->setValue(5);
    TSlider->setOrientation(Qt::Horizontal);
    TSlider->setTickInterval(5);

    hboxLayout->addWidget(TSlider);

    TSteps = new QLabel(ValuesDialog);
    TSteps->setObjectName(QString::fromUtf8("TSteps"));

    hboxLayout->addWidget(TSteps);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    hboxLayout2->setContentsMargins(0, 0, 0, 0);
    TMinLabel = new QLabel(ValuesDialog);
    TMinLabel->setObjectName(QString::fromUtf8("TMinLabel"));

    hboxLayout2->addWidget(TMinLabel);

    TMin = new QLineEdit(ValuesDialog);
    TMin->setObjectName(QString::fromUtf8("TMin"));

    hboxLayout2->addWidget(TMin);


    hboxLayout1->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout3->setContentsMargins(0, 0, 0, 0);
    TMaxLabel = new QLabel(ValuesDialog);
    TMaxLabel->setObjectName(QString::fromUtf8("TMaxLabel"));

    hboxLayout3->addWidget(TMaxLabel);

    TMax = new QLineEdit(ValuesDialog);
    TMax->setObjectName(QString::fromUtf8("TMax"));

    hboxLayout3->addWidget(TMax);


    hboxLayout1->addLayout(hboxLayout3);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    hboxLayout4->setContentsMargins(0, 0, 0, 0);
    ULabel = new QLabel(ValuesDialog);
    ULabel->setObjectName(QString::fromUtf8("ULabel"));

    hboxLayout4->addWidget(ULabel);

    USlider = new QSlider(ValuesDialog);
    USlider->setObjectName(QString::fromUtf8("USlider"));
    USlider->setMinimum(1);
    USlider->setMaximum(50);
    USlider->setPageStep(5);
    USlider->setValue(5);
    USlider->setOrientation(Qt::Horizontal);
    USlider->setTickInterval(5);

    hboxLayout4->addWidget(USlider);

    USteps = new QLabel(ValuesDialog);
    USteps->setObjectName(QString::fromUtf8("USteps"));

    hboxLayout4->addWidget(USteps);


    vboxLayout->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    hboxLayout5->setContentsMargins(0, 0, 0, 0);
    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    hboxLayout6->setContentsMargins(0, 0, 0, 0);
    UMinLabel = new QLabel(ValuesDialog);
    UMinLabel->setObjectName(QString::fromUtf8("UMinLabel"));

    hboxLayout6->addWidget(UMinLabel);

    UMin = new QLineEdit(ValuesDialog);
    UMin->setObjectName(QString::fromUtf8("UMin"));

    hboxLayout6->addWidget(UMin);


    hboxLayout5->addLayout(hboxLayout6);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    hboxLayout7->setContentsMargins(0, 0, 0, 0);
    UMaxLabel = new QLabel(ValuesDialog);
    UMaxLabel->setObjectName(QString::fromUtf8("UMaxLabel"));

    hboxLayout7->addWidget(UMaxLabel);

    UMax = new QLineEdit(ValuesDialog);
    UMax->setObjectName(QString::fromUtf8("UMax"));

    hboxLayout7->addWidget(UMax);


    hboxLayout5->addLayout(hboxLayout7);


    vboxLayout->addLayout(hboxLayout5);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    hboxLayout8->setContentsMargins(0, 0, 0, 0);
    VLabel = new QLabel(ValuesDialog);
    VLabel->setObjectName(QString::fromUtf8("VLabel"));

    hboxLayout8->addWidget(VLabel);

    VSlider = new QSlider(ValuesDialog);
    VSlider->setObjectName(QString::fromUtf8("VSlider"));
    VSlider->setMinimum(1);
    VSlider->setMaximum(50);
    VSlider->setPageStep(5);
    VSlider->setValue(5);
    VSlider->setOrientation(Qt::Horizontal);
    VSlider->setTickInterval(5);

    hboxLayout8->addWidget(VSlider);

    VSteps = new QLabel(ValuesDialog);
    VSteps->setObjectName(QString::fromUtf8("VSteps"));

    hboxLayout8->addWidget(VSteps);


    vboxLayout->addLayout(hboxLayout8);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    hboxLayout9->setContentsMargins(0, 0, 0, 0);
    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    hboxLayout10->setContentsMargins(0, 0, 0, 0);
    VMinLabel = new QLabel(ValuesDialog);
    VMinLabel->setObjectName(QString::fromUtf8("VMinLabel"));

    hboxLayout10->addWidget(VMinLabel);

    VMin = new QLineEdit(ValuesDialog);
    VMin->setObjectName(QString::fromUtf8("VMin"));

    hboxLayout10->addWidget(VMin);


    hboxLayout9->addLayout(hboxLayout10);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    hboxLayout11->setContentsMargins(0, 0, 0, 0);
    VMaxLabel = new QLabel(ValuesDialog);
    VMaxLabel->setObjectName(QString::fromUtf8("VMaxLabel"));

    hboxLayout11->addWidget(VMaxLabel);

    VMax = new QLineEdit(ValuesDialog);
    VMax->setObjectName(QString::fromUtf8("VMax"));

    hboxLayout11->addWidget(VMax);


    hboxLayout9->addLayout(hboxLayout11);


    vboxLayout->addLayout(hboxLayout9);


    gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);

    functionLabel = new QLabel(ValuesDialog);
    functionLabel->setObjectName(QString::fromUtf8("functionLabel"));
    functionLabel->setFont(font);
    functionLabel->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(functionLabel, 2, 0, 1, 1);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(0, 0, 0, 0);
    hboxLayout13 = new QHBoxLayout();
    hboxLayout13->setSpacing(6);
    hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
    hboxLayout13->setContentsMargins(0, 0, 0, 0);
    hboxLayout14 = new QHBoxLayout();
    hboxLayout14->setSpacing(6);
    hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
    hboxLayout14->setContentsMargins(0, 0, 0, 0);
    ParameterLabel[0] = new QLabel(ValuesDialog);
    ParameterLabel[0]->setObjectName(QString::fromUtf8("ParameterLabel[0]"));

    hboxLayout14->addWidget(ParameterLabel[0]);

    Parameter[0] = new QLineEdit(ValuesDialog);
    Parameter[0]->setObjectName(QString::fromUtf8("Parameter[0]"));

    hboxLayout14->addWidget(Parameter[0]);


    hboxLayout13->addLayout(hboxLayout14);

    hboxLayout15 = new QHBoxLayout();
    hboxLayout15->setSpacing(6);
    hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
    hboxLayout15->setContentsMargins(0, 0, 0, 0);
    ParameterLabel[1] = new QLabel(ValuesDialog);
    ParameterLabel[1]->setObjectName(QString::fromUtf8("ParameterLabel[1]"));

    hboxLayout15->addWidget(ParameterLabel[1]);

    Parameter[1] = new QLineEdit(ValuesDialog);
    Parameter[1]->setObjectName(QString::fromUtf8("Parameter[1]"));

    hboxLayout15->addWidget(Parameter[1]);


    hboxLayout13->addLayout(hboxLayout15);


    vboxLayout1->addLayout(hboxLayout13);

    hboxLayout16 = new QHBoxLayout();
    hboxLayout16->setSpacing(6);
    hboxLayout16->setObjectName(QString::fromUtf8("hboxLayout16"));
    hboxLayout16->setContentsMargins(0, 0, 0, 0);
    hboxLayout17 = new QHBoxLayout();
    hboxLayout17->setSpacing(6);
    hboxLayout17->setObjectName(QString::fromUtf8("hboxLayout17"));
    hboxLayout17->setContentsMargins(0, 0, 0, 0);
    ParameterLabel[2] = new QLabel(ValuesDialog);
    ParameterLabel[2]->setObjectName(QString::fromUtf8("ParameterLabel[2]"));

    hboxLayout17->addWidget(ParameterLabel[2]);

    Parameter[2] = new QLineEdit(ValuesDialog);
    Parameter[2]->setObjectName(QString::fromUtf8("Parameter[2]"));

    hboxLayout17->addWidget(Parameter[2]);


    hboxLayout16->addLayout(hboxLayout17);

    hboxLayout18 = new QHBoxLayout();
    hboxLayout18->setSpacing(6);
    hboxLayout18->setObjectName(QString::fromUtf8("hboxLayout18"));
    hboxLayout18->setContentsMargins(0, 0, 0, 0);
    ParameterLabel[3] = new QLabel(ValuesDialog);
    ParameterLabel[3]->setObjectName(QString::fromUtf8("ParameterLabel[3]"));

    hboxLayout18->addWidget(ParameterLabel[3]);

    Parameter[3] = new QLineEdit(ValuesDialog);
    Parameter[3]->setObjectName(QString::fromUtf8("Parameter[3]"));

    hboxLayout18->addWidget(Parameter[3]);


    hboxLayout16->addLayout(hboxLayout18);


    vboxLayout1->addLayout(hboxLayout16);


    gridLayout->addLayout(vboxLayout1, 4, 0, 1, 1);

    hboxLayout19 = new QHBoxLayout();
    hboxLayout19->setSpacing(6);
    hboxLayout19->setObjectName(QString::fromUtf8("hboxLayout19"));
    hboxLayout19->setContentsMargins(0, 0, 0, 0);
    buttonApply = new QPushButton(ValuesDialog);
    buttonApply->setObjectName(QString::fromUtf8("buttonApply"));
    buttonApply->setAutoDefault(true);

    hboxLayout19->addWidget(buttonApply);
    gridLayout->addLayout(hboxLayout19, 5, 0, 1, 1);

    QWidget::setTabOrder(TSlider, TMin);
    QWidget::setTabOrder(TMin, TMax);
    QWidget::setTabOrder(TMax, USlider);
    QWidget::setTabOrder(USlider, UMin);
    QWidget::setTabOrder(UMin, UMax);
    QWidget::setTabOrder(UMax, VSlider);
    QWidget::setTabOrder(VSlider, VMin);
    QWidget::setTabOrder(VMin, VMax);
    QWidget::setTabOrder(VMax, Parameter[0]);
    QWidget::setTabOrder(Parameter[0], Parameter[1]);
    QWidget::setTabOrder(Parameter[1], Parameter[2]);
    QWidget::setTabOrder(Parameter[2], Parameter[3]);
    QWidget::setTabOrder(Parameter[3], buttonApply);

    retranslateUi(ValuesDialog);
    QObject::connect(TSlider, SIGNAL(valueChanged(int)), TSteps, SLOT(setNum(int)));
    QObject::connect(USlider, SIGNAL(valueChanged(int)), USteps, SLOT(setNum(int)));
    QObject::connect(VSlider, SIGNAL(valueChanged(int)), VSteps, SLOT(setNum(int)));
    QObject::connect(buttonApply, SIGNAL(clicked()), ValuesDialog, SLOT(accept()));
    QObject::connect(TSlider, SIGNAL(valueChanged(int)), USlider, SLOT(setValue(int)));
    QObject::connect(TSlider, SIGNAL(valueChanged(int)), VSlider, SLOT(setValue(int)));
    QObject::connect(USlider, SIGNAL(valueChanged(int)), VSlider, SLOT(setValue(int)));

    QMetaObject::connectSlotsByName(ValuesDialog);
    } // setupUi

    void retranslateUi(QDialog *ValuesDialog)
    {
    ValuesDialog->setWindowTitle(QApplication::translate("ValuesDialog", "Enter Values for the Function", 0, QApplication::UnicodeUTF8));
    ValuesDialog->setWhatsThis(QApplication::translate("ValuesDialog", "In this dialog window the user can enter up to four parameters to the displayed four-dimensional function or object.\n"
"She con also change the resolution of the grid.", 0, QApplication::UnicodeUTF8));
    gridLabel->setText(QApplication::translate("ValuesDialog", "Grid size and bounds", 0, QApplication::UnicodeUTF8));
    TLabel->setText(QApplication::translate("ValuesDialog", "Steps in t", 0, QApplication::UnicodeUTF8));
    TSteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    TMinLabel->setText(QApplication::translate("ValuesDialog", "tmin", 0, QApplication::UnicodeUTF8));
    TMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    TMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    TMaxLabel->setText(QApplication::translate("ValuesDialog", "tmax", 0, QApplication::UnicodeUTF8));
    TMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    TMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    ULabel->setText(QApplication::translate("ValuesDialog", "Steps in u", 0, QApplication::UnicodeUTF8));
    USteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    UMinLabel->setText(QApplication::translate("ValuesDialog", "umin", 0, QApplication::UnicodeUTF8));
    UMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    UMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    UMaxLabel->setText(QApplication::translate("ValuesDialog", "umax", 0, QApplication::UnicodeUTF8));
    UMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    UMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    VLabel->setText(QApplication::translate("ValuesDialog", "Steps in v", 0, QApplication::UnicodeUTF8));
    VSteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    VMinLabel->setText(QApplication::translate("ValuesDialog", "vmin", 0, QApplication::UnicodeUTF8));
    VMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    VMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    VMaxLabel->setText(QApplication::translate("ValuesDialog", "vmax", 0, QApplication::UnicodeUTF8));
    VMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    VMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    functionLabel->setText(QApplication::translate("ValuesDialog", "Function Parameters", 0, QApplication::UnicodeUTF8));
    ParameterLabel[0]->setText(QApplication::translate("ValuesDialog", "Parameter A", 0, QApplication::UnicodeUTF8));
    Parameter[0]->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    ParameterLabel[1]->setText(QApplication::translate("ValuesDialog", "Parameter B", 0, QApplication::UnicodeUTF8));
    Parameter[1]->setText(QApplication::translate("ValuesDialog", "0.5", 0, QApplication::UnicodeUTF8));
    ParameterLabel[2]->setText(QApplication::translate("ValuesDialog", "Parameter C", 0, QApplication::UnicodeUTF8));
    Parameter[2]->setText(QApplication::translate("ValuesDialog", "0.25", 0, QApplication::UnicodeUTF8));
    ParameterLabel[3]->setText(QApplication::translate("ValuesDialog", "Parameter D", 0, QApplication::UnicodeUTF8));
    Parameter[3]->setText(QApplication::translate("ValuesDialog", "0", 0, QApplication::UnicodeUTF8));
    buttonApply->setToolTip(QApplication::translate("ValuesDialog", "Accept changes and redraw", 0, QApplication::UnicodeUTF8));
    buttonApply->setText(QApplication::translate("ValuesDialog", "&Apply", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ValuesDialog);
    } // retranslateUi

};

namespace Ui {
    class ValuesDialog: public Ui_ValuesDialog {};
} // namespace Ui

#endif // UI_VALUESDIALOG_H
