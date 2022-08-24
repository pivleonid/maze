#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glif_rectange.h"
#include <QQueue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scena = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scena);
    
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(search()));


    generate();


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    QQueue<Glif_Rectange*> queue;
    Glif_Rectange* start = getStart();
    start->m_father = start;
    queue.enqueue(start);
    while(!queue.isEmpty())
    {
        Glif_Rectange* current, *neighbors;
        current = queue.dequeue();
        QVector<Glif_Rectange*> vec;
        current->getNeighbors(vec);

        foreach (auto var, vec) {
            var->m_father = current;
            m_scena->update();
            QApplication::processEvents();
            if (var->m_Stop == true)
            {
                int i;
                i++;

                var->m_go_back = true;
                while(var!=start)
                {
                    var = var->m_father;
                    var->m_go_back = true;
                    m_scena->update();
                    QApplication::processEvents();
                }

                return;
            }
            queue.enqueue(var);
        }
    }

}
Glif_Rectange* MainWindow::getStart()
{
    foreach (auto var, m_glips) {
        if(var->m_Start == true) return var;
    }
    return nullptr;
}

void MainWindow::generate()
{
    m_glips.clear();
    int x_ = ui->spinBox->value();
    int y_ = ui->spinBox_2->value();

    int x = 0, y = 0;

    for(int i = 0; i < y_; i++)
    {

        for(int j = 0; j < x_; j++)
        {
            Glif_Rectange* gliph = new Glif_Rectange(j, i);
            m_scena->addItem(gliph);
            m_glips.append(gliph);

            gliph->setPos(x, y);
            x+=100;
        }
        y += 100;
        x = 0;
    }
    setGlips_numb();
//debug
//    Glif_Rectange* start =  getRectange(0,0);
//    start->m_Start = true;
//    Glif_Rectange* stop =  getRectange(1,3);
//    stop->m_Stop = true;
//    m_scena->update();
//    QApplication::processEvents();

}

void MainWindow::setGlips_numb()
{
    int x = ui->spinBox->value();
    int y = ui->spinBox_2->value();

    foreach (auto var, m_glips) {
        if(var->m_x == 0 && var->m_y == 0)//левый верхний угол
        {
            Glif_Rectange* tmp = getRectange(var->m_x + 1, var->m_y);
            tmp->m_left = var;
            var->m_right  = tmp;

            tmp = getRectange(var->m_x, var->m_y + 1);
            tmp->m_up = var;
            var->m_down  = tmp;

            continue;
        }

        if(var->m_x == 0 && var->m_y == y - 1)//левый нижний угол
        {
            Glif_Rectange* tmp = getRectange(var->m_x, var->m_y - 1);
            tmp->m_down = var;
            var->m_up  = tmp;

            tmp = getRectange(var->m_x + 1, var->m_y);
            tmp->m_left = var;
            var->m_right  = tmp;
            continue;
        }
        if(var->m_x == x - 1 && var->m_y == 0) //правый верхний угол
        {
            Glif_Rectange* tmp = getRectange(var->m_x - 1, var->m_y);
            tmp->m_right = var;
            var->m_left  = tmp;

            tmp = getRectange(var->m_x, var->m_y + 1);
            tmp->m_up = var;
            var->m_down  = tmp;
            continue;
        }
        if(var->m_x == x - 1 && var->m_y == y - 1)//правый нижний угол
        {
            Glif_Rectange* tmp = getRectange(var->m_x, var->m_y - 1);
            tmp->m_down = var;
            var->m_up  = tmp;

            tmp = getRectange(var->m_x - 1, var->m_y);
            tmp->m_right = var;
            var->m_left  = tmp;
            continue;
        }

        //-------------
        Glif_Rectange* tmp = getRectange(var->m_x - 1, var->m_y);
        if(tmp)
            tmp->m_right = var;
        var->m_left  = tmp;

        tmp = getRectange(var->m_x, var->m_y - 1);
        if(tmp)
            tmp->m_down = var;
        var->m_up  = tmp;

        tmp = getRectange(var->m_x + 1, var->m_y);
        if(tmp)
            tmp->m_left = var;
        var->m_right  = tmp;

        tmp = getRectange(var->m_x, var->m_y + 1);
        if(tmp)
            tmp->m_up = var;
        var->m_down  = tmp;

    }
}
Glif_Rectange* MainWindow::getRectange(int x, int y)
{
    int x_ = ui->spinBox->value();
    int y_ = ui->spinBox_2->value();

    if(x < 0 || y < 0)
        return nullptr;
    if(x >= x_ || y >= y_)
        return nullptr;
    int pos = (y * x_) + x;
    return m_glips.at(pos);
}


void MainWindow::slotCustomMenuRequested(const QPoint pos)
{
    QMenu menu(this);
    m_pos = pos;
    //Устанавливаю контекстное меню относительно позиции курсора
    menu.popup(ui->graphicsView->viewport()->mapToGlobal(pos));
    Glif_Rectange* element = dynamic_cast<Glif_Rectange*> (ui->graphicsView->itemAt(pos));

    if( element == nullptr) return;

    QAction* pointA = menu.addAction("Точка А");
    QAction* pointB = menu.addAction("Точка B");
    QAction* addStop     = menu.addAction("Добавить/Удалить Препятствие");
    connect(pointA,     SIGNAL(triggered()), this, SLOT(pointA()));
    connect(pointB,     SIGNAL(triggered()), this, SLOT(pointB()));
    connect(addStop,    SIGNAL(triggered()), this, SLOT(add_remStop()));

    QAction* selectedAction = menu.exec();

}

void MainWindow::pointA(){

    Glif_Rectange* element = dynamic_cast<Glif_Rectange*> (ui->graphicsView->itemAt(m_pos));
    element->switchStart();
    m_scena->update();

}
void MainWindow::pointB(){

    Glif_Rectange* element = dynamic_cast<Glif_Rectange*> (ui->graphicsView->itemAt(m_pos));
    element->switchStop();
    m_scena->update();

}
void MainWindow::add_remStop(){
    Glif_Rectange* element = dynamic_cast<Glif_Rectange*> (ui->graphicsView->itemAt(m_pos));
    element->switchStopBlock();
    if(element->m_StopBlock){
        Glif_Rectange* tmp = getRectange(element->m_x - 1, element->m_y);
        element->m_left = nullptr;
        if(tmp)
            tmp->m_right = nullptr;

        tmp = getRectange(element->m_x + 1, element->m_y);
        element->m_right = nullptr;
        if(tmp)
            tmp->m_left = nullptr;

        tmp = getRectange(element->m_x, element->m_y + 1);
        element->m_down = nullptr;//тут было наоборот проверить
        if(tmp)
            tmp->m_up = nullptr;

        tmp = getRectange(element->m_x, element->m_y - 1);
        element->m_up = nullptr;
        if(tmp)
            tmp->m_down = nullptr;
    }
    else{
        //+ проверка на блок препятствие
        Glif_Rectange* tmp = getRectange(element->m_x - 1, element->m_y);
        if(tmp)
            tmp->m_right = element;
        element->m_left  = tmp;
        if(tmp){
            if(tmp->m_StopBlock)
            {
                tmp->m_right = nullptr;
                element->m_left  = nullptr;
            }
        }


        tmp = getRectange(element->m_x, element->m_y - 1);
        if(tmp)
            tmp->m_down = element;
        element->m_up  = tmp;
        if(tmp){
            if(tmp->m_StopBlock)
            {
                tmp->m_down = nullptr;
                element->m_up  = nullptr;
            }
        }

        tmp = getRectange(element->m_x + 1, element->m_y);
        if(tmp)
            tmp->m_left = element;
        element->m_right  = tmp;
        if(tmp){
            if(tmp->m_StopBlock)
            {
                tmp->m_left = nullptr;
                element->m_right  = nullptr;
            }
        }

        tmp = getRectange(element->m_x, element->m_y + 1);
        if(tmp)
            tmp->m_up = element;
        element->m_down  = tmp;
        if(tmp){
            if(tmp->m_StopBlock)
            {
                tmp->m_up = nullptr;
                element->m_down  = nullptr;
            }
        }
    }



    m_scena->update();
}


