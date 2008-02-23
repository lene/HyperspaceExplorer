
//      project:      hyperspace explorer
//      module:       Help.C
//      contains:     code for displaying the help window
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <iostream>
#include "Help.H"
//Added by qt3to4:
#include <Q3Frame>

using std::cerr;
using std::endl;

#if (QT_VERSION < 300)


/*******************************************************************************
 *  construct and display a rudimentary help window
 *  this is the terribly old version for Qt versions < 3, I should dump this...
 *  @param parent	parent widget
 */
HelpWindow::HelpWindow (QWidget *parent): 
  Q3MultiLineEdit (parent) {
    setCaption ("XQGLWidget Key Help");
    setReadOnly (TRUE);
    setMinimumSize (360, 498);
    setMaximumSize (360, 498);
    resize (360, 498);
    show ();
    insertLine ("");
    insertLine ("you can manipulate the rendered object either ");
    insertLine ("via popup menus, which are self-explaining, or ");	
    insertLine ("with key strokes, which are explained here.\n");
    insertLine ("\n");
    insertLine ("you can also rotate the object by pressing the ");
    insertLine ("left mouse button and dragging the mouse.\n");
    insertLine ("LMB+left/right:     		rotate about y-axis\n");
    insertLine ("LMB+up/down:			rotate about x-axis\n");
    insertLine ("LMB+MMB+up/down:		rotate about z-axis\n");  
    insertLine ("\n");
    insertLine ("MMB+left/right:   		OR\n");
    insertLine ("CTRL+LMB+left/right:		translate along x-axis\n");
    insertLine ("MMB+up/down:			OR\n");
    insertLine ("CTRL+LMB+up/down:		translate along y-axis\n");
    insertLine ("LMB+MMB+left/right:		OR\n");
    insertLine ("CTRL+MMB+up/down:		translate along z-axis\n");
    insertLine ("CTRL+MMB+left/right:		translate along w-axis\n");
    insertLine ("\n");
    insertLine ("SHIFT+LMB+left/right:      	rotate about xy-plane\n");
    insertLine ("SHIFT+LMB+up/down:		rotate about xz-plane\n");
    insertLine ("SHIFT+MMB+left/right:      	rotate about xw-plane\n");
    insertLine ("SHIFT+MMB+up/down:		rotate about yz-plane\n");
    insertLine ("SHIFT+RMB+left/right:      	rotate about yw-plane\n");
    insertLine ("SHIFT+RMB+up/down:		rotate about zw-plane\n");
    insertLine ("\n");
    insertLine ("CTRL-Q: exit");
}

#else


#include <qstatusbar.h>
#include <QStringList>
#include <QFile>
#include <QDir>


/*******************************************************************************
 *  construct and display a help browser window displaying the Help HTML file
 *  @param home_	name of help file
 *  @param _path	directory of help file
 *  @param parent	parent widget
 *  @param name		widget name
 */
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


#endif

