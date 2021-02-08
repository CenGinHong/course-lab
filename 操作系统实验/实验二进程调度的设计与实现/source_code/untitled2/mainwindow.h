#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadmanager.h"
#include <QTableWidget>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void update() const;      //更新表单内容
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableWidget *qtablewidget;
    ThreadManager *threadmanager;

protected:
    void keyPressEvent(QKeyEvent *event);   //键盘事件响应
};

#endif // MAINWINDOW_H
