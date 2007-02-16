#ifndef VALUESDIALOG_H
#define VALUESDIALOG_H

#include "Qt3Support/Q3GroupBox"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <Qt3Support/Q3MimeSourceFactory>

class Ui_ValuesDialog
{
public:
    Q3GroupBox *Grid;
    QWidget *ULayout;
    QHBoxLayout *hboxLayout;
    QLabel *ULabel;
    QSlider *USlider;
    QLabel *USteps;
    QWidget *VLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *VLabel;
    QSlider *VSlider;
    QLabel *VSteps;
    QWidget *TBoundsLayout;
    QHBoxLayout *hboxLayout2;
    QHBoxLayout *hboxLayout3;
    QLabel *TextLabel12;
    QLineEdit *TMin;
    QHBoxLayout *hboxLayout4;
    QLabel *TextLabel11;
    QLineEdit *TMax;
    QWidget *UBoundsLayout;
    QHBoxLayout *hboxLayout5;
    QHBoxLayout *hboxLayout6;
    QLabel *TextLabel12_2;
    QLineEdit *UMin;
    QHBoxLayout *hboxLayout7;
    QLabel *TextLabel11_2;
    QLineEdit *UMax;
    QWidget *VBoundsLayout;
    QHBoxLayout *hboxLayout8;
    QHBoxLayout *hboxLayout9;
    QLabel *TextLabel12_2_2;
    QLineEdit *VMin;
    QHBoxLayout *hboxLayout10;
    QLabel *TextLabel11_2_2;
    QLineEdit *VMax;
    QWidget *TLayout;
    QHBoxLayout *hboxLayout11;
    QLabel *TLabel;
    QSlider *TSlider;
    QLabel *TSteps;
    QWidget *Layout1;
    QHBoxLayout *hboxLayout12;
    QPushButton *buttonApply;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    Q3GroupBox *Function;
    QWidget *Parameters;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout13;
    QHBoxLayout *hboxLayout14;
    QLabel *ALabel;
    QLineEdit *A;
    QHBoxLayout *hboxLayout15;
    QLabel *BLabel;
    QLineEdit *B;
    QHBoxLayout *hboxLayout16;
    QHBoxLayout *hboxLayout17;
    QLabel *CLabel;
    QLineEdit *C;
    QHBoxLayout *hboxLayout18;
    QLabel *DLabel;
    QLineEdit *D;
    QComboBox *FunctionBox;
    QLabel *TextLabel13;

    void setupUi(QDialog *ValuesDialog)
    {
    ValuesDialog->setObjectName(QString::fromUtf8("ValuesDialog"));
    ValuesDialog->resize(QSize(345, 399).expandedTo(ValuesDialog->minimumSizeHint()));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(1));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ValuesDialog->sizePolicy().hasHeightForWidth());
    ValuesDialog->setSizePolicy(sizePolicy);
    ValuesDialog->setSizeGripEnabled(false);
    Grid = new Q3GroupBox(ValuesDialog);
    Grid->setObjectName(QString::fromUtf8("Grid"));
    Grid->setGeometry(QRect(3, 7, 341, 200));
    Grid->setOrientation(Qt::Vertical);
    ULayout = new QWidget(Grid);
    ULayout->setObjectName(QString::fromUtf8("ULayout"));
    ULayout->setGeometry(QRect(10, 80, 320, 27));
    hboxLayout = new QHBoxLayout(ULayout);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    ULabel = new QLabel(ULayout);
    ULabel->setObjectName(QString::fromUtf8("ULabel"));

    hboxLayout->addWidget(ULabel);

    USlider = new QSlider(ULayout);
    USlider->setObjectName(QString::fromUtf8("USlider"));
    USlider->setMinimum(1);
    USlider->setMaximum(50);
    USlider->setPageStep(5);
    USlider->setValue(5);
    USlider->setOrientation(Qt::Horizontal);
    USlider->setTickInterval(5);

    hboxLayout->addWidget(USlider);

    USteps = new QLabel(ULayout);
    USteps->setObjectName(QString::fromUtf8("USteps"));

    hboxLayout->addWidget(USteps);

    VLayout = new QWidget(Grid);
    VLayout->setObjectName(QString::fromUtf8("VLayout"));
    VLayout->setGeometry(QRect(10, 140, 320, 27));
    hboxLayout1 = new QHBoxLayout(VLayout);
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    VLabel = new QLabel(VLayout);
    VLabel->setObjectName(QString::fromUtf8("VLabel"));

    hboxLayout1->addWidget(VLabel);

    VSlider = new QSlider(VLayout);
    VSlider->setObjectName(QString::fromUtf8("VSlider"));
    VSlider->setMinimum(1);
    VSlider->setMaximum(50);
    VSlider->setPageStep(5);
    VSlider->setValue(5);
    VSlider->setOrientation(Qt::Horizontal);
    VSlider->setTickInterval(5);

    hboxLayout1->addWidget(VSlider);

    VSteps = new QLabel(VLayout);
    VSteps->setObjectName(QString::fromUtf8("VSteps"));

    hboxLayout1->addWidget(VSteps);

    TBoundsLayout = new QWidget(Grid);
    TBoundsLayout->setObjectName(QString::fromUtf8("TBoundsLayout"));
    TBoundsLayout->setGeometry(QRect(70, 50, 240, 26));
    hboxLayout2 = new QHBoxLayout(TBoundsLayout);
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    TextLabel12 = new QLabel(TBoundsLayout);
    TextLabel12->setObjectName(QString::fromUtf8("TextLabel12"));

    hboxLayout3->addWidget(TextLabel12);

    TMin = new QLineEdit(TBoundsLayout);
    TMin->setObjectName(QString::fromUtf8("TMin"));

    hboxLayout3->addWidget(TMin);


    hboxLayout2->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    TextLabel11 = new QLabel(TBoundsLayout);
    TextLabel11->setObjectName(QString::fromUtf8("TextLabel11"));

    hboxLayout4->addWidget(TextLabel11);

    TMax = new QLineEdit(TBoundsLayout);
    TMax->setObjectName(QString::fromUtf8("TMax"));

    hboxLayout4->addWidget(TMax);


    hboxLayout2->addLayout(hboxLayout4);

    UBoundsLayout = new QWidget(Grid);
    UBoundsLayout->setObjectName(QString::fromUtf8("UBoundsLayout"));
    UBoundsLayout->setGeometry(QRect(70, 110, 240, 26));
    hboxLayout5 = new QHBoxLayout(UBoundsLayout);
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    TextLabel12_2 = new QLabel(UBoundsLayout);
    TextLabel12_2->setObjectName(QString::fromUtf8("TextLabel12_2"));

    hboxLayout6->addWidget(TextLabel12_2);

    UMin = new QLineEdit(UBoundsLayout);
    UMin->setObjectName(QString::fromUtf8("UMin"));

    hboxLayout6->addWidget(UMin);


    hboxLayout5->addLayout(hboxLayout6);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setMargin(0);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    TextLabel11_2 = new QLabel(UBoundsLayout);
    TextLabel11_2->setObjectName(QString::fromUtf8("TextLabel11_2"));

    hboxLayout7->addWidget(TextLabel11_2);

    UMax = new QLineEdit(UBoundsLayout);
    UMax->setObjectName(QString::fromUtf8("UMax"));

    hboxLayout7->addWidget(UMax);


    hboxLayout5->addLayout(hboxLayout7);

    VBoundsLayout = new QWidget(Grid);
    VBoundsLayout->setObjectName(QString::fromUtf8("VBoundsLayout"));
    VBoundsLayout->setGeometry(QRect(70, 170, 240, 26));
    hboxLayout8 = new QHBoxLayout(VBoundsLayout);
    hboxLayout8->setSpacing(6);
    hboxLayout8->setMargin(0);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setMargin(0);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    TextLabel12_2_2 = new QLabel(VBoundsLayout);
    TextLabel12_2_2->setObjectName(QString::fromUtf8("TextLabel12_2_2"));

    hboxLayout9->addWidget(TextLabel12_2_2);

    VMin = new QLineEdit(VBoundsLayout);
    VMin->setObjectName(QString::fromUtf8("VMin"));

    hboxLayout9->addWidget(VMin);


    hboxLayout8->addLayout(hboxLayout9);

    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setMargin(0);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    TextLabel11_2_2 = new QLabel(VBoundsLayout);
    TextLabel11_2_2->setObjectName(QString::fromUtf8("TextLabel11_2_2"));

    hboxLayout10->addWidget(TextLabel11_2_2);

    VMax = new QLineEdit(VBoundsLayout);
    VMax->setObjectName(QString::fromUtf8("VMax"));

    hboxLayout10->addWidget(VMax);


    hboxLayout8->addLayout(hboxLayout10);

    TLayout = new QWidget(Grid);
    TLayout->setObjectName(QString::fromUtf8("TLayout"));
    TLayout->setGeometry(QRect(10, 20, 320, 27));
    hboxLayout11 = new QHBoxLayout(TLayout);
    hboxLayout11->setSpacing(6);
    hboxLayout11->setMargin(0);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    TLabel = new QLabel(TLayout);
    TLabel->setObjectName(QString::fromUtf8("TLabel"));

    hboxLayout11->addWidget(TLabel);

    TSlider = new QSlider(TLayout);
    TSlider->setObjectName(QString::fromUtf8("TSlider"));
    TSlider->setMinimum(1);
    TSlider->setMaximum(50);
    TSlider->setPageStep(5);
    TSlider->setValue(5);
    TSlider->setOrientation(Qt::Horizontal);
    TSlider->setTickInterval(5);

    hboxLayout11->addWidget(TSlider);

    TSteps = new QLabel(TLayout);
    TSteps->setObjectName(QString::fromUtf8("TSteps"));

    hboxLayout11->addWidget(TSteps);

    Layout1 = new QWidget(ValuesDialog);
    Layout1->setObjectName(QString::fromUtf8("Layout1"));
    Layout1->setGeometry(QRect(0, 360, 340, 30));
    hboxLayout12 = new QHBoxLayout(Layout1);
    hboxLayout12->setSpacing(6);
    hboxLayout12->setMargin(0);
    hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
    buttonApply = new QPushButton(Layout1);
    buttonApply->setObjectName(QString::fromUtf8("buttonApply"));
    buttonApply->setAutoDefault(true);

    hboxLayout12->addWidget(buttonApply);

    buttonOk = new QPushButton(Layout1);
    buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
    buttonOk->setEnabled(false);
    buttonOk->setAutoDefault(true);
    buttonOk->setDefault(true);

    hboxLayout12->addWidget(buttonOk);

    buttonCancel = new QPushButton(Layout1);
    buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
    buttonCancel->setEnabled(false);
    buttonCancel->setAutoDefault(true);

    hboxLayout12->addWidget(buttonCancel);

    Function = new Q3GroupBox(ValuesDialog);
    Function->setObjectName(QString::fromUtf8("Function"));
    Function->setGeometry(QRect(3, 210, 340, 150));
    Function->setOrientation(Qt::Vertical);
    Parameters = new QWidget(Function);
    Parameters->setObjectName(QString::fromUtf8("Parameters"));
    Parameters->setGeometry(QRect(10, 60, 320, 70));
    vboxLayout = new QVBoxLayout(Parameters);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout13 = new QHBoxLayout();
    hboxLayout13->setSpacing(6);
    hboxLayout13->setMargin(0);
    hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
    hboxLayout14 = new QHBoxLayout();
    hboxLayout14->setSpacing(6);
    hboxLayout14->setMargin(0);
    hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
    ALabel = new QLabel(Parameters);
    ALabel->setObjectName(QString::fromUtf8("ALabel"));

    hboxLayout14->addWidget(ALabel);

    A = new QLineEdit(Parameters);
    A->setObjectName(QString::fromUtf8("A"));

    hboxLayout14->addWidget(A);


    hboxLayout13->addLayout(hboxLayout14);

    hboxLayout15 = new QHBoxLayout();
    hboxLayout15->setSpacing(6);
    hboxLayout15->setMargin(0);
    hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
    BLabel = new QLabel(Parameters);
    BLabel->setObjectName(QString::fromUtf8("BLabel"));

    hboxLayout15->addWidget(BLabel);

    B = new QLineEdit(Parameters);
    B->setObjectName(QString::fromUtf8("B"));

    hboxLayout15->addWidget(B);


    hboxLayout13->addLayout(hboxLayout15);


    vboxLayout->addLayout(hboxLayout13);

    hboxLayout16 = new QHBoxLayout();
    hboxLayout16->setSpacing(6);
    hboxLayout16->setMargin(0);
    hboxLayout16->setObjectName(QString::fromUtf8("hboxLayout16"));
    hboxLayout17 = new QHBoxLayout();
    hboxLayout17->setSpacing(6);
    hboxLayout17->setMargin(0);
    hboxLayout17->setObjectName(QString::fromUtf8("hboxLayout17"));
    CLabel = new QLabel(Parameters);
    CLabel->setObjectName(QString::fromUtf8("CLabel"));

    hboxLayout17->addWidget(CLabel);

    C = new QLineEdit(Parameters);
    C->setObjectName(QString::fromUtf8("C"));

    hboxLayout17->addWidget(C);


    hboxLayout16->addLayout(hboxLayout17);

    hboxLayout18 = new QHBoxLayout();
    hboxLayout18->setSpacing(6);
    hboxLayout18->setMargin(0);
    hboxLayout18->setObjectName(QString::fromUtf8("hboxLayout18"));
    DLabel = new QLabel(Parameters);
    DLabel->setObjectName(QString::fromUtf8("DLabel"));

    hboxLayout18->addWidget(DLabel);

    D = new QLineEdit(Parameters);
    D->setObjectName(QString::fromUtf8("D"));

    hboxLayout18->addWidget(D);


    hboxLayout16->addLayout(hboxLayout18);


    vboxLayout->addLayout(hboxLayout16);

    FunctionBox = new QComboBox(Function);
    FunctionBox->setObjectName(QString::fromUtf8("FunctionBox"));
    FunctionBox->setEnabled(false);
    FunctionBox->setGeometry(QRect(76, 20, 250, 22));
    TextLabel13 = new QLabel(Function);
    TextLabel13->setObjectName(QString::fromUtf8("TextLabel13"));
    TextLabel13->setEnabled(false);
    TextLabel13->setGeometry(QRect(11, 21, 60, 22));
    QWidget::setTabOrder(TSlider, TMin);
    QWidget::setTabOrder(TMin, TMax);
    QWidget::setTabOrder(TMax, USlider);
    QWidget::setTabOrder(USlider, UMin);
    QWidget::setTabOrder(UMin, UMax);
    QWidget::setTabOrder(UMax, VSlider);
    QWidget::setTabOrder(VSlider, VMin);
    QWidget::setTabOrder(VMin, VMax);
    QWidget::setTabOrder(VMax, FunctionBox);
    QWidget::setTabOrder(FunctionBox, A);
    QWidget::setTabOrder(A, B);
    QWidget::setTabOrder(B, C);
    QWidget::setTabOrder(C, D);
    QWidget::setTabOrder(D, buttonApply);
    QWidget::setTabOrder(buttonApply, buttonOk);
    QWidget::setTabOrder(buttonOk, buttonCancel);
    retranslateUi(ValuesDialog);
    QObject::connect(TSlider, SIGNAL(valueChanged(int)), TSteps, SLOT(setNum(int)));
    QObject::connect(USlider, SIGNAL(valueChanged(int)), USteps, SLOT(setNum(int)));
    QObject::connect(VSlider, SIGNAL(valueChanged(int)), VSteps, SLOT(setNum(int)));
    QObject::connect(buttonApply, SIGNAL(clicked()), ValuesDialog, SLOT(accept()));
    QObject::connect(buttonOk, SIGNAL(clicked()), ValuesDialog, SLOT(accept()));

    QMetaObject::connectSlotsByName(ValuesDialog);
    } // setupUi

    void retranslateUi(QDialog *ValuesDialog)
    {
    ValuesDialog->setWindowTitle(QApplication::translate("ValuesDialog", "Enter Values for the Function", 0, QApplication::UnicodeUTF8));
    ValuesDialog->setWhatsThis(QApplication::translate("ValuesDialog", "In this dialog window the user can enter up to four parameters to the displayed four-dimensional function or object.\n"
"She con also change the resolution of the grid.", 0, QApplication::UnicodeUTF8));
    Grid->setTitle(QApplication::translate("ValuesDialog", "Grid Size and Bounds", 0, QApplication::UnicodeUTF8));
    ULabel->setText(QApplication::translate("ValuesDialog", "Steps in u", 0, QApplication::UnicodeUTF8));
    USteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    VLabel->setText(QApplication::translate("ValuesDialog", "Steps in v", 0, QApplication::UnicodeUTF8));
    VSteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    TextLabel12->setText(QApplication::translate("ValuesDialog", "tmin", 0, QApplication::UnicodeUTF8));
    TMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    TMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    TextLabel11->setText(QApplication::translate("ValuesDialog", "tmax", 0, QApplication::UnicodeUTF8));
    TMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    TMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    TextLabel12_2->setText(QApplication::translate("ValuesDialog", "umin", 0, QApplication::UnicodeUTF8));
    UMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    UMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    TextLabel11_2->setText(QApplication::translate("ValuesDialog", "umax", 0, QApplication::UnicodeUTF8));
    UMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    UMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    TextLabel12_2_2->setText(QApplication::translate("ValuesDialog", "vmin", 0, QApplication::UnicodeUTF8));
    VMin->setToolTip(QApplication::translate("ValuesDialog", "enter '-pi' if you mean -3.1415...", 0, QApplication::UnicodeUTF8));
    VMin->setText(QApplication::translate("ValuesDialog", "-1", 0, QApplication::UnicodeUTF8));
    TextLabel11_2_2->setText(QApplication::translate("ValuesDialog", "vmax", 0, QApplication::UnicodeUTF8));
    VMax->setToolTip(QApplication::translate("ValuesDialog", "or 'pi' if you want 3.1415...", 0, QApplication::UnicodeUTF8));
    VMax->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    TLabel->setText(QApplication::translate("ValuesDialog", "Steps in t", 0, QApplication::UnicodeUTF8));
    TSteps->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    buttonApply->setToolTip(QApplication::translate("ValuesDialog", "Accept changes and redraw", 0, QApplication::UnicodeUTF8));
    buttonApply->setText(QApplication::translate("ValuesDialog", "&Apply", 0, QApplication::UnicodeUTF8));
    buttonOk->setToolTip(QApplication::translate("ValuesDialog", "Apply changes, redraw and close this window", 0, QApplication::UnicodeUTF8));
    buttonOk->setText(QApplication::translate("ValuesDialog", "&OK", 0, QApplication::UnicodeUTF8));
    buttonCancel->setToolTip(QApplication::translate("ValuesDialog", "Discard changes", 0, QApplication::UnicodeUTF8));
    buttonCancel->setText(QApplication::translate("ValuesDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    Function->setTitle(QApplication::translate("ValuesDialog", "Function and Parameters", 0, QApplication::UnicodeUTF8));
    ALabel->setText(QApplication::translate("ValuesDialog", "Parameter A", 0, QApplication::UnicodeUTF8));
    A->setText(QApplication::translate("ValuesDialog", "1", 0, QApplication::UnicodeUTF8));
    BLabel->setText(QApplication::translate("ValuesDialog", "Parameter B", 0, QApplication::UnicodeUTF8));
    B->setText(QApplication::translate("ValuesDialog", "0.5", 0, QApplication::UnicodeUTF8));
    CLabel->setText(QApplication::translate("ValuesDialog", "Parameter C", 0, QApplication::UnicodeUTF8));
    C->setText(QApplication::translate("ValuesDialog", "0.25", 0, QApplication::UnicodeUTF8));
    DLabel->setText(QApplication::translate("ValuesDialog", "Parameter D", 0, QApplication::UnicodeUTF8));
    D->setText(QApplication::translate("ValuesDialog", "0", 0, QApplication::UnicodeUTF8));
    TextLabel13->setText(QApplication::translate("ValuesDialog", "Function", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ValuesDialog);
    } // retranslateUi

};

namespace Ui {
    class ValuesDialog: public Ui_ValuesDialog {};
} // namespace Ui

#endif // VALUESDIALOG_H
