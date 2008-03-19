
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_SurfaceDialog.h"
#include "PluginCreator.H"

/** A Dialog to enter a function from \f$ R^2 \rightarrow R^4 \f$, which will
 *  then be compiled into a dynamic library and loaded to be displayed on
 *  screen
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class SurfaceDialogImpl:
        public QDialog, public Ui::SurfaceDialog, public PluginCreator {
    Q_OBJECT

    public:
        SurfaceDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~SurfaceDialogImpl() {}

    public slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    protected:
        virtual bool functionPresent(const QString &);
        virtual void writeSource ();
};
