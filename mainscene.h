#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QWidget>
#include<QLayout>
#include<QPainter>
#include<QFileDialog>
#include<QMouseEvent>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QTimer>
#include<QLabel>
#include<QPixmap>
#include<QVector>
#include<QMap>
#include<QSound>
class MyPushButton:public QPushButton
{
    QString path1;
    QString path2;
public:
    MyPushButton(QString Path1,QString Path2="");

    void animal(int x,int y);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent*event);

};



class MyCoin:public QPushButton
{
public:
    int num;
    bool state;
    QTimer timer;
    bool win;
    MyCoin(bool _state);
    void setPath(QString path);
    void mousePressEvent(QMouseEvent*e);

};



class MainScene : public QMainWindow
{
    Q_OBJECT
    QMenuBar*menubar;
    QMenu* menu;
    QAction* actionback;
    QAction* actionexit;
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QString backpath;
    MyPushButton* stb;
    MyPushButton* back1;
    MyPushButton* back2;
    QLabel*label;
    QVector<QVector<MyCoin*>> mycoinarray;
    QMap<int,QVector<QVector<bool>>> map;
    QLabel* winLabel;
    QTimer timer;
    QSound* sound1;
    QSound* sound2;



public:
    MainScene(QWidget *parent = 0);
    ~MainScene();

    void paintEvent(QPaintEvent *event);

    void init1();

    void init2();

    void init3();

    bool isWin();

    void winAct();

    void unWinAct();

    void animal(QWidget* target,int x,int y);

};









#endif // MAINSCENE_H
