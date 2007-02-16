#ifndef POLARDIALOG_H
#define POLARDIALOG_H

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

class Ui_PolarDialog
{
public:
    QWidget *FLayout;
    QHBoxLayout *hboxLayout;
    QLabel *FLabel;
    QLineEdit *FEdit;
    QWidget *Layout27;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *NameLabel;
    QLineEdit *NameEdit;
    QHBoxLayout *hboxLayout2;
    QLabel *DescLabel;
    QLineEdit *LineEdit12;
    QSpacerItem *spacerItem;
    QWidget *BtnsLayout;
    QHBoxLayout *hboxLayout3;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem1;
    QPushButton *LoadButton;
    QLabel *IntroLabel;

    void setupUi(QDialog *PolarDialog)
    {
    PolarDialog->setObjectName(QString::fromUtf8("PolarDialog"));
    PolarDialog->resize(QSize(362, 182).expandedTo(PolarDialog->minimumSizeHint()));
    FLayout = new QWidget(PolarDialog);
    FLayout->setObjectName(QString::fromUtf8("FLayout"));
    FLayout->setGeometry(QRect(0, 40, 360, 28));
    hboxLayout = new QHBoxLayout(FLayout);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    FLabel = new QLabel(FLayout);
    FLabel->setObjectName(QString::fromUtf8("FLabel"));

    hboxLayout->addWidget(FLabel);

    FEdit = new QLineEdit(FLayout);
    FEdit->setObjectName(QString::fromUtf8("FEdit"));

    hboxLayout->addWidget(FEdit);

    Layout27 = new QWidget(PolarDialog);
    Layout27->setObjectName(QString::fromUtf8("Layout27"));
    Layout27->setGeometry(QRect(0, 71, 360, 71));
    vboxLayout = new QVBoxLayout(Layout27);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    NameLabel = new QLabel(Layout27);
    NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

    hboxLayout1->addWidget(NameLabel);

    NameEdit = new QLineEdit(Layout27);
    NameEdit->setObjectName(QString::fromUtf8("NameEdit"));

    hboxLayout1->addWidget(NameEdit);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    DescLabel = new QLabel(Layout27);
    DescLabel->setObjectName(QString::fromUtf8("DescLabel"));

    hboxLayout2->addWidget(DescLabel);

    LineEdit12 = new QLineEdit(Layout27);
    LineEdit12->setObjectName(QString::fromUtf8("LineEdit12"));
    LineEdit12->setEnabled(false);

    hboxLayout2->addWidget(LineEdit12);


    vboxLayout->addLayout(hboxLayout2);

    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem);

    BtnsLayout = new QWidget(PolarDialog);
    BtnsLayout->setObjectName(QString::fromUtf8("BtnsLayout"));
    BtnsLayout->setGeometry(QRect(-10, 150, 360, 30));
    hboxLayout3 = new QHBoxLayout(BtnsLayout);
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    OKButton = new QPushButton(BtnsLayout);
    OKButton->setObjectName(QString::fromUtf8("OKButton"));

    hboxLayout3->addWidget(OKButton);

    CancelButton = new QPushButton(BtnsLayout);
    CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

    hboxLayout3->addWidget(CancelButton);

    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem1);

    LoadButton = new QPushButton(BtnsLayout);
    LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
    LoadButton->setEnabled(true);

    hboxLayout3->addWidget(LoadButton);

    IntroLabel = new QLabel(PolarDialog);
    IntroLabel->setObjectName(QString::fromUtf8("IntroLabel"));
    IntroLabel->setGeometry(QRect(0, 0, 371, 40));
    retranslateUi(PolarDialog);
    QObject::connect(CancelButton, SIGNAL(clicked()), PolarDialog, SLOT(close()));

    QMetaObject::connectSlotsByName(PolarDialog);
    } // setupUi

    void retranslateUi(QDialog *PolarDialog)
    {
    PolarDialog->setWindowTitle(QApplication::translate("PolarDialog", "Enter a polar function", 0, QApplication::UnicodeUTF8));
    FLabel->setText(QApplication::translate("PolarDialog", "R (t, u, v) =", 0, QApplication::UnicodeUTF8));
    NameLabel->setText(QApplication::translate("PolarDialog", "Name of the function", 0, QApplication::UnicodeUTF8));
    DescLabel->setText(QApplication::translate("PolarDialog", "Additional description (optional)", 0, QApplication::UnicodeUTF8));
    OKButton->setText(QApplication::translate("PolarDialog", "&OK", 0, QApplication::UnicodeUTF8));
    CancelButton->setText(QApplication::translate("PolarDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    LoadButton->setText(QApplication::translate("PolarDialog", "&Load Function", 0, QApplication::UnicodeUTF8));
    IntroLabel->setText(QApplication::translate("PolarDialog", "Enter a Polar function below, in C++ syntax, using t, u and v as\n"
"variables.", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(PolarDialog);
    } // retranslateUi

};

namespace Ui {
    class PolarDialog: public Ui_PolarDialog {};
} // namespace Ui

#endif // POLARDIALOG_H
