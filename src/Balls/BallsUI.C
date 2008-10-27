/****************************************************************************
** Form implementation generated from reading ui file 'BallsUI.ui'
**
** Created: Mon Oct 21 21:51:53 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "BallsUI.H"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a BallsUI which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
BallsUI::BallsUI( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "BallsUI" );
    resize( 333, 370 ); 
    setCaption( trUtf8( "Parameters for bouncing balls" ) );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout21" );
    privateLayoutWidget->setGeometry( QRect( 0, 340, 330, 30 ) ); 
    Layout21 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout21"); 

    TimeProgress = new QProgressBar( privateLayoutWidget, "TimeProgress" );
    Layout21->addWidget( TimeProgress );

    CollisionsLabel = new QLabel( privateLayoutWidget, "CollisionsLabel" );
    CollisionsLabel->setText( trUtf8( "     0 Collisions" ) );
    Layout21->addWidget( CollisionsLabel );

    TabWidget = new QTabWidget( this, "TabWidget" );
    TabWidget->setEnabled( TRUE );
    TabWidget->setGeometry( QRect( 0, 0, 330, 340 ) ); 

    tab = new QWidget( TabWidget, "tab" );

    QWidget* privateLayoutWidget_2 = new QWidget( tab, "Layout22" );
    privateLayoutWidget_2->setGeometry( QRect( 0, 210, 320, 92 ) ); 
    Layout22 = new QVBoxLayout( privateLayoutWidget_2, 0, 6, "Layout22"); 

    Layout19 = new QHBoxLayout( 0, 0, 6, "Layout19"); 

    TextLabel1_8 = new QLabel( privateLayoutWidget_2, "TextLabel1_8" );
    TextLabel1_8->setText( trUtf8( "max. t" ) );
    Layout19->addWidget( TextLabel1_8 );

    TMaxSlider = new QSlider( privateLayoutWidget_2, "TMaxSlider" );
    TMaxSlider->setMaxValue( 100 );
    TMaxSlider->setPageStep( 20 );
    TMaxSlider->setValue( 40 );
    TMaxSlider->setOrientation( QSlider::Horizontal );
    TMaxSlider->setTickmarks( QSlider::Right );
    TMaxSlider->setTickInterval( 20 );
    QToolTip::add( TMaxSlider, trUtf8( "Duration of the simulation (logarithmic scale)" ) );
    QWhatsThis::add( TMaxSlider, trUtf8( "After completion of the indicated time the simulation finishes and prints the count of collisions which have happened" ) );
    Layout19->addWidget( TMaxSlider );

    TMaxLabel = new QLabel( privateLayoutWidget_2, "TMaxLabel" );
    TMaxLabel->setText( trUtf8( "100" ) );
    Layout19->addWidget( TMaxLabel );
    Layout22->addLayout( Layout19 );

    Layout20 = new QHBoxLayout( 0, 0, 6, "Layout20"); 

    TextLabel1_4 = new QLabel( privateLayoutWidget_2, "TextLabel1_4" );
    TextLabel1_4->setText( trUtf8( "Delta t" ) );
    Layout20->addWidget( TextLabel1_4 );

    DTSlider = new QSlider( privateLayoutWidget_2, "DTSlider" );
    DTSlider->setMaxValue( 100 );
    DTSlider->setValue( 40 );
    DTSlider->setOrientation( QSlider::Horizontal );
    DTSlider->setTickmarks( QSlider::Right );
    DTSlider->setTickInterval( 20 );
    QToolTip::add( DTSlider, trUtf8( "Timestep (logarithmic scale)" ) );
    QWhatsThis::add( DTSlider, trUtf8( "The time difference beween two updates - generally the smaller the more accurate, but also the slower" ) );
    Layout20->addWidget( DTSlider );

    DTLabel = new QLabel( privateLayoutWidget_2, "DTLabel" );
    DTLabel->setText( trUtf8( "0.001" ) );
    Layout20->addWidget( DTLabel );
    Layout22->addLayout( Layout20 );

    Layout21_2 = new QHBoxLayout( 0, 0, 6, "Layout21_2"); 

    TextLabel1_5 = new QLabel( privateLayoutWidget_2, "TextLabel1_5" );
    TextLabel1_5->setText( trUtf8( "Steps between two updates" ) );
    Layout21_2->addWidget( TextLabel1_5 );

    StepsSlider = new QSlider( privateLayoutWidget_2, "StepsSlider" );
    StepsSlider->setMaxValue( 200 );
    StepsSlider->setPageStep( 20 );
    StepsSlider->setValue( 20 );
    StepsSlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( StepsSlider, trUtf8( "Calculate steps between two displays" ) );
    QWhatsThis::add( StepsSlider, trUtf8( "Number of steps done between two draw events, without displaying - you'll want to tweak this parameter depending on the number of balls, the dimension of the system and your hardware together with delta t to get the quickest, smoothest motion possible." ) );
    Layout21_2->addWidget( StepsSlider );

    StepsLabel = new QLabel( privateLayoutWidget_2, "StepsLabel" );
    StepsLabel->setText( trUtf8( "20" ) );
    Layout21_2->addWidget( StepsLabel );
    Layout22->addLayout( Layout21_2 );

    QWidget* privateLayoutWidget_3 = new QWidget( tab, "Layout18" );
    privateLayoutWidget_3->setGeometry( QRect( 0, 70, 181, 26 ) ); 
    Layout18 = new QHBoxLayout( privateLayoutWidget_3, 0, 6, "Layout18"); 

    TextLabel1_6 = new QLabel( privateLayoutWidget_3, "TextLabel1_6" );
    TextLabel1_6->setEnabled( TRUE );
    TextLabel1_6->setText( trUtf8( "Dimension" ) );
    Layout18->addWidget( TextLabel1_6 );

    DimensionSlider = new QSlider( privateLayoutWidget_3, "DimensionSlider" );
    DimensionSlider->setEnabled( FALSE );
    DimensionSlider->setMinValue( 2 );
    DimensionSlider->setMaxValue( 10 );
    DimensionSlider->setPageStep( 1 );
    DimensionSlider->setValue( 3 );
    DimensionSlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( DimensionSlider, trUtf8( "Dimension of the system" ) );
    Layout18->addWidget( DimensionSlider );

    DimensionLabel = new QLabel( privateLayoutWidget_3, "DimensionLabel" );
    DimensionLabel->setText( trUtf8( "3" ) );
    Layout18->addWidget( DimensionLabel );

    QWidget* privateLayoutWidget_4 = new QWidget( tab, "Layout23_2" );
    privateLayoutWidget_4->setGeometry( QRect( 0, 10, 320, 58 ) ); 
    Layout23_2 = new QVBoxLayout( privateLayoutWidget_4, 0, 6, "Layout23_2"); 

    Layout15_2 = new QHBoxLayout( 0, 0, 6, "Layout15_2"); 

    TextLabel1_3_2 = new QLabel( privateLayoutWidget_4, "TextLabel1_3_2" );
    TextLabel1_3_2->setFrameShape( QLabel::MShape );
    TextLabel1_3_2->setFrameShadow( QLabel::MShadow );
    TextLabel1_3_2->setText( trUtf8( "Number of Spheres" ) );
    Layout15_2->addWidget( TextLabel1_3_2 );

    NumSpheresSlider = new QSlider( privateLayoutWidget_4, "NumSpheresSlider" );
    NumSpheresSlider->setMaxValue( 1000 );
    NumSpheresSlider->setLineStep( 1 );
    NumSpheresSlider->setPageStep( 50 );
    NumSpheresSlider->setValue( 350 );
    NumSpheresSlider->setOrientation( QSlider::Horizontal );
    NumSpheresSlider->setTickmarks( QSlider::Right );
    NumSpheresSlider->setTickInterval( 250 );
    QToolTip::add( NumSpheresSlider, trUtf8( "Number of displayed spheres (logarithmic scale)" ) );
    QWhatsThis::add( NumSpheresSlider, trUtf8( "With this slider you can create or destroy balls in the system. Be careful with the amount of balls, you don't want your computer to choke because you've gone too high with this value! The computational complexity grows with the square of the number of balls." ) );
    Layout15_2->addWidget( NumSpheresSlider );

    NumSpheresLabel = new QLabel( privateLayoutWidget_4, "NumSpheresLabel" );
    NumSpheresLabel->setText( trUtf8( "25" ) );
    Layout15_2->addWidget( NumSpheresLabel );
    Layout23_2->addLayout( Layout15_2 );

    Layout14_3 = new QHBoxLayout( 0, 0, 6, "Layout14_3"); 

    Layout13_2 = new QHBoxLayout( 0, 0, 6, "Layout13_2"); 

    TextLabel1_7_2 = new QLabel( privateLayoutWidget_4, "TextLabel1_7_2" );
    TextLabel1_7_2->setText( trUtf8( "(max.) Radius" ) );
    Layout13_2->addWidget( TextLabel1_7_2 );

    RMaxSlider = new QSlider( privateLayoutWidget_4, "RMaxSlider" );
    RMaxSlider->setMinValue( 0 );
    RMaxSlider->setMaxValue( 100 );
    RMaxSlider->setValue( 20 );
    RMaxSlider->setOrientation( QSlider::Horizontal );
    QToolTip::add( RMaxSlider, trUtf8( "maximum radius of the displayed spheres" ) );
    QWhatsThis::add( RMaxSlider, trUtf8( "If 'Random size' is set, this denotes the maximum radius of the spheres. If it is unchecked, all newly generated balls have this radius. This option takes effect only on newly generated balls." ) );
    Layout13_2->addWidget( RMaxSlider );

    RMaxLabel = new QLabel( privateLayoutWidget_4, "RMaxLabel" );
    RMaxLabel->setText( trUtf8( "0.2" ) );
    Layout13_2->addWidget( RMaxLabel );
    Layout14_3->addLayout( Layout13_2 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout14_3->addItem( spacer );

    RndSizeCheck = new QCheckBox( privateLayoutWidget_4, "RndSizeCheck" );
    RndSizeCheck->setText( trUtf8( "Random size" ) );
    RndSizeCheck->setChecked( TRUE );
    QWhatsThis::add( RndSizeCheck, trUtf8( "If checked, newly generated balls have random mass and diameter" ) );
    Layout14_3->addWidget( RndSizeCheck );
    Layout23_2->addLayout( Layout14_3 );

    QWidget* privateLayoutWidget_5 = new QWidget( tab, "Layout15" );
    privateLayoutWidget_5->setGeometry( QRect( 0, 100, 320, 102 ) ); 
    Layout15 = new QVBoxLayout( privateLayoutWidget_5, 0, 6, "Layout15"); 

    Layout16 = new QHBoxLayout( 0, 0, 6, "Layout16"); 

    TextLabel1 = new QLabel( privateLayoutWidget_5, "TextLabel1" );
    TextLabel1->setText( trUtf8( "Friction" ) );
    Layout16->addWidget( TextLabel1 );

    FrictionSlider = new QSlider( privateLayoutWidget_5, "FrictionSlider" );
    FrictionSlider->setMinValue( -100 );
    FrictionSlider->setMaxValue( 100 );
    FrictionSlider->setLineStep( 1 );
    FrictionSlider->setPageStep( 25 );
    FrictionSlider->setOrientation( QSlider::Horizontal );
    FrictionSlider->setTickmarks( QSlider::Right );
    FrictionSlider->setTickInterval( 20 );
    QToolTip::add( FrictionSlider, trUtf8( "Friction with the walls" ) );
    QWhatsThis::add( FrictionSlider, trUtf8( "Set negative to turn on the heat, positive to slow down the system" ) );
    Layout16->addWidget( FrictionSlider );

    FrictionLabel = new QLabel( privateLayoutWidget_5, "FrictionLabel" );
    FrictionLabel->setText( trUtf8( "0.0" ) );
    Layout16->addWidget( FrictionLabel );
    Layout15->addLayout( Layout16 );

    Layout17 = new QHBoxLayout( 0, 0, 6, "Layout17"); 

    TextLabel1_2 = new QLabel( privateLayoutWidget_5, "TextLabel1_2" );
    TextLabel1_2->setText( trUtf8( "Gravitation" ) );
    Layout17->addWidget( TextLabel1_2 );

    GravitationSlider = new QSlider( privateLayoutWidget_5, "GravitationSlider" );
    GravitationSlider->setMinValue( 0 );
    GravitationSlider->setMaxValue( 100 );
    GravitationSlider->setOrientation( QSlider::Horizontal );
    GravitationSlider->setTickmarks( QSlider::Right );
    GravitationSlider->setTickInterval( 20 );
    QToolTip::add( GravitationSlider, trUtf8( "Gravity of the system" ) );
    Layout17->addWidget( GravitationSlider );

    GravitationLabel = new QLabel( privateLayoutWidget_5, "GravitationLabel" );
    GravitationLabel->setText( trUtf8( "0.0" ) );
    Layout17->addWidget( GravitationLabel );
    Layout15->addLayout( Layout17 );

    Layout14 = new QHBoxLayout( 0, 0, 6, "Layout14"); 

    TextLabel1_9 = new QLabel( privateLayoutWidget_5, "TextLabel1_9" );
    TextLabel1_9->setText( trUtf8( "Elasticity" ) );
    Layout14->addWidget( TextLabel1_9 );

    ElasticitySlider = new QSlider( privateLayoutWidget_5, "ElasticitySlider" );
    ElasticitySlider->setMinValue( -100 );
    ElasticitySlider->setMaxValue( 200 );
    ElasticitySlider->setLineStep( 1 );
    ElasticitySlider->setPageStep( 25 );
    ElasticitySlider->setValue( 100 );
    ElasticitySlider->setOrientation( QSlider::Horizontal );
    ElasticitySlider->setTickmarks( QSlider::Right );
    ElasticitySlider->setTickInterval( 20 );
    QToolTip::add( ElasticitySlider, trUtf8( "Elasticity of the balls" ) );
    QWhatsThis::add( ElasticitySlider, trUtf8( "Set this to 1 for totally elastic (ping pong) balls, to 0 for totally inelastic (hacky sack) ones. Values above 1 and below 0 are unphysical, but might be interesting." ) );
    Layout14->addWidget( ElasticitySlider );

    ElasticityLabel = new QLabel( privateLayoutWidget_5, "ElasticityLabel" );
    ElasticityLabel->setText( trUtf8( "1.0" ) );
    Layout14->addWidget( ElasticityLabel );
    Layout15->addLayout( Layout14 );
    TabWidget->insertTab( tab, trUtf8( "System parameters" ) );

    tab_2 = new QWidget( TabWidget, "tab_2" );

    QWidget* privateLayoutWidget_6 = new QWidget( tab_2, "Layout16" );
    privateLayoutWidget_6->setGeometry( QRect( 0, 10, 320, 23 ) ); 
    Layout16_2 = new QHBoxLayout( privateLayoutWidget_6, 0, 6, "Layout16_2"); 

    TextLabel1_3 = new QLabel( privateLayoutWidget_6, "TextLabel1_3" );
    TextLabel1_3->setText( trUtf8( "Viewpoint distance" ) );
    Layout16_2->addWidget( TextLabel1_3 );

    XCamSlider = new QSlider( privateLayoutWidget_6, "XCamSlider" );
    XCamSlider->setMinValue( 0 );
    XCamSlider->setMaxValue( 100 );
    XCamSlider->setLineStep( 1 );
    XCamSlider->setPageStep( 25 );
    XCamSlider->setOrientation( QSlider::Horizontal );
    XCamSlider->setTickmarks( QSlider::Right );
    XCamSlider->setTickInterval( 20 );
    QToolTip::add( XCamSlider, trUtf8( "Distance of the camera to the origin" ) );
    QWhatsThis::add( XCamSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout16_2->addWidget( XCamSlider );

    XCamLabel = new QLabel( privateLayoutWidget_6, "XCamLabel" );
    XCamLabel->setText( trUtf8( "0.0" ) );
    Layout16_2->addWidget( XCamLabel );

    QWidget* privateLayoutWidget_7 = new QWidget( tab_2, "Layout20" );
    privateLayoutWidget_7->setGeometry( QRect( 0, 40, 320, 83 ) ); 
    Layout20_2 = new QVBoxLayout( privateLayoutWidget_7, 0, 6, "Layout20_2"); 

    Layout17_2 = new QHBoxLayout( 0, 0, 6, "Layout17_2"); 

    TextLabel1_3_3 = new QLabel( privateLayoutWidget_7, "TextLabel1_3_3" );
    TextLabel1_3_3->setText( trUtf8( "X rotation" ) );
    Layout17_2->addWidget( TextLabel1_3_3 );

    XrotSlider = new QSlider( privateLayoutWidget_7, "XrotSlider" );
    XrotSlider->setMinValue( 0 );
    XrotSlider->setMaxValue( 1000 );
    XrotSlider->setLineStep( 1 );
    XrotSlider->setPageStep( 250 );
    XrotSlider->setOrientation( QSlider::Horizontal );
    XrotSlider->setTickmarks( QSlider::Right );
    XrotSlider->setTickInterval( 125 );
    QToolTip::add( XrotSlider, trUtf8( "X rotation speed" ) );
    QWhatsThis::add( XrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_2->addWidget( XrotSlider );

    XrotLabel = new QLabel( privateLayoutWidget_7, "XrotLabel" );
    XrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_2->addWidget( XrotLabel );
    Layout20_2->addLayout( Layout17_2 );

    Layout17_2_2 = new QHBoxLayout( 0, 0, 6, "Layout17_2_2"); 

    TextLabel1_3_3_2 = new QLabel( privateLayoutWidget_7, "TextLabel1_3_3_2" );
    TextLabel1_3_3_2->setText( trUtf8( "Y rotation" ) );
    Layout17_2_2->addWidget( TextLabel1_3_3_2 );

    YrotSlider = new QSlider( privateLayoutWidget_7, "YrotSlider" );
    YrotSlider->setMinValue( 0 );
    YrotSlider->setMaxValue( 1000 );
    YrotSlider->setLineStep( 1 );
    YrotSlider->setPageStep( 250 );
    YrotSlider->setOrientation( QSlider::Horizontal );
    YrotSlider->setTickmarks( QSlider::Right );
    YrotSlider->setTickInterval( 125 );
    QToolTip::add( YrotSlider, trUtf8( "Y rotation speed" ) );
    QWhatsThis::add( YrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_2_2->addWidget( YrotSlider );

    YrotLabel = new QLabel( privateLayoutWidget_7, "YrotLabel" );
    YrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_2_2->addWidget( YrotLabel );
    Layout20_2->addLayout( Layout17_2_2 );

    Layout17_3 = new QHBoxLayout( 0, 0, 6, "Layout17_3"); 

    TextLabel1_3_3_3 = new QLabel( privateLayoutWidget_7, "TextLabel1_3_3_3" );
    TextLabel1_3_3_3->setText( trUtf8( "Z rotation" ) );
    Layout17_3->addWidget( TextLabel1_3_3_3 );

    ZrotSlider = new QSlider( privateLayoutWidget_7, "ZrotSlider" );
    ZrotSlider->setMinValue( 0 );
    ZrotSlider->setMaxValue( 1000 );
    ZrotSlider->setLineStep( 1 );
    ZrotSlider->setPageStep( 250 );
    ZrotSlider->setOrientation( QSlider::Horizontal );
    ZrotSlider->setTickmarks( QSlider::Right );
    ZrotSlider->setTickInterval( 125 );
    QToolTip::add( ZrotSlider, trUtf8( "Z rotation speed" ) );
    QWhatsThis::add( ZrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_3->addWidget( ZrotSlider );

    ZrotLabel = new QLabel( privateLayoutWidget_7, "ZrotLabel" );
    ZrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_3->addWidget( ZrotLabel );
    Layout20_2->addLayout( Layout17_3 );

    QWidget* privateLayoutWidget_8 = new QWidget( tab_2, "Layout20_2" );
    privateLayoutWidget_8->setGeometry( QRect( 0, 130, 320, 83 ) ); 
    Layout20_2_2 = new QVBoxLayout( privateLayoutWidget_8, 0, 6, "Layout20_2_2"); 

    Layout17_4 = new QHBoxLayout( 0, 0, 6, "Layout17_4"); 

    TextLabel1_3_3_4 = new QLabel( privateLayoutWidget_8, "TextLabel1_3_3_4" );
    TextLabel1_3_3_4->setText( trUtf8( "XW rotation" ) );
    Layout17_4->addWidget( TextLabel1_3_3_4 );

    XWrotSlider = new QSlider( privateLayoutWidget_8, "XWrotSlider" );
    XWrotSlider->setMinValue( 0 );
    XWrotSlider->setMaxValue( 1000 );
    XWrotSlider->setLineStep( 1 );
    XWrotSlider->setPageStep( 250 );
    XWrotSlider->setOrientation( QSlider::Horizontal );
    XWrotSlider->setTickmarks( QSlider::Right );
    XWrotSlider->setTickInterval( 125 );
    QToolTip::add( XWrotSlider, trUtf8( "XW rotation speed" ) );
    QWhatsThis::add( XWrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_4->addWidget( XWrotSlider );

    XWrotLabel = new QLabel( privateLayoutWidget_8, "XWrotLabel" );
    XWrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_4->addWidget( XWrotLabel );
    Layout20_2_2->addLayout( Layout17_4 );

    Layout17_2_2_2 = new QHBoxLayout( 0, 0, 6, "Layout17_2_2_2"); 

    TextLabel1_3_3_2_2 = new QLabel( privateLayoutWidget_8, "TextLabel1_3_3_2_2" );
    TextLabel1_3_3_2_2->setText( trUtf8( "YW rotation" ) );
    Layout17_2_2_2->addWidget( TextLabel1_3_3_2_2 );

    YWrotSlider = new QSlider( privateLayoutWidget_8, "YWrotSlider" );
    YWrotSlider->setMinValue( 0 );
    YWrotSlider->setMaxValue( 1000 );
    YWrotSlider->setLineStep( 1 );
    YWrotSlider->setPageStep( 250 );
    YWrotSlider->setOrientation( QSlider::Horizontal );
    YWrotSlider->setTickmarks( QSlider::Right );
    YWrotSlider->setTickInterval( 125 );
    QToolTip::add( YWrotSlider, trUtf8( "YW rotation speed" ) );
    QWhatsThis::add( YWrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_2_2_2->addWidget( YWrotSlider );

    YWrotLabel = new QLabel( privateLayoutWidget_8, "YWrotLabel" );
    YWrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_2_2_2->addWidget( YWrotLabel );
    Layout20_2_2->addLayout( Layout17_2_2_2 );

    Layout17_3_2 = new QHBoxLayout( 0, 0, 6, "Layout17_3_2"); 

    TextLabel1_3_3_3_2 = new QLabel( privateLayoutWidget_8, "TextLabel1_3_3_3_2" );
    TextLabel1_3_3_3_2->setText( trUtf8( "ZW rotation" ) );
    Layout17_3_2->addWidget( TextLabel1_3_3_3_2 );

    ZWrotSlider = new QSlider( privateLayoutWidget_8, "ZWrotSlider" );
    ZWrotSlider->setMinValue( 0 );
    ZWrotSlider->setMaxValue( 1000 );
    ZWrotSlider->setLineStep( 1 );
    ZWrotSlider->setPageStep( 250 );
    ZWrotSlider->setOrientation( QSlider::Horizontal );
    ZWrotSlider->setTickmarks( QSlider::Right );
    ZWrotSlider->setTickInterval( 125 );
    QToolTip::add( ZWrotSlider, trUtf8( "ZW rotation speed" ) );
    QWhatsThis::add( ZWrotSlider, trUtf8( "This applies to all dimensions, currently it is not possible to change the distance for every dimension independently" ) );
    Layout17_3_2->addWidget( ZWrotSlider );

    ZWrotLabel = new QLabel( privateLayoutWidget_8, "ZWrotLabel" );
    ZWrotLabel->setText( trUtf8( "0.0" ) );
    Layout17_3_2->addWidget( ZWrotLabel );
    Layout20_2_2->addLayout( Layout17_3_2 );
    TabWidget->insertTab( tab_2, trUtf8( "View parameters" ) );

    tab_3 = new QWidget( TabWidget, "tab_3" );

    QWidget* privateLayoutWidget_9 = new QWidget( tab_3, "Layout16_2_2" );
    privateLayoutWidget_9->setGeometry( QRect( 0, 30, 320, 30 ) ); 
    Layout16_2_2 = new QHBoxLayout( privateLayoutWidget_9, 0, 6, "Layout16_2_2"); 

    SaveCheck = new QCheckBox( privateLayoutWidget_9, "SaveCheck" );
    SaveCheck->setText( trUtf8( "Save pictures" ) );
    Layout16_2_2->addWidget( SaveCheck );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout16_2_2->addItem( spacer_2 );

    Layout14_2_2_2 = new QHBoxLayout( 0, 0, 6, "Layout14_2_2_2"); 

    TextLabel1_10_2_2_2 = new QLabel( privateLayoutWidget_9, "TextLabel1_10_2_2_2" );
    TextLabel1_10_2_2_2->setText( trUtf8( "Prefix" ) );
    Layout14_2_2_2->addWidget( TextLabel1_10_2_2_2 );

    SaveEdit = new QLineEdit( privateLayoutWidget_9, "SaveEdit" );
    Layout14_2_2_2->addWidget( SaveEdit );
    Layout16_2_2->addLayout( Layout14_2_2_2 );

    DisplayCheck = new QCheckBox( tab_3, "DisplayCheck" );
    DisplayCheck->setGeometry( QRect( 0, 0, 116, 25 ) ); 
    DisplayCheck->setText( trUtf8( "Display pictures" ) );
    DisplayCheck->setChecked( TRUE );
    QToolTip::add( DisplayCheck, trUtf8( "Switch the display on and off" ) );
    QWhatsThis::add( DisplayCheck, trUtf8( "You might want to turn off the display, if you are generating an animation (with the 'save' option), or simply want to know the number of collisions which have taken place" ) );

    FullscreenCheck = new QCheckBox( tab_3, "FullscreenCheck" );
    FullscreenCheck->setEnabled( FALSE );
    FullscreenCheck->setGeometry( QRect( 230, 0, 90, 25 ) ); 
    FullscreenCheck->setText( trUtf8( "Fullscreen" ) );
    TabWidget->insertTab( tab_3, trUtf8( "Operation" ) );

    // signals and slots connections
    connect( DimensionSlider, SIGNAL( valueChanged(int) ), DimensionLabel, SLOT( setNum(int) ) );
    connect( StepsSlider, SIGNAL( valueChanged(int) ), StepsLabel, SLOT( setNum(int) ) );
    connect( DimensionSlider, SIGNAL( valueChanged(int) ), this, SLOT( DimensionChanged(int) ) );
    connect( FrictionSlider, SIGNAL( valueChanged(int) ), this, SLOT( FrictionChanged(int) ) );
    connect( GravitationSlider, SIGNAL( valueChanged(int) ), this, SLOT( GravitationChanged(int) ) );
    connect( ElasticitySlider, SIGNAL( valueChanged(int) ), this, SLOT( ElasticityChanged(int) ) );
    connect( TMaxSlider, SIGNAL( valueChanged(int) ), this, SLOT( TMaxChanged(int) ) );
    connect( DTSlider, SIGNAL( valueChanged(int) ), this, SLOT( DTChanged(int) ) );
    connect( StepsSlider, SIGNAL( valueChanged(int) ), this, SLOT( StepsChanged(int) ) );
    connect( NumSpheresSlider, SIGNAL( valueChanged(int) ), this, SLOT( NumSpheresChanged(int) ) );
    connect( RMaxSlider, SIGNAL( valueChanged(int) ), this, SLOT( RMaxChanged(int) ) );
    connect( RndSizeCheck, SIGNAL( toggled(bool) ), this, SLOT( RndSizeChanged(bool) ) );
    connect( SaveCheck, SIGNAL( toggled(bool) ), this, SLOT( SaveChanged(bool) ) );
    connect( SaveEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( SaveNameChanged(const QString&) ) );
    connect( XCamSlider, SIGNAL( valueChanged(int) ), this, SLOT( XCamChanged(int) ) );
    connect( XrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( XrotChanged(int) ) );
    connect( YrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( YrotChanged(int) ) );
    connect( ZrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( ZrotChanged(int) ) );
    connect( XWrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( XWrotChanged(int) ) );
    connect( YWrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( YWrotChanged(int) ) );
    connect( ZWrotSlider, SIGNAL( valueChanged(int) ), this, SLOT( ZWrotChanged(int) ) );

    // tab order
    setTabOrder( DimensionSlider, FrictionSlider );
    setTabOrder( FrictionSlider, GravitationSlider );
    setTabOrder( GravitationSlider, ElasticitySlider );
    setTabOrder( ElasticitySlider, TMaxSlider );
    setTabOrder( TMaxSlider, DTSlider );
    setTabOrder( DTSlider, StepsSlider );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
BallsUI::~BallsUI()
{
    // no need to delete child widgets, Qt does it all for us
}

void BallsUI::DimensionChanged(int)
{
    qWarning( "BallsUI::DimensionChanged(int): Not implemented yet!" );
}

void BallsUI::DisplayChanged(bool)
{
    qWarning( "BallsUI::DisplayChanged(bool): Not implemented yet!" );
}

void BallsUI::DTChanged(int)
{
    qWarning( "BallsUI::DTChanged(int): Not implemented yet!" );
}

void BallsUI::ElasticityChanged(int)
{
    qWarning( "BallsUI::ElasticityChanged(int): Not implemented yet!" );
}

void BallsUI::FrictionChanged(int)
{
    qWarning( "BallsUI::FrictionChanged(int): Not implemented yet!" );
}

void BallsUI::GravitationChanged(int)
{
    qWarning( "BallsUI::GravitationChanged(int): Not implemented yet!" );
}

void BallsUI::NumSpheresChanged(int)
{
    qWarning( "BallsUI::NumSpheresChanged(int): Not implemented yet!" );
}

void BallsUI::RMaxChanged(int)
{
    qWarning( "BallsUI::RMaxChanged(int): Not implemented yet!" );
}

void BallsUI::RndSizeChanged(bool)
{
    qWarning( "BallsUI::RndSizeChanged(bool): Not implemented yet!" );
}

void BallsUI::SaveChanged(bool)
{
    qWarning( "BallsUI::SaveChanged(bool): Not implemented yet!" );
}

void BallsUI::SaveNameChanged(const QString&)
{
    qWarning( "BallsUI::SaveNameChanged(const QString&): Not implemented yet!" );
}

void BallsUI::StepsChanged(int)
{
    qWarning( "BallsUI::StepsChanged(int): Not implemented yet!" );
}

void BallsUI::TMaxChanged(int)
{
    qWarning( "BallsUI::TMaxChanged(int): Not implemented yet!" );
}

void BallsUI::XCamChanged(int)
{
    qWarning( "BallsUI::XCamChanged(int): Not implemented yet!" );
}

void BallsUI::XrotChanged(int)
{
    qWarning( "BallsUI::XrotChanged(int): Not implemented yet!" );
}

void BallsUI::XWrotChanged(int)
{
    qWarning( "BallsUI::XWrotChanged(int): Not implemented yet!" );
}

void BallsUI::YrotChanged(int)
{
    qWarning( "BallsUI::YrotChanged(int): Not implemented yet!" );
}

void BallsUI::YWrotChanged(int)
{
    qWarning( "BallsUI::YWrotChanged(int): Not implemented yet!" );
}

void BallsUI::ZrotChanged(int)
{
    qWarning( "BallsUI::ZrotChanged(int): Not implemented yet!" );
}

void BallsUI::ZWrotChanged(int)
{
    qWarning( "BallsUI::ZWrotChanged(int): Not implemented yet!" );
}

