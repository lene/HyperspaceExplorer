
//      project:      hyperspace explorer
//      module:       Help.C
//      contains:     code for displaying the help window
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <iostream>

#include <QStatusBar>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextBrowser>

#include "Help.h"
#include "Globals.h"

using std::cerr;
using std::endl;

unsigned HelpWindow::defaultWidth = 850;
unsigned HelpWindow::defaultHeight = 720;

/** construct and display a help browser window displaying the Help HTML file
 *  \param home_	name of help file
 *  \param _path	directory of help file
 *  \param parent	parent widget                                         */
HelpWindow::HelpWindow( const QString& home_, const QString& _path,
                        QWidget* parent)
    : QMainWindow(parent/*, Qt::WA_DeleteOnClose*/) {
    _browser = new QTextBrowser( this );
    QStringList possiblePaths;
    if (_path.size() > 0) {
        possiblePaths.append(_path+"/");
        possiblePaths.append(_path+"/Documentation/");
        possiblePaths.append(_path+"/doc/");
        possiblePaths.append(_path+"/src/Documentation/");
        possiblePaths.append(_path+"/src/doc/");
        possiblePaths.append(QDir::currentPath()+"/Documentation/");
    } else {
         for (QStringList::const_iterator constIterator = Globals::Instance().rcdirs.constBegin();
              constIterator != Globals::Instance().rcdirs.constEnd();
             ++constIterator)
             possiblePaths.append((*constIterator)+"/doc/");
    }
    _browser->setSearchPaths(possiblePaths);
    _browser->setSource(QUrl(home_));
    _browser->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    setCentralWidget( _browser );

    if ( !home_.isEmpty() )
        _browser->setSource( home_ );

    connect( _browser, SIGNAL( highlighted( const QString&) ),
             statusBar(), SLOT( message( const QString&)) );

    resize(defaultWidth, defaultHeight);

    _browser->setFocus();

    setWindowTitle("Hyperspace Explorer Help Browser");
}
