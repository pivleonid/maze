#ifndef GLIF_RECTANGEH_H
#define GLIF_RECTANGEH_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

#include <QMenu>

#include <QGraphicsScene>
#include <QPen>

struct xy_cords
{
    uint x;
    uint y;
};

class Glif_Rectange : public QObject, public QGraphicsItem
{
    Q_OBJECT


public:
    size_t       m_radius;
    QColor       m_color;

    Glif_Rectange* m_left = nullptr;
    Glif_Rectange* m_right= nullptr;
    Glif_Rectange* m_up   = nullptr;
    Glif_Rectange* m_down = nullptr;

    Glif_Rectange* m_father = nullptr;
    void getNeighbors(QVector<Glif_Rectange*> &vec){
        if(m_left && !(m_left->m_father))
            vec.append(m_left);
        if(m_right && !(m_right->m_father))
            vec.append(m_right);
        if(m_up && !(m_up->m_father))
            vec.append(m_up);
        if(m_down && !(m_down->m_father))
            vec.append(m_down);
    }


public:
    int m_x = 0;
    int m_y = 0;

    bool m_StopBlock = false;
    bool m_Start = false;
    bool m_Stop = false;



    explicit Glif_Rectange(int x, int y, size_t radius = 50, QColor color = Qt::GlobalColor::white,
                         QObject *parent = nullptr);
    Glif_Rectange(const Glif_Rectange&);
    ~Glif_Rectange()
    {

    }
    void setBold_1();
    void setBold_2();
    void setNormal();

    void switchStart();
    void switchStop();
    void switchStopBlock();


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;


    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        /* РЈСЃС‚Р°РЅР°РІР»РёРІР°РµРј РїРѕР·РёС†РёСЋ РіСЂР°С„РёС‡РµСЃРєРѕРіРѕ СЌР»РµРјРµРЅС‚Р°
         * РІ РіСЂР°С„РёС‡РµСЃРєРѕР№ СЃС†РµРЅРµ, С‚СЂР°РЅСЃР»РёСЂРѕРІР°РІ РєРѕРѕСЂРґРёРЅР°С‚С‹
         * РєСѓСЂСЃРѕСЂР° РІРЅСѓС‚СЂРё РіСЂР°С„РёС‡РµСЃРєРѕРіРѕ СЌР»РµРјРµРЅС‚Р°
         * РІ РєРѕРѕСЂРґРёРЅР°С‚РЅСѓСЋ СЃРёСЃС‚РµРјСѓ РіСЂР°С„РёС‡РµСЃРєРѕР№ СЃС†РµРЅС‹
         * */

//        if( event->buttons() == Qt::MouseButton::LeftButton)
//        {
//            this->setPos(mapToScene(event->pos()));
//            emit moveElement(this);
//        }
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        /* РџСЂРё РЅР°Р¶Р°С‚РёРё РјС‹С€СЊСЋ РЅР° РіСЂР°С„РёС‡РµСЃРєРёР№ СЌР»РµРјРµРЅС‚
         * Р·Р°РјРµРЅСЏРµРј РєСѓСЂСЃРѕСЂ РЅР° СЂСѓРєСѓ, РєРѕС‚РѕСЂР°СЏ РґРµСЂР¶РёС‚ СЌС‚РѕС‚ СЌР»РµРјРµРЅС‚Р°
         * */
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        /* РџСЂРё РѕС‚РїСѓСЃРєР°РЅРёРё РјС‹С€СЊСЋ СЌР»РµРјРµРЅС‚Р°
         * Р·Р°РјРµРЅСЏРµРј РЅР° РѕР±С‹С‡РЅС‹Р№ РєСѓСЂСЃРѕСЂ СЃС‚СЂРµР»РєСѓ
         * */
        Qt::MouseButton btn = event->button();
        if( btn == Qt::MouseButton::RightButton)
        {
        }
        else
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
            Q_UNUSED(event);
        }
    }
signals:
    void moveElement( Glif_Rectange* );

public slots:
};







#endif // GLIF_RECTANGEH_H
