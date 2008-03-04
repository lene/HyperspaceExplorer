
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#ifndef HELP_H
#define HELP_H

#include <QMainWindow>

class QTextBrowser;

class HelpWindow : public QMainWindow {
    Q_OBJECT
    public:
        HelpWindow(const QString& home_,  const QString& path, 
                   QWidget* parent = 0, const char *name=0);

    private:
        QTextBrowser* browser;
  };


#endif                                          //   HELP_H
