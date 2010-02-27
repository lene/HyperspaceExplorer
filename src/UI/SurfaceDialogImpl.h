
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

#include "ui_SurfaceDialog.h"
#include "PluginCreator.h"

namespace UI {
    namespace Dialogs {
        /// A Dialog to enter a function from \f$ R^2 \rightarrow R^4 \f$
        /** The function will then be compiled into a dynamic library and loaded to be
        *  displayed on screen
        *  \ingroup UIGroup
        *  @author Helge Preuss <lene.preuss@gmail.com>                         */
        class SurfaceDialogImpl:
                public QDialog, public Ui::SurfaceDialog, public PluginCreator {
            Q_OBJECT

            public:
                SurfaceDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
                virtual ~SurfaceDialogImpl() {}

            private slots:
                virtual bool checkValidity();
                virtual bool loadFunction();

            private:
                virtual bool functionPresent(const QString &);
                virtual void writeSource ();
        };
    }
}
