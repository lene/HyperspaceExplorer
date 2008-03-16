
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_PolarDialog.h"
#include "PluginCreator.H"

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
        virtual bool doLoadFunction(const QString &);
        virtual void writeSource ();
};
