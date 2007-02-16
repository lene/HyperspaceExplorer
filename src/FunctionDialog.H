#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

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

class Ui_FunctionDialog
{
public:
    QLabel *IntroLabel;
    QWidget *BtnsLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem;
    QPushButton *LoadButton;
    QWidget *FLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *FLabel;
    QLineEdit *FEdit;
    QWidget *Layout22;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout2;
    QLabel *NameLabel;
    QLineEdit *NameEdit;
    QHBoxLayout *hboxLayout3;
    QLabel *DescLabel;
    QLineEdit *LineEdit12;
    QSpacerItem *spacerItem1;

    void setupUi(QDialog *FunctionDialog)
    {
    FunctionDialog->setObjectName(QString::fromUtf8("FunctionDialog"));
    FunctionDialog->resize(QSize(361, 149).expandedTo(FunctionDialog->minimumSizeHint()));
    IntroLabel = new QLabel(FunctionDialog);
    IntroLabel->setObjectName(QString::fromUtf8("IntroLabel"));
    IntroLabel->setGeometry(QRect(0, 0, 259, 20));
    BtnsLayout = new QWidget(FunctionDialog);
    BtnsLayout->setObjectName(QString::fromUtf8("BtnsLayout"));
    BtnsLayout->setGeometry(QRect(0, 120, 360, 30));
    hboxLayout = new QHBoxLayout(BtnsLayout);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    OKButton = new QPushButton(BtnsLayout);
    OKButton->setObjectName(QString::fromUtf8("OKButton"));

    hboxLayout->addWidget(OKButton);

    CancelButton = new QPushButton(BtnsLayout);
    CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

    hboxLayout->addWidget(CancelButton);

    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    LoadButton = new QPushButton(BtnsLayout);
    LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
    LoadButton->setEnabled(true);

    hboxLayout->addWidget(LoadButton);

    FLayout = new QWidget(FunctionDialog);
    FLayout->setObjectName(QString::fromUtf8("FLayout"));
    FLayout->setGeometry(QRect(0, 20, 360, 28));
    hboxLayout1 = new QHBoxLayout(FLayout);
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    FLabel = new QLabel(FLayout);
    FLabel->setObjectName(QString::fromUtf8("FLabel"));

    hboxLayout1->addWidget(FLabel);

    FEdit = new QLineEdit(FLayout);
    FEdit->setObjectName(QString::fromUtf8("FEdit"));

    hboxLayout1->addWidget(FEdit);

    Layout22 = new QWidget(FunctionDialog);
    Layout22->setObjectName(QString::fromUtf8("Layout22"));
    Layout22->setGeometry(QRect(0, 50, 360, 71));
    vboxLayout = new QVBoxLayout(Layout22);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    NameLabel = new QLabel(Layout22);
    NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

    hboxLayout2->addWidget(NameLabel);

    NameEdit = new QLineEdit(Layout22);
    NameEdit->setObjectName(QString::fromUtf8("NameEdit"));

    hboxLayout2->addWidget(NameEdit);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    DescLabel = new QLabel(Layout22);
    DescLabel->setObjectName(QString::fromUtf8("DescLabel"));
    DescLabel->setEnabled(true);

    hboxLayout3->addWidget(DescLabel);

    LineEdit12 = new QLineEdit(Layout22);
    LineEdit12->setObjectName(QString::fromUtf8("LineEdit12"));
    LineEdit12->setEnabled(false);

    hboxLayout3->addWidget(LineEdit12);


    vboxLayout->addLayout(hboxLayout3);

    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem1);

    QWidget::setTabOrder(FEdit, NameEdit);
    QWidget::setTabOrder(NameEdit, LineEdit12);
    QWidget::setTabOrder(LineEdit12, OKButton);
    QWidget::setTabOrder(OKButton, CancelButton);
    QWidget::setTabOrder(CancelButton, LoadButton);
    retranslateUi(FunctionDialog);
    QObject::connect(CancelButton, SIGNAL(clicked()), FunctionDialog, SLOT(close()));

    QMetaObject::connectSlotsByName(FunctionDialog);
    } // setupUi

    void retranslateUi(QDialog *FunctionDialog)
    {
    FunctionDialog->setWindowTitle(QApplication::translate("FunctionDialog", "Enter a real scalar function", 0, QApplication::UnicodeUTF8));
    IntroLabel->setText(QApplication::translate("FunctionDialog", "Enter a function f:R\302\263->R below, in C++ syntax.", 0, QApplication::UnicodeUTF8));
    OKButton->setText(QApplication::translate("FunctionDialog", "&OK", 0, QApplication::UnicodeUTF8));
    CancelButton->setText(QApplication::translate("FunctionDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
    LoadButton->setText(QApplication::translate("FunctionDialog", "&Load Function", 0, QApplication::UnicodeUTF8));
    FLabel->setText(QApplication::translate("FunctionDialog", "f (x, y, z) =", 0, QApplication::UnicodeUTF8));
    NameLabel->setText(QApplication::translate("FunctionDialog", "Name of the function", 0, QApplication::UnicodeUTF8));
    DescLabel->setText(QApplication::translate("FunctionDialog", "Additional description (optional)", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FunctionDialog);
    } // retranslateUi

};

namespace Ui {
    class FunctionDialog: public Ui_FunctionDialog {};
} // namespace Ui

#endif // FUNCTIONDIALOG_H
