#include "mainscene.h"



MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    ,backpath(":/image/PlayLevelSceneBg.png")
{
    setFixedSize(320,593);
    //初始化成员变量：
    menubar=menuBar();
    setMenuBar(menubar);
    menu=new QMenu("设置");
    menubar->addMenu(menu);
    actionback=new QAction("背景");
    menu->addAction(actionback);
    actionexit=new QAction("退出");
    menu->addAction(actionexit);
    for(int i=1;i<=20;i++)
    {
        map[i].resize(4);
        for(auto &e:map[i])
        {
            e.resize(4);
            for(auto&k:e)
            {
                k=rand()%2;
            }
        }
    }
    mycoinarray.resize(4);
    for(int i=0;i<4;i++)
    {
       mycoinarray[i].resize(4);
       for(int j=0;j<4;j++)
       {
           mycoinarray[i][j]=new MyCoin(true);
           MyCoin*p=mycoinarray[i][j];
           connect(p,p->clicked,[=](){
               sound1->play();
               p->timer.start(40);
               if(i-1>=0)
                   mycoinarray[i-1][j]->timer.start(60);
               if(i+1<4)
                   mycoinarray[i+1][j]->timer.start(60);
               if(j-1>=0)
                   mycoinarray[i][j-1]->timer.start(60);
               if(j+1<4)
                   mycoinarray[i][j+1]->timer.start(60);
               QTimer::singleShot(600,this,[=](){
                   if(isWin())
                   {
                       winAct();
                       sound1->play();
                   }
               });
           });
       }
    }
    widget1=new QWidget();
    init1();
    widget2=new QWidget();
    init2();
    widget3=new QWidget();
    init3();
    setCentralWidget(widget1);
    sound1=new QSound(":/image/123.wav");
    sound2=new QSound(":/image/456.mp3");

    //设置抬头：
    setWindowIcon(QIcon(":/image/Coin0001.png"));
    setWindowTitle("翻金币主场景");

    connect(actionback,actionback->triggered,[=](){
        QString path=QFileDialog::getOpenFileName(this,"选择背景","..","(*.png *.jpg)");
        if(path.size())
        {
            backpath=path;
        }
    });
    connect(actionexit,actionexit->triggered,[=](){
        close();
    });
    connect(stb,stb->clicked,[=](){
        sound1->play();
        QTimer::singleShot(20,this,[=](){
            widget1->setParent(0);
            setCentralWidget(widget2);
            backpath=":/image/OtherSceneBg.png";
            setWindowTitle("选择游戏关卡");
        });

    });
    connect(back1,back1->clicked,[=](){
        sound1->play();
        QTimer::singleShot(5,this,[=](){
            widget2->setParent(0);
            setCentralWidget(widget1);
            backpath=":/image/PlayLevelSceneBg.png";
            setWindowTitle("翻金币主场景");
        });
    });
    connect(back2,back2->clicked,[=](){
        sound1->play();
        QTimer::singleShot(5,this,[=](){
            widget3->setParent(0);
            setCentralWidget(widget2);
            backpath=":/image/OtherSceneBg.png";
            setWindowTitle("选择游戏关卡");
            if(isWin())
                unWinAct();
        });
    });
    map[1]={{1,1,0,1},{1,0,0,0},{1,1,0,1},{1,1,1,1}};




}

MainScene::~MainScene()
{

}



 void MainScene::paintEvent(QPaintEvent *event)
 {
     QPainter painter(this);
     painter.drawPixmap(centralWidget()->geometry(),QPixmap(backpath));
     if(centralWidget()==widget3)
         return;
     painter.drawPixmap(10,30,200,50,QPixmap(":/image/Title.png"));
 }


 void MainScene::init1()
 {
    stb=new MyPushButton(":/image/MenuSceneStartButton.png");
    stb->setParent(widget1);
    stb->move(width()/2-stb->width()/2,height()*0.6);
 }
 void MainScene::init2()
 {
     back1=new MyPushButton(":/image/BackButton.png",":/image/BackButtonSelected.png");
     back1->setParent(widget2);
     back1->move(width()-back1->width(),height()-back1->height()-23);
     for(int i=0;i<20;i++)
     {
         QPushButton* bt=new QPushButton();
         bt->setParent(widget2);
         QPixmap pix(":/image/LevelIcon.png");
         bt->setFixedSize(pix.width(),pix.height());
         bt->setIcon(pix);
         bt->setIconSize(pix.size());
         bt->setStyleSheet("QPushButton{background:transparent}");
         QLabel* label=new QLabel(QString::number(i+1),widget2);
         label->setFixedSize(bt->width(),bt->height());
         label->setAlignment(Qt::AlignCenter);
         bt->move(55-bt->width()/2+i%4*70,130+i/4*70);
         label->move(55-bt->width()/2+i%4*70,130+i/4*70);
         label->setAttribute(Qt::WA_TransparentForMouseEvents);
         connect(bt,bt->clicked,[=](){
             sound1->play();
             widget2->setParent(0);
             setCentralWidget(widget3);
             backpath=":/image/MenuSceneBg.png";
             setWindowTitle("翻金币场景");
             this->label->setText(QString("level:%1 ").arg(i+1));
             for(int k=0;k<4;k++)
             {
                 for(int j=0;j<4;j++)
                 {
                     if(map[i+1][k][j])
                     {
                         mycoinarray[k][j]->state=true;
                         mycoinarray[k][j]->setPath(":/image/Coin0001.png");
                     }
                     else
                     {
                         mycoinarray[k][j]->state=false;
                         mycoinarray[k][j]->setPath(":/image/Coin0008.png");
                     }
                 }
             }
        });
    }
}
 void MainScene::init3()
 {
     back2=new MyPushButton(":/image/BackButton.png",":/image/BackButtonSelected.png");
     back2->setParent(widget3);
     back2->move(width()-back2->width(),height()-back2->height()-23);
     label=new QLabel(widget3);
     label->setGeometry(85,10,150,40);
     label->setAlignment(Qt::AlignCenter);
     label->setFont(QFont("华文新魏",20));
     winLabel=new QLabel(widget3);
     QPixmap pix(":/image/LevelCompletedDialogBg.png");
     winLabel->setFixedSize(pix.width(),pix.height());
     winLabel->setPixmap(pix);
     winLabel->move(160-winLabel->width()/2,-winLabel->height());




     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++)
         {
             QLabel* lab=new QLabel(widget3);
             lab->setFixedSize(50,50);
             lab->move(60+j*50,260+i*50);
             lab->setPixmap(QPixmap(":/image/BoardNode.png"));
             MyCoin* coin=mycoinarray[i][j];
             coin->setParent(widget3);
             coin->move(60+j*50,260+i*50);
             coin->setFixedSize(50,50);
         }
     }


 }
 bool MainScene::isWin()
 {
     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++)
         {
             if(!mycoinarray[i][j]->state)
                 return false;
         }
     }
     return true;
 }
 void MainScene::winAct()
 {
     animal(winLabel,0,150);
     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++)
         {
             mycoinarray[i][j]->win=true;
         }
     }
 }

 void MainScene:: unWinAct()
 {
     animal(winLabel,0,-150);
     for(int i=0;i<4;i++)
     {
         for(int j=0;j<4;j++)
         {
             mycoinarray[i][j]->win=false;
         }
     }
 }

 void MainScene::animal(QWidget* target,int x,int y)
 {
    static QPropertyAnimation* animation=new QPropertyAnimation();
    animation->setTargetObject(target);
    animation->setPropertyName("geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(target->geometry()));
    animation->setEndValue(QRect(target->x()+x,target->y()+y,target->width(),target->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
 }



 MyPushButton::MyPushButton(QString Path1,QString Path2)
     :path1(Path1)
     ,path2(Path2)
 {
     QPixmap map(path1);
     int w=map.width();
     int h=map.height();
     setFixedSize(w,h);
     setStyleSheet("QPushButton{background:transparent}");
     setIcon(map);
     setIconSize(QSize(w,h));
 }

 void MyPushButton::animal(int x,int y)
 {
    static QPropertyAnimation* animation=new QPropertyAnimation();
    animation->setTargetObject(this);
    animation->setPropertyName("geometry");
    animation->setDuration(10);
    animation->setStartValue(QRect(geometry()));
    animation->setEndValue(QRect(this->x()+x,this->y()+y,width(),height()));
    animation->setEasingCurve(QEasingCurve::OutInBounce);
    animation->start();
 }

 void MyPushButton::mousePressEvent(QMouseEvent* event)
 {
    if(path2!="")
     {
         QPixmap map(path2);
         int w=map.width();
         int h=map.height();
         setFixedSize(w,h);
         setIcon(map);
         setIconSize(QSize(w,h));
     }
    if(event->button()==Qt::LeftButton)
        animal(-10,-10);
    QPushButton::mousePressEvent(event);

 }

 void MyPushButton::mouseReleaseEvent(QMouseEvent*event)
 {
     if(path2!="")
     {
         QPixmap map(path1);
         int w=map.width();
         int h=map.height();
         setFixedSize(w,h);
         setIcon(map);
         setIconSize(QSize(w,h));
     }
     if(event->button()==Qt::LeftButton)
         animal(10,10);
     QPushButton::mouseReleaseEvent(event);
 }






 MyCoin::MyCoin(bool _state)
     :state(_state)
     ,num(0)
     ,win(false)
 {
     if(state)
     {
         setPath(":/image/Coin0001.png");
     }
     else
     {
         setPath(":/image/Coin0008.png");
     }
     connect(&timer,timer.timeout,[=](){
         num++;
         if(num==9)
         {
             num=0;
             timer.stop();
             state=1-state;
             return;
         }
         if(state)
         {
             QString path=QString(":/image/Coin000%1.png").arg(num);
             setPath(path);
         }
         else
         {
             setPath(QString(":/image/Coin000%1.png").arg(9-num));
         }
     });

 }


 void MyCoin::setPath(QString path)
 {
     QPixmap pix(path);
     setFixedSize(pix.width(),pix.height());
     setIcon(pix);
     setIconSize(pix.size());
     setStyleSheet("QPushButton{background:transparent}");
 }

void MyCoin::mousePressEvent(QMouseEvent*e)
{
    if(num!=0||win)
        return;
    QPushButton::mousePressEvent(e);
}




