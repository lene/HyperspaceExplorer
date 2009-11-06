
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_ComplexDialog.h"
#include "PluginCreator.h"

namespace UI {
    namespace Dialogs {
        /// A Dialog to enter a user-defined complex function, \f$ f: C \rightarrow C \f$
        /** The function will then be compiled into a dynamic library and loaded to be
        *  displayed on screen.
        *  \ingroup UIGroup
        *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
        class ComplexDialogImpl:
                public QDialog, public Ui::ComplexDialog, public PluginCreator {
            Q_OBJECT

            public:
                ComplexDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
                virtual ~ComplexDialogImpl() {}

            private slots:
                virtual bool checkValidity();
                virtual bool loadFunction();

            private:
                virtual bool functionPresent(const QString &);
                virtual void writeSource ();
        };
    }
}
