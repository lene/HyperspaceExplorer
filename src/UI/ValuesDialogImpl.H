
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#ifndef VALUES_DIALOG_IMPL_H
#define VALUES_DIALOG_IMPL_H

#include <cstdlib>
#include <iostream>

#include <qslider.h>
#include <qlineedit.h>
#include <qcombobox.h>

#include "ui_ValuesDialog.h"

class ValuesDialogImpl: public QDialog, public Ui::ValuesDialog {
  Q_OBJECT

public:
  ValuesDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
  virtual ~ValuesDialogImpl() {}

  double tmin () { return atof (TMin->text ().toStdString().c_str()); }
  double tmax () { return atof (TMax->text ().toStdString().c_str()); }
  unsigned tsteps () { return TSlider->value (); }
  double dt () { return (tmax ()-tmin ())/double (tsteps ()); }

  double umin () { return atof (UMin->text ().toStdString().c_str()); }
  double umax () { return atof (UMax->text ().toStdString().c_str()); }
  unsigned usteps () { return USlider->value (); }
  double du () { return (umax ()-umin ())/double (usteps ()); }

  double vmin () { return atof (VMin->text ().toStdString().c_str()); }
  double vmax () { return atof (VMax->text ().toStdString().c_str()); }
  unsigned vsteps () { return VSlider->value (); }
  double dv () { return (vmax ()-vmin ())/double (vsteps ()); }

  double a () { return atof (A->text ().toStdString().c_str()); }
  double b () { return atof (B->text ().toStdString().c_str()); }
  double c () { return atof (C->text ().toStdString().c_str()); }
  double d () { return atof (D->text ().toStdString().c_str()); }

  int Function () { return FunctionBox->currentIndex(); }
  QString FunctionName () { return FunctionBox->currentText (); }
  void setFunction(const QString &f) { std::cerr << "ValuesDialogImpl::setFunction("<<f.toStdString()<<")"<< std::endl;; }
  int InsertFunction (const QString &FuncName, int index = -1);

public slots:
  virtual void accept ();					//  reimplementation of ValuesDialog::accept ()

  virtual void DisplayValues ();
  virtual void CheckNumeric (const QString &);

  virtual void aText (const QString &);
  virtual void bText (const QString &);
  virtual void cText (const QString &);
  virtual void dText (const QString &);

protected slots:
    virtual void AlignValues(int);

signals:
  void ApplyChanges ();

};

#endif

