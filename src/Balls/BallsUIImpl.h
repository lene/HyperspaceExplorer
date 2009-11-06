#include "BallsUI.H"
#include "BoxWidget.H"

class BallsUIImpl: public BallsUI {
  Q_OBJECT

public:
  BallsUIImpl (BoxWidget *_BW,
	       QWidget *parent = 0, const char *name =0,
	       bool modal = true, WFlags f = 0);

public slots:
  virtual void NumSpheresChanged(int);

protected slots:
// Tab 1
  virtual void DimensionChanged(int);
  virtual void DTChanged(int);
  virtual void ElasticityChanged(int);
  virtual void FrictionChanged(int);
  virtual void GravitationChanged(int);
  virtual void DisplayChanged(bool);
  virtual void RMaxChanged(int);
  virtual void RndSizeChanged(bool);
  virtual void StepsChanged(int);
  virtual void TMaxChanged(int);
// Tab 2
  virtual void XCamChanged(int);
  virtual void XrotChanged(int);
  virtual void XWrotChanged(int);
  virtual void YrotChanged(int);
  virtual void YWrotChanged(int);
  virtual void ZrotChanged(int);
  virtual void ZWrotChanged(int);
// Tab 3
  virtual void SaveChanged(bool);
  virtual void SaveNameChanged(const QString&);

protected:
  void timerEvent( QTimerEvent * );

  BoxWidget *BW;
};
