#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qtablewidget=new QTableWidget(50,10,this);    //创建gui表单
    qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setCentralWidget(qtablewidget);             //使表单适应窗口
    threadmanager=new ThreadManager();          //初始化类
    qtablewidget->resizeRowsToContents();
    this->grabKeyboard();
    resize(1050,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()const
{
    qtablewidget->clearContents();//清空原表格
    PCB *cur=new PCB();

    //根据队列绘制表格
    for(int i=0;i<50;i++){
        int col=0;
        cur=threadmanager->adj[i].next;
        while(cur!=nullptr){
            qtablewidget->setItem(i,col++,new QTableWidgetItem(QString::number(cur->pid)));
            cur=cur->next;
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F)){
        if(threadmanager->newThread()){
            update();
        }
    }else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_A)){
        threadmanager->runThread();
        update();
    }else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q)){
        exit(0);
    }
}

