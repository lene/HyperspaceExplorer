
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
#include "ParameterMap.H"

class Function;

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

        void setFunction(const std::auto_ptr<Function> &);

        std::string print ();

        double tmin () { return atof (Min[0]->text ().toStdString().c_str()); }
        double tmax () { return atof (Max[0]->text ().toStdString().c_str()); }
        unsigned tsteps () { return Slider[0]->value (); }
        double dt () { return (tmax ()-tmin ())/double (tsteps ()); }

        double umin () { return atof (Min[1]->text ().toStdString().c_str()); }
        double umax () { return atof (Max[1]->text ().toStdString().c_str()); }
        unsigned usteps () { return Slider[1]->value (); }
        double du () { return (umax ()-umin ())/double (usteps ()); }

        double vmin () { return atof (Min[2]->text ().toStdString().c_str()); }
        double vmax () { return atof (Max[2]->text ().toStdString().c_str()); }
        unsigned vsteps () { return Slider[2]->value (); }
        double dv () { return (vmax ()-vmin ())/double (vsteps ()); }

    public slots:
        virtual void accept ();

    signals:
        void ApplyChanges (const ParameterMap &);

    private:
        void setParameters(const ParameterMap &);
        ParameterMap parameters;
};

#endif

