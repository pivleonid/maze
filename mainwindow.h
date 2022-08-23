#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <glif_rectange.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setGlips_numb();
    Glif_Rectange* getRectange(int x, int y);

private:
    Ui::MainWindow *ui;

    QVector< Glif_Rectange* > m_glips;
    QGraphicsScene* m_scena;

    QPoint m_pos;


public slots:
    void slotCustomMenuRequested(QPoint pos);
    void pointA();
    void pointB();
    void add_remStop();

    void generate();
};
#endif // MAINWINDOW_H
