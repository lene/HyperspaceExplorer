
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_SurfaceDialog.h"
#include "PluginCreator.H"

class SurfaceDialogImpl:
        public QDialog, public Ui::SurfaceDialog, public PluginCreator {
    Q_OBJECT

    public:
        SurfaceDialogImpl (QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~SurfaceDialogImpl() {}

        QString libraryName ();

    public slots:
        virtual bool checkValidity();
        virtual bool loadFunction();

    protected:
        virtual bool doLoadFunction(const QString &);
        virtual void writeSource ();
};
