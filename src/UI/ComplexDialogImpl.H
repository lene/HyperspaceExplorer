
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "ui_ComplexDialog.h"

class ComplexDialogImpl: public QDialog, public Ui::ComplexDialog {
  Q_OBJECT

public:
  ComplexDialogImpl (QWidget *parent = 0, const char *name =0,
		      bool modal = true, Qt::WFlags f = 0);
  virtual ~ComplexDialogImpl() {}
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
