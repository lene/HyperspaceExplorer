
#include <qslider.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qprogressbar.h>

#include "BallsUIImpl.H"


# if (!defined __PI)
#   include <cmath>
    const double pi = 4.*atan (1.);
#   define __PI 3_14
# endif

double percentage (const QSlider *slider) {
  return double (slider->value ())/(double (slider->maxValue ())-double (slider->minValue ()));
}

BallsUIImpl::BallsUIImpl (BoxWidget *_BW,
			  QWidget *parent = 0, const char *name =0,
			  bool modal = true, WFlags f = 0) :
    BallsUI (parent, name, modal, f),
    BW (_BW) {
  DimensionSlider->setValue (BW->getDimension ());
  DisplayCheck->setChecked (BW->getDisplay ());
  DTSlider->setValue (int (20.*log10 (BW->getDeltaT ()/0.00001)));
  ElasticitySlider->setValue (int (BW->getElasticity ()*100));
  FrictionSlider->setValue (int (BW->getFriction ()*100));
  GravitationSlider->setValue (int (BW->getGravitation ()*100));
  NumSpheresSlider->setValue (unsigned (log10(double (BW->getNumBalls ()))*250.));
  RndSizeCheck->setChecked (BW->getRndSize ());
  RMaxSlider->setValue (int (BW->getRMax ()*100));
  SaveCheck->setChecked (BW->getSave ());
  SaveEdit->setText (BW->getSaveName ());
  StepsSlider->setValue (int (BW->getSteps ())); 

  XrotSlider->setValue (int (BW->getRotation (1, 2)));
  YrotSlider->setValue (int (BW->getRotation (0, 2)));
  ZrotSlider->setValue (int (BW->getRotation (0, 1)));
  XWrotSlider->setValue (int (BW->getRotation (0, 3)));
  YWrotSlider->setValue (int (BW->getRotation (1, 3)));
  ZWrotSlider->setValue (int (BW->getRotation (2, 3)));
			
  TimeProgress->setTotalSteps (500);
  startTimer (200);
  
  show ();
}

void BallsUIImpl::DimensionChanged(int) {
  BW->setDimension (DimensionSlider->value ());
}

void BallsUIImpl::DisplayChanged(bool) {
  BW->setDisplay (DisplayCheck->isChecked ());
}

void BallsUIImpl::DTChanged(int) {
  DTLabel->setText (
    QString::number (
		     0.00001*pow (10, percentage (DTSlider)*5.),
		     'g', 3));
  BW->setDeltaT (0.00001*pow (10, percentage (DTSlider)*5.));
}

void BallsUIImpl::ElasticityChanged(int) {
  ElasticityLabel->setText (QString::number (double (ElasticitySlider->value())/100.));
  BW->setElasticity (double (ElasticitySlider->value())/100.);
}

void BallsUIImpl::FrictionChanged(int) {
  FrictionLabel->setText (QString::number (double (FrictionSlider->value())/100.));
  BW->setFriction (double (FrictionSlider->value())/100.);
}

void BallsUIImpl::GravitationChanged(int) {
  GravitationLabel->setText (QString::number (double (percentage (GravitationSlider))));
  BW->setGravitation (double (percentage (GravitationSlider)));
}

void BallsUIImpl::NumSpheresChanged(int) {
  unsigned n =unsigned (pow (10, percentage (NumSpheresSlider)*4.)+0.5);
  NumSpheresLabel->setText (QString::number (n));
  BW->setNumBalls (n);
}

void BallsUIImpl::RMaxChanged(int) {
  RMaxLabel->setText (QString::number (double (percentage (RMaxSlider))));
  BW->setRMax (double (percentage (RMaxSlider)));

}
void BallsUIImpl::RndSizeChanged(bool) {
  BW->setRndSize (RndSizeCheck->isChecked ());
}

void BallsUIImpl::SaveChanged(bool) {
  BW->setSave (SaveCheck->isChecked ());
}

void BallsUIImpl::SaveNameChanged(const QString&) {
  BW->setSaveName (SaveEdit->text ());
}

void BallsUIImpl::StepsChanged(int) {
    BW->setSteps (StepsSlider->value ());
}

void BallsUIImpl::TMaxChanged(int) {
  TMaxLabel->setText (QString::number (pow (10., double (TMaxSlider->value())/20.), 'g', 3));
  BW->setTMax (pow (10., 5.*percentage (TMaxSlider)));
}

void BallsUIImpl::timerEvent(QTimerEvent*) {
  TimeProgress->setProgress (int (BW->getTime ()/pow (10., 5.*percentage (TMaxSlider))*TimeProgress->totalSteps ()));
  CollisionsLabel->setText (QString::number (BW->getCollisions ())+" Collisions");
}

void BallsUIImpl::XCamChanged(int) {
  XCamLabel->setText (QString::number (20.*percentage (XCamSlider)));
  qWarning( "BallsUIImpl::XCamChanged(int): Not implemented yet!" );
}

void BallsUIImpl::XrotChanged(int) {
  XrotLabel->setText (QString::number (percentage (XrotSlider))+" ¶");
  BW->setRotation (1, 2, percentage (XrotSlider)*pi);
}

void BallsUIImpl::YrotChanged(int) {
  YrotLabel->setText (QString::number (percentage (YrotSlider))+" ¶");
  BW->setRotation (0, 2, percentage (YrotSlider)*pi);
}

void BallsUIImpl::ZrotChanged(int) {
  ZrotLabel->setText (QString::number (percentage (ZrotSlider))+" ¶");
  BW->setRotation (0, 1, percentage (ZrotSlider)*pi);
}

void BallsUIImpl::XWrotChanged(int) {
  XWrotLabel->setText (QString::number (percentage (XWrotSlider))+" ¶");
  BW->setRotation (0, 3, percentage (XWrotSlider)*pi);
}

void BallsUIImpl::YWrotChanged(int) {
  YWrotLabel->setText (QString::number (percentage (YWrotSlider))+" ¶");
  BW->setRotation (1, 3, percentage (YWrotSlider)*pi);
}

void BallsUIImpl::ZWrotChanged(int) {
  ZWrotLabel->setText (QString::number (percentage (ZWrotSlider))+" ¶");
  BW->setRotation (2, 3, percentage (ZWrotSlider)*pi);
}

