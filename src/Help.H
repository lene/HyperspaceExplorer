
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <qglobal.h>


#if (QT_VERSION < 300)


# include <qmultilinedit.h>

  class HelpWindow: public Q3MultiLineEdit {
    public:
      HelpWindow (QWidget * = 0);
  };


#else


# include <q3mainwindow.h>
# include <q3textbrowser.h>

  class HelpWindow : public Q3MainWindow {
    Q_OBJECT
  public:
    HelpWindow( const QString& home_,  const QString& path, QWidget* parent = 0, const char *name=0 );

  private:
    Q3TextBrowser* browser;
  };


#endif					//	(QT_VERSION < 300)

