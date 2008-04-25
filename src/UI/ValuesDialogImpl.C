
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <qmessagebox.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "ValuesDialogImpl.H"

#include "ParameterMap.H"

using namespace std;

ValuesDialogImpl::ValuesDialogImpl(QWidget *parent, Qt::WFlags f) :
    QDialog (parent, f) {
    setupUi(this);

    TSteps->setText (QString::number (TSlider->value ()));
    USteps->setText (QString::number (USlider->value ()));
    VSteps->setText (QString::number (VSlider->value ()));

    buttonOk->hide();
    buttonCancel->hide();

    if (layout()) layout()->setSizeConstraint(QLayout::SetFixedSize);

    show ();
}

void ValuesDialogImpl::setParameters(const ParameterMap &parms) {
    std::cerr << "ValuesDialogImpl::setParameters(" << parms.print() << ") not yet implemented!" << std::endl;
}

void ValuesDialogImpl::DisplayValues () {
  ostringstream o;
  o << "tsteps: " << TSlider->value () << "\t"	<< "dt    : " << dt () << "\n"
    << "usteps: " << USlider->value () << "\t"	<< "du    : " << du () << "\n"
    << "vsteps: " << VSlider->value () << "\t"	<< "dv    : " << dv () << "\n\n"
    << "a     : " << a () << "\t"
    << "b     : " << b () << "\n"
    << "c     : " << c () << "\t"
    << "d     : " << d () << "\n\n"
    << ends;
  QMessageBox::information (this, QString ("There you are:"), QString (o.str ().c_str ()));
}

void ValuesDialogImpl::CheckNumeric (const QString &) {
  //  QMessageBox::information (this, QString ("There you are:"), QString ("Hi dee Ho"));
}

void ValuesDialogImpl::accept () {
  emit ApplyChanges ();
}


void ValuesDialogImpl::AlignValues(int v) {
  if (TSlider->value () == v && USlider->value () == v && VSlider->value () == v) return;
  TSlider->setValue (v);
  USlider->setValue (v);
  VSlider->setValue (v);
}

void ValuesDialogImpl::aText (const QString &text) {
    ALabel()->setText (text);
}
void ValuesDialogImpl::bText (const QString &text) {
    BLabel()->setText (text);
}
void ValuesDialogImpl::cText (const QString &text) {
    CLabel()->setText (text);
}
void ValuesDialogImpl::dText (const QString &text) {
    DLabel()->setText (text);
}

