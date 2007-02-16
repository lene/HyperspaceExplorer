/****************************************************************************
** Form implementation generated from reading ui file 'ValuesDialog.ui'
**
** Created: Wed Jul 20 22:11:49 2005
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "ValuesDialog.H"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ValuesDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ValuesDialog::ValuesDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ValuesDialog" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setSizeGripEnabled( FALSE );

    Grid = new QGroupBox( this, "Grid" );
    Grid->setGeometry( QRect( 3, 7, 341, 200 ) );
    Grid->setFrameShape( QGroupBox::Box );
    Grid->setFrameShadow( QGroupBox::Sunken );

    QWidget* privateLayoutWidget = new QWidget( Grid, "ULayout" );
    privateLayoutWidget->setGeometry( QRect( 10, 80, 320, 27 ) );
    ULayout = new QHBoxLayout( privateLayoutWidget, 0, 6, "ULayout"); 

    ULabel = new QLabel( privateLayoutWidget, "ULabel" );
    ULayout->addWidget( ULabel );

    USlider = new QSlider( privateLayoutWidget, "USlider" );
    USlider->setMinValue( 1 );
    USlider->setMaxValue( 50 );
    USlider->setPageStep( 5 );
    USlider->setValue( 5 );
    USlider->setOrientation( QSlider::Horizontal );
    USlider->setTickmarks( QSlider::Right );
    USlider->setTickInterval( 5 );
    ULayout->addWidget( USlider );

    USteps = new QLabel( privateLayoutWidget, "USteps" );
    ULayout->addWidget( USteps );

    QWidget* privateLayoutWidget_2 = new QWidget( Grid, "VLayout" );
    privateLayoutWidget_2->setGeometry( QRect( 10, 140, 320, 27 ) );
    VLayout = new QHBoxLayout( privateLayoutWidget_2, 0, 6, "VLayout"); 

    VLabel = new QLabel( privateLayoutWidget_2, "VLabel" );
    VLayout->addWidget( VLabel );

    VSlider = new QSlider( privateLayoutWidget_2, "VSlider" );
    VSlider->setMinValue( 1 );
    VSlider->setMaxValue( 50 );
    VSlider->setPageStep( 5 );
    VSlider->setValue( 5 );
    VSlider->setOrientation( QSlider::Horizontal );
    VSlider->setTickmarks( QSlider::Right );
    VSlider->setTickInterval( 5 );
    VLayout->addWidget( VSlider );

    VSteps = new QLabel( privateLayoutWidget_2, "VSteps" );
    VLayout->addWidget( VSteps );

    QWidget* privateLayoutWidget_3 = new QWidget( Grid, "TBoundsLayout" );
    privateLayoutWidget_3->setGeometry( QRect( 70, 50, 240, 26 ) );
    TBoundsLayout = new QHBoxLayout( privateLayoutWidget_3, 0, 6, "TBoundsLayout"); 

    TminLayout = new QHBoxLayout( 0, 0, 6, "TminLayout"); 

    TextLabel12 = new QLabel( privateLayoutWidget_3, "TextLabel12" );
    TminLayout->addWidget( TextLabel12 );

    TMin = new QLineEdit( privateLayoutWidget_3, "TMin" );
    TminLayout->addWidget( TMin );
    TBoundsLayout->addLayout( TminLayout );

    TmaxLayout = new QHBoxLayout( 0, 0, 6, "TmaxLayout"); 

    TextLabel11 = new QLabel( privateLayoutWidget_3, "TextLabel11" );
    TmaxLayout->addWidget( TextLabel11 );

    TMax = new QLineEdit( privateLayoutWidget_3, "TMax" );
    TmaxLayout->addWidget( TMax );
    TBoundsLayout->addLayout( TmaxLayout );

    QWidget* privateLayoutWidget_4 = new QWidget( Grid, "UBoundsLayout" );
    privateLayoutWidget_4->setGeometry( QRect( 70, 110, 240, 26 ) );
    UBoundsLayout = new QHBoxLayout( privateLayoutWidget_4, 0, 6, "UBoundsLayout"); 

    UminLayout = new QHBoxLayout( 0, 0, 6, "UminLayout"); 

    TextLabel12_2 = new QLabel( privateLayoutWidget_4, "TextLabel12_2" );
    UminLayout->addWidget( TextLabel12_2 );

    UMin = new QLineEdit( privateLayoutWidget_4, "UMin" );
    UminLayout->addWidget( UMin );
    UBoundsLayout->addLayout( UminLayout );

    UMaxLayout = new QHBoxLayout( 0, 0, 6, "UMaxLayout"); 

    TextLabel11_2 = new QLabel( privateLayoutWidget_4, "TextLabel11_2" );
    UMaxLayout->addWidget( TextLabel11_2 );

    UMax = new QLineEdit( privateLayoutWidget_4, "UMax" );
    UMaxLayout->addWidget( UMax );
    UBoundsLayout->addLayout( UMaxLayout );

    QWidget* privateLayoutWidget_5 = new QWidget( Grid, "VBoundsLayout" );
    privateLayoutWidget_5->setGeometry( QRect( 70, 170, 240, 26 ) );
    VBoundsLayout = new QHBoxLayout( privateLayoutWidget_5, 0, 6, "VBoundsLayout"); 

    VminLayout = new QHBoxLayout( 0, 0, 6, "VminLayout"); 

    TextLabel12_2_2 = new QLabel( privateLayoutWidget_5, "TextLabel12_2_2" );
    VminLayout->addWidget( TextLabel12_2_2 );

    VMin = new QLineEdit( privateLayoutWidget_5, "VMin" );
    VminLayout->addWidget( VMin );
    VBoundsLayout->addLayout( VminLayout );

    VMaxLayout = new QHBoxLayout( 0, 0, 6, "VMaxLayout"); 

    TextLabel11_2_2 = new QLabel( privateLayoutWidget_5, "TextLabel11_2_2" );
    VMaxLayout->addWidget( TextLabel11_2_2 );

    VMax = new QLineEdit( privateLayoutWidget_5, "VMax" );
    VMaxLayout->addWidget( VMax );
    VBoundsLayout->addLayout( VMaxLayout );

    QWidget* privateLayoutWidget_6 = new QWidget( Grid, "TLayout" );
    privateLayoutWidget_6->setGeometry( QRect( 10, 20, 320, 27 ) );
    TLayout = new QHBoxLayout( privateLayoutWidget_6, 0, 6, "TLayout"); 

    TLabel = new QLabel( privateLayoutWidget_6, "TLabel" );
    TLayout->addWidget( TLabel );

    TSlider = new QSlider( privateLayoutWidget_6, "TSlider" );
    TSlider->setMinValue( 1 );
    TSlider->setMaxValue( 50 );
    TSlider->setPageStep( 5 );
    TSlider->setValue( 5 );
    TSlider->setOrientation( QSlider::Horizontal );
    TSlider->setTickmarks( QSlider::Right );
    TSlider->setTickInterval( 5 );
    TLayout->addWidget( TSlider );

    TSteps = new QLabel( privateLayoutWidget_6, "TSteps" );
    TLayout->addWidget( TSteps );

    QWidget* privateLayoutWidget_7 = new QWidget( this, "Layout1" );
    privateLayoutWidget_7->setGeometry( QRect( 0, 360, 340, 30 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget_7, 0, 6, "Layout1"); 

    buttonApply = new QPushButton( privateLayoutWidget_7, "buttonApply" );
    buttonApply->setAutoDefault( TRUE );
    Layout1->addWidget( buttonApply );

    buttonOk = new QPushButton( privateLayoutWidget_7, "buttonOk" );
    buttonOk->setEnabled( FALSE );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget_7, "buttonCancel" );
    buttonCancel->setEnabled( FALSE );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    Function = new QGroupBox( this, "Function" );
    Function->setGeometry( QRect( 3, 210, 340, 150 ) );

    QWidget* privateLayoutWidget_8 = new QWidget( Function, "Parameters" );
    privateLayoutWidget_8->setGeometry( QRect( 10, 60, 320, 70 ) );
    Parameters = new QVBoxLayout( privateLayoutWidget_8, 0, 6, "Parameters"); 

    AB = new QHBoxLayout( 0, 0, 6, "AB"); 

    A_in = new QHBoxLayout( 0, 0, 6, "A_in"); 

    ALabel = new QLabel( privateLayoutWidget_8, "ALabel" );
    A_in->addWidget( ALabel );

    A = new QLineEdit( privateLayoutWidget_8, "A" );
    A_in->addWidget( A );
    AB->addLayout( A_in );

    B_in = new QHBoxLayout( 0, 0, 6, "B_in"); 

    BLabel = new QLabel( privateLayoutWidget_8, "BLabel" );
    B_in->addWidget( BLabel );

    B = new QLineEdit( privateLayoutWidget_8, "B" );
    B_in->addWidget( B );
    AB->addLayout( B_in );
    Parameters->addLayout( AB );

    CD = new QHBoxLayout( 0, 0, 6, "CD"); 

    C_in = new QHBoxLayout( 0, 0, 6, "C_in"); 

    CLabel = new QLabel( privateLayoutWidget_8, "CLabel" );
    C_in->addWidget( CLabel );

    C = new QLineEdit( privateLayoutWidget_8, "C" );
    C_in->addWidget( C );
    CD->addLayout( C_in );

    D_in = new QHBoxLayout( 0, 0, 6, "D_in"); 

    DLabel = new QLabel( privateLayoutWidget_8, "DLabel" );
    D_in->addWidget( DLabel );

    D = new QLineEdit( privateLayoutWidget_8, "D" );
    D_in->addWidget( D );
    CD->addLayout( D_in );
    Parameters->addLayout( CD );

    FunctionBox = new QComboBox( FALSE, Function, "FunctionBox" );
    FunctionBox->setEnabled( FALSE );
    FunctionBox->setGeometry( QRect( 76, 20, 250, 22 ) );

    TextLabel13 = new QLabel( Function, "TextLabel13" );
    TextLabel13->setEnabled( FALSE );
    TextLabel13->setGeometry( QRect( 11, 21, 60, 22 ) );
    languageChange();
    resize( QSize(345, 399).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( TSlider, SIGNAL( valueChanged(int) ), TSteps, SLOT( setNum(int) ) );
    connect( USlider, SIGNAL( valueChanged(int) ), USteps, SLOT( setNum(int) ) );
    connect( VSlider, SIGNAL( valueChanged(int) ), VSteps, SLOT( setNum(int) ) );
    connect( A, SIGNAL( textChanged(const QString&) ), this, SLOT( CheckNumeric(const QString&) ) );
    connect( B, SIGNAL( textChanged(const QString&) ), this, SLOT( CheckNumeric(const QString&) ) );
    connect( C, SIGNAL( textChanged(const QString&) ), this, SLOT( CheckNumeric(const QString&) ) );
    connect( D, SIGNAL( textChanged(const QString&) ), this, SLOT( CheckNumeric(const QString&) ) );
    connect( buttonApply, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( TSlider, SIGNAL( valueChanged(int) ), this, SLOT( AlignValues(int) ) );
    connect( USlider, SIGNAL( valueChanged(int) ), this, SLOT( AlignValues(int) ) );
    connect( VSlider, SIGNAL( valueChanged(int) ), this, SLOT( AlignValues(int) ) );

    // tab order
    setTabOrder( TSlider, TMin );
    setTabOrder( TMin, TMax );
    setTabOrder( TMax, USlider );
    setTabOrder( USlider, UMin );
    setTabOrder( UMin, UMax );
    setTabOrder( UMax, VSlider );
    setTabOrder( VSlider, VMin );
    setTabOrder( VMin, VMax );
    setTabOrder( VMax, FunctionBox );
    setTabOrder( FunctionBox, A );
    setTabOrder( A, B );
    setTabOrder( B, C );
    setTabOrder( C, D );
    setTabOrder( D, buttonApply );
    setTabOrder( buttonApply, buttonOk );
    setTabOrder( buttonOk, buttonCancel );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ValuesDialog::~ValuesDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ValuesDialog::languageChange()
{
    setCaption( tr( "Enter Values for the Function" ) );
    QWhatsThis::add( this, tr( "In this dialog window the user can enter up to four parameters to the displayed four-dimensional function or object.\n"
"She con also change the resolution of the grid." ) );
    Grid->setTitle( tr( "Grid Size and Bounds" ) );
    ULabel->setText( tr( "Steps in u" ) );
    USteps->setText( tr( "1" ) );
    VLabel->setText( tr( "Steps in v" ) );
    VSteps->setText( tr( "1" ) );
    TextLabel12->setText( tr( "tmin" ) );
    TMin->setText( tr( "-1" ) );
    QToolTip::add( TMin, tr( "enter '-pi' if you mean -3.1415..." ) );
    TextLabel11->setText( tr( "tmax" ) );
    TMax->setText( tr( "1" ) );
    QToolTip::add( TMax, tr( "or 'pi' if you want 3.1415..." ) );
    TextLabel12_2->setText( tr( "umin" ) );
    UMin->setText( tr( "-1" ) );
    QToolTip::add( UMin, tr( "enter '-pi' if you mean -3.1415..." ) );
    TextLabel11_2->setText( tr( "umax" ) );
    UMax->setText( tr( "1" ) );
    QToolTip::add( UMax, tr( "or 'pi' if you want 3.1415..." ) );
    TextLabel12_2_2->setText( tr( "vmin" ) );
    VMin->setText( tr( "-1" ) );
    QToolTip::add( VMin, tr( "enter '-pi' if you mean -3.1415..." ) );
    TextLabel11_2_2->setText( tr( "vmax" ) );
    VMax->setText( tr( "1" ) );
    QToolTip::add( VMax, tr( "or 'pi' if you want 3.1415..." ) );
    TLabel->setText( tr( "Steps in t" ) );
    TSteps->setText( tr( "1" ) );
    buttonApply->setText( tr( "&Apply" ) );
    QToolTip::add( buttonApply, tr( "Accept changes and redraw" ) );
    buttonOk->setText( tr( "&OK" ) );
    QToolTip::add( buttonOk, tr( "Apply changes, redraw and close this window" ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    QToolTip::add( buttonCancel, tr( "Discard changes" ) );
    Function->setTitle( tr( "Function and Parameters" ) );
    ALabel->setText( tr( "Parameter A" ) );
    A->setText( tr( "1" ) );
    BLabel->setText( tr( "Parameter B" ) );
    B->setText( tr( "0.5" ) );
    CLabel->setText( tr( "Parameter C" ) );
    C->setText( tr( "0.25" ) );
    DLabel->setText( tr( "Parameter D" ) );
    D->setText( tr( "0" ) );
    TextLabel13->setText( tr( "Function" ) );
}

void ValuesDialog::AlignValues(int)
{
    qWarning( "ValuesDialog::AlignValues(int): Not implemented yet" );
}

void ValuesDialog::CheckNumeric(const QString&)
{
    qWarning( "ValuesDialog::CheckNumeric(const QString&): Not implemented yet" );
}

void ValuesDialog::DisplayValues()
{
    qWarning( "ValuesDialog::DisplayValues(): Not implemented yet" );
}

