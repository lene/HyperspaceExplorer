
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

#include <QSlider>
#include <QLineEdit>
#include <QComboBox>

#include "ValuesDialog.H"

#include "Log.H"

class ParameterMap;

/** A Dialog to enter parameters for the displayed function.
 *
 *  These parameters encompass the definition space, the resolution of the
 *  grid on which the function's values are sampled and displayed, as well as
 *  parameters which are specific to the function.
 *
 *  The switching on and off of input fields, depending on which function is
 *  selected, is done from C4DView. This is of course unfortunate and will be
 *  changed.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class ValuesDialogImpl: public QDialog, public Ui::ValuesDialog {
  Q_OBJECT

public:
    ValuesDialogImpl(QWidget *parent = 0, Qt::WFlags f = 0);
    virtual ~ValuesDialogImpl() {}

    void setParameters(const ParameterMap &);
    
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

    QLineEdit *&A() { return Parameter[0]; }
    QLineEdit *&B() { return Parameter[1]; }
    QLineEdit *&C() { return Parameter[2]; }
    QLineEdit *&D() { return Parameter[3]; }

    QLabel *&ALabel() { return ParameterLabel[0]; }
    QLabel *&BLabel() { return ParameterLabel[1]; }
    QLabel *&CLabel() { return ParameterLabel[2]; }
    QLabel *&DLabel() { return ParameterLabel[3]; }

    double a () { return atof (A()->text ().toStdString().c_str()); }
    double b () { return atof (B()->text ().toStdString().c_str()); }
    double c () { return atof (C()->text ().toStdString().c_str()); }
    double d () { return atof (D()->text ().toStdString().c_str()); }

public slots:
  virtual void accept ();   //  reimplementation of ValuesDialog::accept ()

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

