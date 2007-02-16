#ifndef SURFACEDIALOG_H
#define SURFACEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <Qt3Support/Q3MimeSourceFactory>

class Ui_SurfaceDialog
{
public:
    QLabel *IntroLabel;
    QWidget *FunctionsLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *XLabel;
    QLineEdit *XEdit;
    QHBoxLayout *hboxLayout1;
    QLabel *YLabel;
    QLineEdit *YEdit;
    QHBoxLayout *hboxLayout2;
    QLabel *ZLabel;
    QLineEdit *ZEdit;
    QHBoxLayout *hboxLayout3;
    QLabel *WLabel;
    QLineEdit *WEdit;
    QWidget *Layout29;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout4;
    QLabel *NameLabel;
    QLineEdit *NameEdit;
    QHBoxLayout *hboxLayout5;
    QLabel *DescLabel;
    QLineEdit *LineEdit12;
    QSpacerItem *spacerItem;
    QWidget *BtnsLayout;
    QHBoxLayout *hboxLayout6;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem1;
    QPushButton *LoadButton;

    void setupUi(QDialog *SurfaceDialog)
    {
    SurfaceDialog->setObjectName(QString::fromUtf8("SurfaceDialog"));
    SurfaceDialog->resize(QSize(361, 292).expandedTo(SurfaceDialog->minimumSizeHint()));
    IntroLabel = new QLabel(SurfaceDialog);
    IntroLabel->setObjectName(QString::fromUtf8("IntroLabel"));
    IntroLabel->setGeometry(QRect(0, 0, 368, 40));
    FunctionsLayout = new QWidget(SurfaceDialog);
    FunctionsLayout->setObjectName(QString::fromUtf8("FunctionsLayout"));
    FunctionsLayout->setGeometry(QRect(0, 40, 360, 132));
    vboxLayout = new QVBoxLayout(FunctionsLayout);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    XLabel = new QLabel(FunctionsLayout);
    XLabel->setObjectName(QString::fromUtf8("XLabel"));

    hboxLayout->addWidget(XLabel);

    XEdit = new QLineEdit(FunctionsLayout);
    XEdit->setObjectName(QString::fromUtf8("XEdit"));

    hboxLayout->addWidget(XEdit);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    YLabel = new QLabel(FunctionsLayout);
    YLabel->setObjectName(QString::fromUtf8("YLabel"));

    hboxLayout1->addWidget(YLabel);

    YEdit = new QLineEdit(FunctionsLayout);
    YEdit->setObjectName(QString::fromUtf8("YEdit"));

    hboxLayout1->addWidget(YEdit);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    ZLabel = new QLabel(FunctionsLayout);
    ZLabel->setObjectName(QString::fromUtf8("ZLabel"));

    hboxLayout2->addWidget(ZLabel);

    ZEdit = new QLineEdit(FunctionsLayout);
    ZEdit->setObjectName(QString::fromUtf8("ZEdit"));

    hboxLayout2->addWidget(ZEdit);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    WLabel = new QLabel(FunctionsLayout);
    WLabel->setObjectName(QString::fromUtf8("WLabel"));

    hboxLayout3->addWidget(WLabel);

    WEdit = new QLineEdit(FunctionsLayout);
    WEdit->setObjectName(QString::fromUtf8("WEdit"));

    hboxLayout3->addWidget(WEdit);


    vboxLayout->addLayout(hboxLayout3);

    Layout29 = new QWidget(SurfaceDialog);
    Layout29->setObjectName(QString::fromUtf8("Layout29"));
    Layout29->setGeometry(QRect(0, 180, 360, 71));
    vboxLayout1 = new QVBoxLayout(Layout29);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    NameLabel = new QLabel(Layout29);
    NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

    hboxLayout4->addWidget(NameLabel);

    NameEdit = new QLineEdit(Layout29);
    NameEdit->setObjectName(QString::fromUtf8("NameEdit"));

    hboxLayout4->addWidget(NameEdit);


    vboxLayout1->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    DescLabel = new QLabel(Layout29);
    DescLabel->setObjectName(QString::fromUtf8("DescLabel"));

    hboxLayout5->addWidget(DescLabel);

    LineEdit12 = new QLineEdit(Layout29);
    LineEdit12->setObjectName(QString::fromUtf8("LineEdit12"));
    LineEdit12->setEnabled(false);

    hboxLayout5->addWidget(LineEdit12);


    vboxLayout1->addLayout(hboxLayout5);

    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem);

    BtnsLayout = new QWidget(SurfaceDialog);
    BtnsLayout->setObjectName(QString::fromUtf8("BtnsLayout"));
    BtnsLayout->setGeometry(QRect(0, 260, 360, 30));
    hboxLayout6 = new QHBoxLayout(BtnsLayout);
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    OKButton = new QPushButton(BtnsLayout);
    OKButton->setObjectName(QString::fromUtf8("OKButton"));

    hboxLayout6->addWidget(OKButton);

    CancelButton = new QPushButton(BtnsLayout);
    CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

    hboxLayout6->addWidget(CancelButton);

    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem1);

    LoadButton = new QPushButton(BtnsLayout);
    LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
    LoadButton->setEnabled(true);

    hboxLayout6->addWidget(LoadButton);

    retranslateUi(SurfaceDialog);
    QObject::connect(CancelButton, SIGNAL(clicked()), SurfaceDialog, SLOT(close()));

    QMetaObject::connectSlotsByName(SurfaceDialog);
    } // setupUi

    void retranslateUi(QDialog *SurfaceDialog)
    {
    SurfaceDialog->setWindowTitle(QApplication::translate("SurfaceDialog", "Enter a definition for the surface", 0, QApplication::UnicodeUTF8));
    IntroLabel->setText(QApplication::translate("SurfaceDialog", "A surface in four dimensions is defined with four functions of two\n"
"variables. Please enter these functions below, in C++ syntax.", 0, QApplication::UnicodeUTF8));
    XLabel->setText(QApplication::translate("SurfaceDialog", "X (u, v) =", 0, QApplication::UnicodeUTF8));
    YLabel->setText(QApplication::translate("SurfaceDialog", "Y (u, v) =", 0, QApplication::UnicodeUTF8));
    ZLabel->setText(QApplication::translate("SurfaceDialog", "Z (u, v) =", 0, QApplication::UnicodeUTF8));
    WLabel->setText(QApplication::translate("SurfaceDialog", "W (u, v) =", 0, QApplication::UnicodeUTF8));
    NameLabel->setText(QApplication::translate("SurfaceDialog", "Name of the function", 0, QApplication::UnicodeUTF8));
    DescLabel->setText(QApplication::translate("SurfaceDialog", "Additional description (optional)", 0, QApplication::UnicodeUTF8));
    OKButton->setText(QApplication::translate("SurfaceDialog", "&OK", 0, QApplication::UnicodeUTF8));
    CancelButton->setText(QApplication::translate("SurfaceDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    LoadButton->setText(QApplication::translate("SurfaceDialog", "&Load Function", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SurfaceDialog);
    } // retranslateUi

};

namespace Ui {
    class SurfaceDialog: public Ui_SurfaceDialog {};
} // namespace Ui

#endif // SURFACEDIALOG_H
