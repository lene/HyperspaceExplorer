
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "FunctionDialog.H"

class FunctionDialogImpl: public FunctionDialog {
  Q_OBJECT

public:
  FunctionDialogImpl (QWidget *parent = 0, const char *name =0,
		      bool modal = true, WFlags f = 0);
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
