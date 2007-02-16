#ifndef COMPLEXDIALOG_H
#define COMPLEXDIALOG_H

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

class Ui_ComplexDialog
{
public:
    QWidget *WLayout;
    QHBoxLayout *hboxLayout;
    QLabel *WLabel;
    QLineEdit *WEdit;
    QWidget *Layout25;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
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

    void setupUi(QDialog *ComplexDialog)
    {
    ComplexDialog->setObjectName(QString::fromUtf8("ComplexDialog"));
    ComplexDialog->resize(QSize(361, 201).expandedTo(ComplexDialog->minimumSizeHint()));
    WLayout = new QWidget(ComplexDialog);
    WLayout->setObjectName(QString::fromUtf8("WLayout"));
    WLayout->setGeometry(QRect(0, 60, 360, 28));
    hboxLayout = new QHBoxLayout(WLayout);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    WLabel = new QLabel(WLayout);
    WLabel->setObjectName(QString::fromUtf8("WLabel"));

    hboxLayout->addWidget(WLabel);

    WEdit = new QLineEdit(WLayout);
    WEdit->setObjectName(QString::fromUtf8("WEdit"));

    hboxLayout->addWidget(WEdit);

    Layout25 = new QWidget(ComplexDialog);
    Layout25->setObjectName(QString::fromUtf8("Layout25"));
    Layout25->setGeometry(QRect(0, 90, 360, 73));
    vboxLayout = new QVBoxLayout(Layout25);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    NameLabel = new QLabel(Layout25);
    NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

    hboxLayout1->addWidget(NameLabel);

    NameEdit = new QLineEdit(Layout25);
    NameEdit->setObjectName(QString::fromUtf8("NameEdit"));

    hboxLayout1->addWidget(NameEdit);


    vboxLayout1->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    DescLabel = new QLabel(Layout25);
    DescLabel->setObjectName(QString::fromUtf8("DescLabel"));

    hboxLayout2->addWidget(DescLabel);

    LineEdit12 = new QLineEdit(Layout25);
    LineEdit12->setObjectName(QString::fromUtf8("LineEdit12"));
    LineEdit12->setEnabled(false);

    hboxLayout2->addWidget(LineEdit12);


    vboxLayout1->addLayout(hboxLayout2);


    vboxLayout->addLayout(vboxLayout1);

    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem);

    BtnsLayout = new QWidget(ComplexDialog);
    BtnsLayout->setObjectName(QString::fromUtf8("BtnsLayout"));
    BtnsLayout->setGeometry(QRect(0, 170, 360, 30));
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

    IntroLabel = new QLabel(ComplexDialog);
    IntroLabel->setObjectName(QString::fromUtf8("IntroLabel"));
    IntroLabel->setGeometry(QRect(0, 0, 353, 60));
    retranslateUi(ComplexDialog);
    QObject::connect(CancelButton, SIGNAL(clicked()), ComplexDialog, SLOT(close()));

    QMetaObject::connectSlotsByName(ComplexDialog);
    } // setupUi

    void retranslateUi(QDialog *ComplexDialog)
    {
    ComplexDialog->setWindowTitle(QApplication::translate("ComplexDialog", "Enter a complex function", 0, QApplication::UnicodeUTF8));
    WLabel->setText(QApplication::translate("ComplexDialog", "w (z) =", 0, QApplication::UnicodeUTF8));
    NameLabel->setText(QApplication::translate("ComplexDialog", "Name of the function", 0, QApplication::UnicodeUTF8));
    DescLabel->setText(QApplication::translate("ComplexDialog", "Additional description (optional)", 0, QApplication::UnicodeUTF8));
    OKButton->setText(QApplication::translate("ComplexDialog", "&OK", 0, QApplication::UnicodeUTF8));
    CancelButton->setText(QApplication::translate("ComplexDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    LoadButton->setText(QApplication::translate("ComplexDialog", "&Load Function", 0, QApplication::UnicodeUTF8));
    IntroLabel->setText(QApplication::translate("ComplexDialog", "Enter a complex function below, in C++ syntax, using z.real ()\n"
"and z.imag () for the real and complex part of the argument\n"
"(if necessary).", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ComplexDialog);
    } // retranslateUi

};

namespace Ui {
    class ComplexDialog: public Ui_ComplexDialog {};
} // namespace Ui

#endif // COMPLEXDIALOG_H
