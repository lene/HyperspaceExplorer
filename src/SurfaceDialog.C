/****************************************************************************
** Form implementation generated from reading ui file 'SurfaceDialog.ui'
**
** Created: Wed Jul 20 22:11:51 2005
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "SurfaceDialog.H"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

/*
 *  Constructs a SurfaceDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SurfaceDialog::SurfaceDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "SurfaceDialog" );

    IntroLabel = new QLabel( this, "IntroLabel" );
    IntroLabel->setGeometry( QRect( 0, 0, 368, 40 ) );

    QWidget* privateLayoutWidget = new QWidget( this, "FunctionsLayout" );
    privateLayoutWidget->setGeometry( QRect( 0, 40, 360, 132 ) );
    FunctionsLayout = new Q3VBoxLayout( privateLayoutWidget, 0, 6, "FunctionsLayout"); 

    XLayout = new Q3HBoxLayout( 0, 0, 6, "XLayout"); 

    XLabel = new QLabel( privateLayoutWidget, "XLabel" );
    XLayout->addWidget( XLabel );

    XEdit = new QLineEdit( privateLayoutWidget, "XEdit" );
    XLayout->addWidget( XEdit );
    FunctionsLayout->addLayout( XLayout );

    YLayout = new Q3HBoxLayout( 0, 0, 6, "YLayout"); 

    YLabel = new QLabel( privateLayoutWidget, "YLabel" );
    YLayout->addWidget( YLabel );

    YEdit = new QLineEdit( privateLayoutWidget, "YEdit" );
    YLayout->addWidget( YEdit );
    FunctionsLayout->addLayout( YLayout );

    ZLayout = new Q3HBoxLayout( 0, 0, 6, "ZLayout"); 

    ZLabel = new QLabel( privateLayoutWidget, "ZLabel" );
    ZLayout->addWidget( ZLabel );

    ZEdit = new QLineEdit( privateLayoutWidget, "ZEdit" );
    ZLayout->addWidget( ZEdit );
    FunctionsLayout->addLayout( ZLayout );

    WLayout = new Q3HBoxLayout( 0, 0, 6, "WLayout"); 

    WLabel = new QLabel( privateLayoutWidget, "WLabel" );
    WLayout->addWidget( WLabel );

    WEdit = new QLineEdit( privateLayoutWidget, "WEdit" );
    WLayout->addWidget( WEdit );
    FunctionsLayout->addLayout( WLayout );

    QWidget* privateLayoutWidget_2 = new QWidget( this, "Layout29" );
    privateLayoutWidget_2->setGeometry( QRect( 0, 180, 360, 71 ) );
    Layout29 = new Q3VBoxLayout( privateLayoutWidget_2, 0, 6, "Layout29"); 

    NameLayout1 = new Q3HBoxLayout( 0, 0, 6, "NameLayout1"); 

    NameLabel = new QLabel( privateLayoutWidget_2, "NameLabel" );
    NameLayout1->addWidget( NameLabel );

    NameEdit = new QLineEdit( privateLayoutWidget_2, "NameEdit" );
    NameLayout1->addWidget( NameEdit );
    Layout29->addLayout( NameLayout1 );

    Layout21 = new Q3HBoxLayout( 0, 0, 6, "Layout21"); 

    DescLabel = new QLabel( privateLayoutWidget_2, "DescLabel" );
    Layout21->addWidget( DescLabel );

    LineEdit12 = new QLineEdit( privateLayoutWidget_2, "LineEdit12" );
    LineEdit12->setEnabled( FALSE );
    Layout21->addWidget( LineEdit12 );
    Layout29->addLayout( Layout21 );
    Spacer2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout29->addItem( Spacer2 );

    QWidget* privateLayoutWidget_3 = new QWidget( this, "BtnsLayout" );
    privateLayoutWidget_3->setGeometry( QRect( 0, 260, 360, 30 ) );
    BtnsLayout = new Q3HBoxLayout( privateLayoutWidget_3, 0, 6, "BtnsLayout"); 

    OKButton = new QPushButton( privateLayoutWidget_3, "OKButton" );
    BtnsLayout->addWidget( OKButton );

    CancelButton = new QPushButton( privateLayoutWidget_3, "CancelButton" );
    BtnsLayout->addWidget( CancelButton );
    Spacer1 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    BtnsLayout->addItem( Spacer1 );

    LoadButton = new QPushButton( privateLayoutWidget_3, "LoadButton" );
    LoadButton->setEnabled( TRUE );
    BtnsLayout->addWidget( LoadButton );
    languageChange();
    resize( QSize(361, 292).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( CancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( OKButton, SIGNAL( clicked() ), this, SLOT( checkValidity() ) );
    connect( LoadButton, SIGNAL( clicked() ), this, SLOT( loadFunction() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
SurfaceDialog::~SurfaceDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SurfaceDialog::languageChange()
{
    setCaption( tr( "Enter a definition for the surface" ) );
    IntroLabel->setText( tr( "A surface in four dimensions is defined with four functions of two\n"
"variables. Please enter these functions below, in C++ syntax." ) );
    XLabel->setText( tr( "X (u, v) =" ) );
    YLabel->setText( tr( "Y (u, v) =" ) );
    ZLabel->setText( tr( "Z (u, v) =" ) );
    WLabel->setText( tr( "W (u, v) =" ) );
    NameLabel->setText( tr( "Name of the function" ) );
    DescLabel->setText( tr( "Additional description (optional)" ) );
    OKButton->setText( tr( "&OK" ) );
    CancelButton->setText( tr( "&Cancel" ) );
    LoadButton->setText( tr( "&Load Function" ) );
}

bool SurfaceDialog::checkValidity()
{
    qWarning( "SurfaceDialog::checkValidity(): Not implemented yet" );
    return FALSE;
}

bool SurfaceDialog::loadFunction()
{
    qWarning( "SurfaceDialog::loadFunction(): Not implemented yet" );
    return FALSE;
}

