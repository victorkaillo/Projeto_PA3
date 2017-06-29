#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QColor>

class Plotter : public QWidget
{
  Q_OBJECT
private:
  float data, time, oX, oY, x2, y2;
  QColor fundo;

public:
  explicit Plotter(QWidget *parent = 0);
  void paintEvent(QPaintEvent *e);
  void setFundo(int r, int g, int b);
  void plot(int x, int y);

signals:

public slots:
  void setData(int _data);
  void setTime(int _time);
  void setOriginX(int _x);
  void setOriginY(int _y);
};

#endif // PLOTTER_H
