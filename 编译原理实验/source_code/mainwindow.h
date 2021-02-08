#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "QTextStream"
#include "QDebug"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QString MainWindow::showFileDialog();

    void on_openFile_triggered();

    void on_saveFile_triggered();

    void on_prase_triggered();

    void on_printTree_triggered();

    void on_newFIle_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
