
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

#include "Help.H"
#include "Globals.H"

using std::cerr;
using std::endl;

/** construct and display a help browser window displaying the Help HTML file
 *  @param home_	name of help file
 *  @param _path	directory of help file
 *  @param parent	parent widget
 *  @param name		widget name                                           */
HelpWindow::HelpWindow( const QString& home_, const QString& _path,
                        QWidget* parent)
    : QMainWindow(parent/*, Qt::WA_DeleteOnClose*/) {
    browser = new QTextBrowser( this );
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
    browser->setSearchPaths(possiblePaths);
    browser->setSource(QUrl(home_));
    browser->setFrameStyle( QFrame::Panel | QFrame::Sunken );

    setCentralWidget( browser );

    if ( !home_.isEmpty() )
        browser->setSource( home_ );

    connect( browser, SIGNAL( highlighted( const QString&) ),
             statusBar(), SLOT( message( const QString&)) );

    resize( 640,700 );

    browser->setFocus();

    setWindowTitle("Hyperspace Explorer Help Browser");
}
