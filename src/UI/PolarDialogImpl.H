
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_PolarDialog.h"
#include "PluginCreator.H"

/** A Dialog to enter a function from \f$ R^3 \rightarrow R \f$ in a polar
 *  coordinate system, which will then be compiled into a dynamic library and
 *  loaded to be displayed on screen
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class PolarDialogImpl:
        public QDialog, public Ui::PolarDialog, public PluginCreator {
    Q_OBJECT

    public:
        PolarDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~PolarDialogImpl() {}

    public slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    protected:
        virtual bool functionPresent(const QString &);
        virtual void writeSource ();
};
