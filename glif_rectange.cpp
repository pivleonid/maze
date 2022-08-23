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
  //painter->setBrush(m_color);

  if(m_Start){
      painter->setBrush(Qt::GlobalColor::green);
      painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 10), Qt::AlignCenter, m_up?( QString::number(m_up->m_x) + " "+ QString::number(m_up->m_y)):"");// верхняя точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 150), Qt::AlignCenter, m_down?( QString::number(m_down->m_x) + " "+ QString::number(m_down->m_y)):"");// нижняя точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*3, 100), Qt::AlignCenter, m_right?( QString::number(m_right->m_x) + " "+ QString::number(m_right->m_y)):"");// правая точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius, 100), Qt::AlignCenter, m_left?( QString::number(m_left->m_x) + " "+ QString::number(m_left->m_y)):"");// левая точка
      return;
  }
  if(m_Stop) {
      painter->setBrush(Qt::GlobalColor::darkYellow);
      painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
      //painter->drawText(QRect(-m_radius, 0, m_radius*2, 10), Qt::AlignCenter, "B");
      painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 10), Qt::AlignCenter, m_up?( QString::number(m_up->m_x) + " "+ QString::number(m_up->m_y)):"");// верхняя точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 150), Qt::AlignCenter, m_down?( QString::number(m_down->m_x) + " "+ QString::number(m_down->m_y)):"");// нижняя точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius*3, 100), Qt::AlignCenter, m_right?( QString::number(m_right->m_x) + " "+ QString::number(m_right->m_y)):"");// правая точка
      painter->drawText(QRect(-m_radius, -m_radius, m_radius, 100), Qt::AlignCenter, m_left?( QString::number(m_left->m_x) + " "+ QString::number(m_left->m_y)):"");// левая точка
      return;
  }
  if(m_StopBlock)  painter->setBrush(Qt::GlobalColor::gray);
  //Левая и правая координата
  painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
  painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 10), Qt::AlignCenter, m_up?( QString::number(m_up->m_x) + " "+ QString::number(m_up->m_y)):"");// верхняя точка
  painter->drawText(QRect(-m_radius, -m_radius, m_radius*2, 150), Qt::AlignCenter, m_down?( QString::number(m_down->m_x) + " "+ QString::number(m_down->m_y)):"");// нижняя точка
  painter->drawText(QRect(-m_radius, -m_radius, m_radius*3, 100), Qt::AlignCenter, m_right?( QString::number(m_right->m_x) + " "+ QString::number(m_right->m_y)):"");// правая точка
  painter->drawText(QRect(-m_radius, -m_radius, m_radius, 100), Qt::AlignCenter, m_left?( QString::number(m_left->m_x) + " "+ QString::number(m_left->m_y)):"");// левая точка

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

