#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

using namespace std;

Plotter::Plotter(QWidget *parent) :
  QWidget(parent){
  fundo.setRgb(255,255,0);
  setMouseTracking(true);
}


void Plotter::setFundo(int r, int g, int b){
  fundo.setRgb(r,g,b);
  repaint();
}


void Plotter::setTime(int _time){
    time = _time;
    repaint();
}

void Plotter::setData(int _data){
    data = _data;
    repaint();
}

void Plotter::setOriginX(int _x){
    oX = _x;
}

void Plotter::setOriginY(int _y){
    oY = _y;
}

void Plotter::paintEvent(QPaintEvent *e){
  int x1, y1;

  // cria um objeto pintor
  QPainter p(this);

  // faz com que a linha seja desenhada
  // com tracos suaves
  p.setRenderHint(QPainter::Antialiasing);

  // cria um objeto de caneta
  QPen pen;
  // cria um objeto de pincel
  QBrush brush;
  // define a cor da caneta
  pen.setColor(QColor(255,0,0));
  pen.setWidth(2);

  // informa ao painter qual a caneta a ser
  // usada
  p.setPen(pen);

  // define a cor do pincel
  brush.setColor(fundo);
  brush.setStyle(Qt::SolidPattern);

  // informa oa painter qual o pincel a ser
  // usado
  p.setBrush(brush);
  p.drawRect(0,0,width(),height());
  // (x1,y1) -> (x2,y2)
  pen.setColor(QColor(0,0,255));
  p.setPen(pen);

  x1 = oX;
  y1 = oY;
  x2 = time;
  y2 = data;

  p.drawLine(round(x1*width()),height()*(1-(y1/100.0)), round(x2*width()), height()*(1-(y2/100.0)));

  setOriginX(time);
  setOriginY(data);
}

void Plotter::plot(int x, int y){
    oX = x;
    oX = y;
    x2 = time;
    y2 = data;

    repaint();
}
