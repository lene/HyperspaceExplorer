
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

#ifndef HELP_H
#define HELP_H

#include <QMainWindow>

class QTextBrowser;

/// A popup window displaying the Hyperspace Explorer online help as HTML
/** \author Helge Preuss <lene.preuss@gmail.com>                         */
class HelpWindow : public QMainWindow {
    Q_OBJECT
    public:
        HelpWindow(const QString& home_,  const QString& path = "",
                   QWidget* parent = 0);

    private:
        QTextBrowser* _browser;         ///< Qt widget displaying the help file

        static unsigned defaultWidth;   ///< Default width of the help window
        static unsigned defaultHeight;  ///< Default height of the help window
};


#endif                                          //   HELP_H
