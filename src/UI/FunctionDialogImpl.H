
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_FunctionDialog.h"
#include "PluginCreator.H"

class FunctionDialogImpl:
        public QDialog, public Ui::functionDialog, public PluginCreator {
    Q_OBJECT

    public:
        FunctionDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~FunctionDialogImpl() {}

    public slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    protected:
        virtual bool doLoadFunction(const QString &);
        virtual void writeSource ();
};
