
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
//Added by qt3to4:
#include <Q3Frame>

#include "Help.H"

using std::cerr;
using std::endl;

/** construct and display a help browser window displaying the Help HTML file
 *  @param home_	name of help file
 *  @param _path	directory of help file
 *  @param parent	parent widget
 *  @param name		widget name                                           */
HelpWindow::HelpWindow( const QString& home_, const QString& _path,
                        QWidget* parent, const char *name )
  : QMainWindow( parent, name, Qt::WDestructiveClose ) {
    browser = new QTextBrowser( this );
    QStringList possiblePaths;
    possiblePaths.append(_path+"/");
    possiblePaths.append(_path+"/Documentation/");
    possiblePaths.append(_path+"/src/Documentation/");
    possiblePaths.append(QDir::currentPath()+"/Documentation/");

    browser->setSearchPaths(possiblePaths);
    browser->setSource(QUrl(home_));
    browser->setFrameStyle( Q3Frame::Panel | Q3Frame::Sunken );
    
    setCentralWidget( browser );

    if ( !home_.isEmpty() )
        browser->setSource( home_ );

    connect( browser, SIGNAL( highlighted( const QString&) ),
             statusBar(), SLOT( message( const QString&)) );

    resize( 640,700 );

    browser->setFocus();

    setCaption ("Hyperspace Explorer Help Browser");
}
