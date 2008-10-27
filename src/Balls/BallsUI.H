/****************************************************************************
** Form interface generated from reading ui file 'BallsUI.ui'
**
** Created: Mon Oct 21 21:51:52 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef BALLSUI_H
#define BALLSUI_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QCheckBox;
class QLabel;
class QLineEdit;
class QProgressBar;
class QSlider;
class QTabWidget;
class QWidget;

class BallsUI : public QDialog
{ 
    Q_OBJECT

public:
    BallsUI( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~BallsUI();

    QProgressBar* TimeProgress;
    QLabel* CollisionsLabel;
    QTabWidget* TabWidget;
    QWidget* tab;
    QLabel* TextLabel1_8;
    QSlider* TMaxSlider;
    QLabel* TMaxLabel;
    QLabel* TextLabel1_4;
    QSlider* DTSlider;
    QLabel* DTLabel;
    QLabel* TextLabel1_5;
    QSlider* StepsSlider;
    QLabel* StepsLabel;
    QLabel* TextLabel1_6;
    QSlider* DimensionSlider;
    QLabel* DimensionLabel;
    QLabel* TextLabel1_3_2;
    QSlider* NumSpheresSlider;
    QLabel* NumSpheresLabel;
    QLabel* TextLabel1_7_2;
    QSlider* RMaxSlider;
    QLabel* RMaxLabel;
    QCheckBox* RndSizeCheck;
    QLabel* TextLabel1;
    QSlider* FrictionSlider;
    QLabel* FrictionLabel;
    QLabel* TextLabel1_2;
    QSlider* GravitationSlider;
    QLabel* GravitationLabel;
    QLabel* TextLabel1_9;
    QSlider* ElasticitySlider;
    QLabel* ElasticityLabel;
    QWidget* tab_2;
    QLabel* TextLabel1_3;
    QSlider* XCamSlider;
    QLabel* XCamLabel;
    QLabel* TextLabel1_3_3;
    QSlider* XrotSlider;
    QLabel* XrotLabel;
    QLabel* TextLabel1_3_3_2;
    QSlider* YrotSlider;
    QLabel* YrotLabel;
    QLabel* TextLabel1_3_3_3;
    QSlider* ZrotSlider;
    QLabel* ZrotLabel;
    QLabel* TextLabel1_3_3_4;
    QSlider* XWrotSlider;
    QLabel* XWrotLabel;
    QLabel* TextLabel1_3_3_2_2;
    QSlider* YWrotSlider;
    QLabel* YWrotLabel;
    QLabel* TextLabel1_3_3_3_2;
    QSlider* ZWrotSlider;
    QLabel* ZWrotLabel;
    QWidget* tab_3;
    QCheckBox* SaveCheck;
    QLabel* TextLabel1_10_2_2_2;
    QLineEdit* SaveEdit;
    QCheckBox* DisplayCheck;
    QCheckBox* FullscreenCheck;


protected slots:
    virtual void DimensionChanged(int);
    virtual void DisplayChanged(bool);
    virtual void DTChanged(int);
    virtual void ElasticityChanged(int);
    virtual void FrictionChanged(int);
    virtual void GravitationChanged(int);
    virtual void NumSpheresChanged(int);
    virtual void RMaxChanged(int);
    virtual void RndSizeChanged(bool);
    virtual void SaveChanged(bool);
    virtual void SaveNameChanged(const QString&);
    virtual void StepsChanged(int);
    virtual void TMaxChanged(int);
    virtual void XCamChanged(int);
    virtual void XrotChanged(int);
    virtual void XWrotChanged(int);
    virtual void YrotChanged(int);
    virtual void YWrotChanged(int);
    virtual void ZrotChanged(int);
    virtual void ZWrotChanged(int);

protected:
    QHBoxLayout* Layout21;
    QVBoxLayout* Layout22;
    QHBoxLayout* Layout19;
    QHBoxLayout* Layout20;
    QHBoxLayout* Layout21_2;
    QHBoxLayout* Layout18;
    QVBoxLayout* Layout23_2;
    QHBoxLayout* Layout15_2;
    QHBoxLayout* Layout14_3;
    QHBoxLayout* Layout13_2;
    QVBoxLayout* Layout15;
    QHBoxLayout* Layout16;
    QHBoxLayout* Layout17;
    QHBoxLayout* Layout14;
    QHBoxLayout* Layout16_2;
    QVBoxLayout* Layout20_2;
    QHBoxLayout* Layout17_2;
    QHBoxLayout* Layout17_2_2;
    QHBoxLayout* Layout17_3;
    QVBoxLayout* Layout20_2_2;
    QHBoxLayout* Layout17_4;
    QHBoxLayout* Layout17_2_2_2;
    QHBoxLayout* Layout17_3_2;
    QHBoxLayout* Layout16_2_2;
    QHBoxLayout* Layout14_2_2_2;
};

#endif // BALLSUI_H
