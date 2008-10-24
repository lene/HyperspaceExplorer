
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_PolarDialog.h"
#include "PluginCreator.H"

namespace UI {
    namespace Dialogs {
        /// A Dialog to enter a function from \f$ R^3 \rightarrow R \f$ in polar coordinates
        /** The function is evaluated as \f$ \vec{x} = f(\theta, \phi, \psi) \f$.
         *
         *  The function will then be compiled into a dynamic library and
         *  loaded to be displayed on screen
         *  \todo Make the above definition mathematically correct
         *  \ingroup UIGroup
         *  @author Helge Preuss <scout@hyperspace-travel.de>                 */
        class PolarDialogImpl:
                public QDialog, public Ui::PolarDialog, public PluginCreator {
            Q_OBJECT

            public:
                PolarDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
                virtual ~PolarDialogImpl() {}

            private slots:
                virtual bool checkValidity();
                virtual bool loadFunction();

            private:
                virtual bool functionPresent(const QString &);
                virtual void writeSource ();
        };
    }
}
