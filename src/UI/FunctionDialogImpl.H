
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_FunctionDialog.h"
#include "PluginCreator.H"

/// A Dialog to enter a function from \f$ R^3 \rightarrow R \f$
/** The function which has been entered will then be compiled into a dynamic
 *  library and loaded to be displayed on screen as a Function.
 *  \ingroup UIGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class FunctionDialogImpl:
        public QDialog, public Ui::functionDialog, public PluginCreator {
    Q_OBJECT

    public:
        FunctionDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~FunctionDialogImpl() {}

    private slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    private:
        virtual bool functionPresent(const QString &);
        virtual void writeSource ();
};
