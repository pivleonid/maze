#include "glif_rectange.h"



Glif_Rectange::Glif_Rectange( int x, int y, size_t radius, QColor color, QObject *parent)
    : QObject(parent), QGraphicsItem(), m_radius(radius), m_color(color), m_x(x), m_y(y)
{

}


QRectF Glif_Rectange::boundingRect() const {
  return QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius));
}
void Glif_Rectange::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{


  painter->setPen(QPen(Qt::black, 0, Qt::SolidLine));
  painter->setBrush(m_color);

  if(m_Start)
  {

      QRectF A(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius));
      painter->setBrush(Qt::GlobalColor::green);
      painter->drawText(A, Qt::AlignCenter, "m_name");

      return; //не понял почему цвет и надпись не появляются

  }
  if(m_Stop)  painter->setBrush(Qt::GlobalColor::darkYellow);
  if(m_StopBlock)  painter->setBrush(Qt::GlobalColor::gray);



  //Левая и правая координата
  painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
}

void Glif_Rectange::switchStart()
{
    if(m_Start)
        m_Start = false;
    else
        m_Start = true;

}
void Glif_Rectange::switchStop(){
    if(m_Stop)
        m_Stop = false;
    else
        m_Stop = true;

}
void Glif_Rectange::switchStopBlock(){
    if(m_StopBlock)
        m_StopBlock = false;
    else
        m_StopBlock = true;
}

