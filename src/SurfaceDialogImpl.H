
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_SurfaceDialog.h"

class SurfaceDialogImpl: public QDialog, public Ui::SurfaceDialog {
  Q_OBJECT

public:
  SurfaceDialogImpl (QWidget *parent = 0, const char *name =0,
		      bool modal = true, Qt::WFlags f = 0);
  virtual ~SurfaceDialogImpl() {}

  QString libraryName ();
  
public slots:
  virtual bool checkValidity();
  virtual bool loadFunction();

private:
  virtual bool loadFunction(const QString &);
  void writeSource ();
  bool compile ();
  bool link ();
  QString LibraryName;
};
