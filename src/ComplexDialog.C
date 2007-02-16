/****************************************************************************
** Form implementation generated from reading ui file 'ComplexDialog.ui'
**
** Created: Wed Jul 20 22:11:51 2005
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "ComplexDialog.H"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ComplexDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ComplexDialog::ComplexDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ComplexDialog" );

    QWidget* privateLayoutWidget = new QWidget( this, "WLayout" );
    privateLayoutWidget->setGeometry( QRect( 0, 60, 360, 28 ) );
    WLayout = new QHBoxLayout( privateLayoutWidget, 0, 6, "WLayout"); 

    WLabel = new QLabel( privateLayoutWidget, "WLabel" );
    WLayout->addWidget( WLabel );

    WEdit = new QLineEdit( privateLayoutWidget, "WEdit" );
    WLayout->addWidget( WEdit );

    QWidget* privateLayoutWidget_2 = new QWidget( this, "Layout25" );
    privateLayoutWidget_2->setGeometry( QRect( 0, 90, 360, 73 ) );
    Layout25 = new QVBoxLayout( privateLayoutWidget_2, 0, 6, "Layout25"); 

    Layout24 = new QVBoxLayout( 0, 0, 6, "Layout24"); 

    NameLayout1 = new QHBoxLayout( 0, 0, 6, "NameLayout1"); 

    NameLabel = new QLabel( privateLayoutWidget_2, "NameLabel" );
    NameLayout1->addWidget( NameLabel );

    NameEdit = new QLineEdit( privateLayoutWidget_2, "NameEdit" );
    NameLayout1->addWidget( NameEdit );
    Layout24->addLayout( NameLayout1 );

    Layout21 = new QHBoxLayout( 0, 0, 6, "Layout21"); 

    DescLabel = new QLabel( privateLayoutWidget_2, "DescLabel" );
    Layout21->addWidget( DescLabel );

    LineEdit12 = new QLineEdit( privateLayoutWidget_2, "LineEdit12" );
    LineEdit12->setEnabled( FALSE );
    Layout21->addWidget( LineEdit12 );
    Layout24->addLayout( Layout21 );
    Layout25->addLayout( Layout24 );
    Spacer3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout25->addItem( Spacer3 );

    QWidget* privateLayoutWidget_3 = new QWidget( this, "BtnsLayout" );
    privateLayoutWidget_3->setGeometry( QRect( 0, 170, 360, 30 ) );
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
    IntroLabel->setGeometry( QRect( 0, 0, 353, 60 ) );
    languageChange();
    resize( QSize(361, 201).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( CancelButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( OKButton, SIGNAL( clicked() ), this, SLOT( checkValidity() ) );
    connect( LoadButton, SIGNAL( clicked() ), this, SLOT( loadFunction() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ComplexDialog::~ComplexDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ComplexDialog::languageChange()
{
    setCaption( tr( "Enter a complex function" ) );
    WLabel->setText( tr( "w (z) =" ) );
    NameLabel->setText( tr( "Name of the function" ) );
    DescLabel->setText( tr( "Additional description (optional)" ) );
    OKButton->setText( tr( "&OK" ) );
    CancelButton->setText( tr( "&Cancel" ) );
    LoadButton->setText( tr( "&Load Function" ) );
    IntroLabel->setText( tr( "Enter a complex function below, in C++ syntax, using z.real ()\n"
"and z.imag () for the real and complex part of the argument\n"
"(if necessary)." ) );
}

bool ComplexDialog::checkValidity()
{
    qWarning( "ComplexDialog::checkValidity(): Not implemented yet" );
    return FALSE;
}

bool ComplexDialog::loadFunction()
{
    qWarning( "ComplexDialog::loadFunction(): Not implemented yet" );
    return FALSE;
}

