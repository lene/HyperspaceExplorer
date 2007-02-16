/****************************************************************************
** Form implementation generated from reading ui file 'FunctionDialog.ui'
**
** Created: Wed Jul 20 22:11:52 2005
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "FunctionDialog.H"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a FunctionDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FunctionDialog::FunctionDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FunctionDialog" );

    IntroLabel = new QLabel( this, "IntroLabel" );
    IntroLabel->setGeometry( QRect( 0, 0, 259, 20 ) );

    QWidget* privateLayoutWidget = new QWidget( this, "BtnsLayout" );
    privateLayoutWidget->setGeometry( QRect( 0, 120, 360, 30 ) );
    BtnsLayout = new QHBoxLayout( privateLayoutWidget, 0, 6, "BtnsLayout"); 

    OKButton = new QPushButton( privateLayoutWidget, "OKButton" );
    BtnsLayout->addWidget( OKButton );

    CancelButton = new QPushButton( privateLayoutWidget, "CancelButton" );
    BtnsLayout->addWidget( CancelButton );
    Spacer1 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    BtnsLayout->addItem( Spacer1 );

    LoadButton = new QPushButton( privateLayoutWidget, "LoadButton" );
    LoadButton->setEnabled( TRUE );
    BtnsLayout->addWidget( LoadButton );

    QWidget* privateLayoutWidget_2 = new QWidget( this, "FLayout" );
    privateLayoutWidget_2->setGeometry( QRect( 0, 20, 360, 28 ) );
    FLayout = new QHBoxLayout( privateLayoutWidget_2, 0, 6, "FLayout"); 

    FLabel = new QLabel( privateLayoutWidget_2, "FLabel" );
    FLayout->addWidget( FLabel );

    FEdit = new QLineEdit( privateLayoutWidget_2, "FEdit" );
    FLayout->addWidget( FEdit );

    QWidget* privateLayoutWidget_3 = new QWidget( this, "Layout22" );
    privateLayoutWidget_3->setGeometry( QRect( 0, 50, 360, 71 ) );
    Layout22 = new QVBoxLayout( privateLayoutWidget_3, 0, 6, "Layout22"); 

    NameLayout1 = new QHBoxLayout( 0, 0, 6, "NameLayout1"); 

    NameLabel = new QLabel( privateLayoutWidget_3, "NameLabel" );
    NameLayout1->addWidget( NameLabel );

    NameEdit = new QLineEdit( privateLayoutWidget_3, "NameEdit" );
    NameLayout1->addWidget( NameEdit );
    Layout22->addLayout( NameLayout1 );

    Layout21 = new QHBoxLayout( 0, 0, 6, "Layout21"); 

    DescLabel = new QLabel( privateLayoutWidget_3, "DescLabel" );
    DescLabel->setEnabled( TRUE );
    Layout21->addWidget( DescLabel );

    LineEdit12 = new QLineEdit( privateLayoutWidget_3, "LineEdit12" );
    LineEdit12->setEnabled( FALSE );
    Layout21->addWidget( LineEdit12 );
    Layout22->addLayout( Layout21 );
    Spacer3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout22->addItem( Spacer3 );
    languageChange();
    resize( QSize(361, 149).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( CancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( OKButton, SIGNAL( clicked() ), this, SLOT( checkValidity() ) );
    connect( LoadButton, SIGNAL( clicked() ), this, SLOT( loadFunction() ) );

    // tab order
    setTabOrder( FEdit, NameEdit );
    setTabOrder( NameEdit, LineEdit12 );
    setTabOrder( LineEdit12, OKButton );
    setTabOrder( OKButton, CancelButton );
    setTabOrder( CancelButton, LoadButton );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FunctionDialog::~FunctionDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FunctionDialog::languageChange()
{
    setCaption( tr( "Enter a real scalar function" ) );
    IntroLabel->setText( trUtf8( "\x45\x6e\x74\x65\x72\x20\x61\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x66\x3a\x52\xc2\xb3\x2d\x3e\x52\x20\x62\x65\x6c\x6f\x77\x2c\x20\x69\x6e\x20\x43\x2b\x2b\x20\x73\x79\x6e\x74\x61\x78\x2e" ) );
    OKButton->setText( tr( "&OK" ) );
    CancelButton->setText( tr( "&Cancel" ) );
    LoadButton->setText( tr( "&Load Function" ) );
    FLabel->setText( tr( "f (x, y, z) =" ) );
    NameLabel->setText( tr( "Name of the function" ) );
    DescLabel->setText( tr( "Additional description (optional)" ) );
}

bool FunctionDialog::checkValidity()
{
    qWarning( "FunctionDialog::checkValidity(): Not implemented yet" );
    return FALSE;
}

bool FunctionDialog::loadFunction()
{
    qWarning( "FunctionDialog::loadFunction(): Not implemented yet" );
    return FALSE;
}

