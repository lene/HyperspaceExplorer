
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <qapplication.h>
#include <qstringlist.h>
#include <qstring.h>
#include <qdir.h>
#include "4DView.H"

QStringList rcdirs;

void help (QString progname) {
  cout << "Usage:" << endl
       << progname << " [--rcdir dir]" << endl
       << progname << " [-h | --help]" << endl;
}
  
void parse (int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    if (QString (argv[i]) == QString ("--rcdir"))
      if (i+1 < argc) rcdirs.append (QString (argv[i+1]));
    if (QString (argv[i]) == QString ("--help") ||
	QString (argv[i]) == QString ("-h")) {
      help (argv[0]);
      exit (0);
    }
  }
}


int main (int argc, char *argv[]) {
  QApplication app (argc, argv);

  QString rcdir (".HyperspaceExplorer");
  //  if default rc directory does not yet exist, create it
  if (!QDir::home ().exists (rcdir))
    QDir::home ().mkdir (rcdir);
  //  if numclass module for linking custom functions does not exist, copy it
  if (!QDir::home ().exists (rcdir+"/plugins"))
    QDir::home ().mkdir (rcdir+"/plugins");
  if (!QDir::home ().exists (rcdir+"/plugins/numclass.o")) {
#   if 0    
    cerr << (qApp->applicationDirPath ()+"/numclass.o").ascii () << " "
	 << (rcdir+"/plugins/numclass.o").ascii () << " "
	 << symlink ((qApp->applicationDirPath ()+"/numclass.o").ascii (),
		     (QDir::home ().absPath ()+"/"+rcdir+"/plugins/numclass.o").ascii () ) << " "
	 << strerror (errno) << endl 
	 << qApp->applicationDirPath ()+"/numclass.H " 
	 << symlink ((qApp->applicationDirPath ()+"/numclass.H").ascii (),
		     (QDir::home ().absPath ()+"/"+rcdir+"/plugins/numclass.H").ascii () ) << " "
	 << strerror (errno) << endl;
#   else
    symlink ((qApp->applicationDirPath ()+"/numclass.o").ascii (),
	     (QDir::home ().absPath ()+"/"+rcdir+"/plugins/numclass.o").ascii () );
    symlink ((qApp->applicationDirPath ()+"/numclass.H").ascii (),
	     (QDir::home ().absPath ()+"/"+rcdir+"/plugins/numclass.H").ascii () );
#   endif    
  }  
  rcdirs.append (QDir::home ().absPath ()+"/"+rcdir);
  
  parse (argc, argv);

  rcdirs.append (".");

  C4DView view;
  app.setMainWidget (&view);

  int ret = app.exec ();
  return ret;
}
