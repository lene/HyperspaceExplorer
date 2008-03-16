
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_ComplexDialog.h"
#include "PluginCreator.H"

class ComplexDialogImpl:
        public QDialog, public Ui::ComplexDialog, public PluginCreator {
    Q_OBJECT

    public:
        ComplexDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~ComplexDialogImpl() {}

    public slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    protected:
        virtual bool doLoadFunction(const QString &);
        virtual void writeSource ();
};
