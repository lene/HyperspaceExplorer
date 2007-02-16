/****************************************************************************
** Form implementation generated from reading ui file 'PolarDialog.ui'
**
** Created: Wed Jul 20 22:11:52 2005
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "PolarDialog.H"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a PolarDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
PolarDialog::PolarDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "PolarDialog" );

    QWidget* privateLayoutWidget = new QWidget( this, "FLayout" );
    privateLayoutWidget->setGeometry( QRect( 0, 40, 360, 28 ) );
    FLayout = new QHBoxLayout( privateLayoutWidget, 0, 6, "FLayout"); 

    FLabel = new QLabel( privateLayoutWidget, "FLabel" );
    FLayout->addWidget( FLabel );

    FEdit = new QLineEdit( privateLayoutWidget, "FEdit" );
    FLayout->addWidget( FEdit );

    QWidget* privateLayoutWidget_2 = new QWidget( this, "Layout27" );
    privateLayoutWidget_2->setGeometry( QRect( 0, 71, 360, 71 ) );
    Layout27 = new QVBoxLayout( privateLayoutWidget_2, 0, 6, "Layout27"); 

    NameLayout1 = new QHBoxLayout( 0, 0, 6, "NameLayout1"); 

    NameLabel = new QLabel( privateLayoutWidget_2, "NameLabel" );
    NameLayout1->addWidget( NameLabel );

    NameEdit = new QLineEdit( privateLayoutWidget_2, "NameEdit" );
    NameLayout1->addWidget( NameEdit );
    Layout27->addLayout( NameLayout1 );

    Layout21 = new QHBoxLayout( 0, 0, 6, "Layout21"); 

    DescLabel = new QLabel( privateLayoutWidget_2, "DescLabel" );
    Layout21->addWidget( DescLabel );

    LineEdit12 = new QLineEdit( privateLayoutWidget_2, "LineEdit12" );
    LineEdit12->setEnabled( FALSE );
    Layout21->addWidget( LineEdit12 );
    Layout27->addLayout( Layout21 );
    Spacer3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout27->addItem( Spacer3 );

    QWidget* privateLayoutWidget_3 = new QWidget( this, "BtnsLayout" );
    privateLayoutWidget_3->setGeometry( QRect( -10, 150, 360, 30 ) );
    BtnsLayout = new QHBoxLayout( privateLayoutWidget_3, 0, 6, "BtnsLayout"); 

    OKButton = new QPushButton( privateLayoutWidget_3, "OKButton" );
    BtnsLayout->addWidget( OKButton );

    CancelButton = new QPushButton( privateLayoutWidget_3, "CancelButton" );
    BtnsLayout->addWidget( CancelButton );
    Spacer1 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    BtnsLayout->addItem( Spacer1 );

    LoadButton = new QPushButton( privateLayoutWidget_3, "LoadButton" );
    LoadButton->setEnabled( TRUE );
    BtnsLayout->addWidget( LoadButton );

    IntroLabel = new QLabel( this, "IntroLabel" );
    IntroLabel->setGeometry( QRect( 0, 0, 371, 40 ) );
    languageChange();
    resize( QSize(362, 182).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( CancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( OKButton, SIGNAL( clicked() ), this, SLOT( checkValidity() ) );
    connect( LoadButton, SIGNAL( clicked() ), this, SLOT( loadFunction() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
PolarDialog::~PolarDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PolarDialog::languageChange()
{
    setCaption( tr( "Enter a polar function" ) );
    FLabel->setText( tr( "R (t, u, v) =" ) );
    NameLabel->setText( tr( "Name of the function" ) );
    DescLabel->setText( tr( "Additional description (optional)" ) );
    OKButton->setText( tr( "&OK" ) );
    CancelButton->setText( tr( "&Cancel" ) );
    LoadButton->setText( tr( "&Load Function" ) );
    IntroLabel->setText( tr( "Enter a Polar function below, in C++ syntax, using t, u and v as\n"
"variables." ) );
}

bool PolarDialog::checkValidity()
{
    qWarning( "PolarDialog::checkValidity(): Not implemented yet" );
    return FALSE;
}

bool PolarDialog::loadFunction()
{
    qWarning( "PolarDialog::loadFunction(): Not implemented yet" );
    return FALSE;
}

