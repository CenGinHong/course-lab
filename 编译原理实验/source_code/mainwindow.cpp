#include "mainwindow.h"
#include "ui_mainwindow.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

extern __declspec(dllexport) void getSyntaxTree(char* sourceFileFullName, char* savedFileFullName);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_triggered()
{
    QFile file(showFileDialog());
    if(file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QString TNYcode = QString(file.readAll());
        ui->textEdit->setPlainText(TNYcode);

    }else{
        QMessageBox::warning(this,tr("error"),tr("Open File filed"));
    }
    file.close();
}


//该函数存在于自定义主窗口类里
QString MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("open a file."),
        "D:/",
        tr("Tiny Source Files(*.tny);;All files(*.*)"));
   return fileName;
}

void MainWindow::on_saveFile_triggered()
{
    QFileDialog fileDialog;

    if(ui->textEdit->toPlainText() == "")
    {
        return;
    }
    QString codeSavePath = fileDialog.getSaveFileName(this,tr("Save File"),"DEMO",tr("tny Source File(*.tny)"));
    QFile filename(codeSavePath);
    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QMessageBox::warning(this,tr("tip"),tr("Save File Successfully"),QMessageBox::Ok);
        QTextStream textStream(&filename);
        textStream<<ui->textEdit->toPlainText();
    }

}

void MainWindow::on_prase_triggered()
{
    QFileDialog fileDialog;
    QString codeSavePath = fileDialog.getSaveFileName(this,
                                             tr("Save File"),
                                             "DEMO",
                                             tr("tny Source File(*.tny)"));

    QFile filename(codeSavePath);
    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("error"),tr("Open File filed"),QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream textStream(&filename);
        QString str = ui->textEdit->toPlainText();
        textStream<<str;
    }
    filename.close();

    //当前工程所在目录
    QString SyntaxTreeSavePath = QCoreApplication::applicationDirPath() + "SyntaxTree.txt";
    qDebug()<<(SyntaxTreeSavePath);

    //参数需要转换类型
    getSyntaxTree(codeSavePath.toLatin1().data(),SyntaxTreeSavePath.toLatin1().data());
    if (Error){
        QMessageBox::warning(this,tr("error"),tr("Pass Parsing Filed"),QMessageBox::Ok);
    }else{
        QMessageBox::warning(this,tr("tip"),tr("Pass Parsing Sussessfully"),QMessageBox::Ok);
    }
        QFile::remove(SyntaxTreeSavePath);

}

void MainWindow::on_printTree_triggered()
{
    QFileDialog fileDialog;
    QString codeSavePath = fileDialog.getSaveFileName(this,tr("Save File"),"DEMO",tr("tny Source File(*.tny)"));
    QFile filename(codeSavePath);
    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("error"),tr("Save File filed"),QMessageBox::Ok);
        return;
    }
    else
    {
        QMessageBox::warning(this,tr("tip"),tr("Save File Successfully"),QMessageBox::Ok);
        QTextStream textStream(&filename);
        textStream<<ui->textEdit->toPlainText();
        filename.close();

        QString SyntaxTreeSavePath = QFileDialog::getSaveFileName(this,tr("SyntaxTree Save As"),"/SyntaxTree",tr("Text File(*.txt)"));

        //生成语法树
        getSyntaxTree(codeSavePath.toLatin1().data(),SyntaxTreeSavePath.toLatin1().data());

        //显示语法树
        QFile SyntaxTree(SyntaxTreeSavePath);
        if (SyntaxTree.open(QIODevice::ReadWrite | QIODevice::Text)){
            ui->textEdit->setPlainText(SyntaxTree.readAll());
        }else{
            QMessageBox::warning(this,tr("tip"),tr("Save File Successfully"),QMessageBox::Ok);
        }
    }

}

void MainWindow::on_newFIle_triggered()
{
    QFileDialog fileDialog;

    if(ui->textEdit->toPlainText() == "")
    {
        return;
    }else{
        QString codeSavePath = fileDialog.getSaveFileName(this,tr("Save File"),"DEMO",tr("tny Source File(*.tny)"));
        QFile filename(codeSavePath);
        if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        else
        {
            //保存文件内容
            QMessageBox::warning(this,tr("tip"),tr("Save File Successfully"),QMessageBox::Ok);
            QTextStream textStream(&filename);
            textStream<<ui->textEdit->toPlainText();

        }
    }
    ui->textEdit->clear();
}

void getSyntaxTree(char* sourceFileFullName, char* savedFileFullName)
{
    TreeNode * syntaxTree;

    source = fopen(sourceFileFullName, "r");

    if (source == NULL)
    {
        fprintf(stderr, "File %s not found\n", sourceFileFullName);
        exit(1);
    }

    listing = fopen(savedFileFullName, "w");
    fprintf(listing, "TINY COMPILATION: %s\n\n", sourceFileFullName);

    // 进行重置
    linepos = 0;  /* current position in LineBuf */
    bufsize = 0;  /* current size of buffer string */
    EOF_flag = 0; /* corrects ungetNextChar behavior on EOF */

    syntaxTree = parse();

    fprintf(listing, "Syntax tree:\n\n");
    printTree(syntaxTree);
    printf("%d", Error);

    fclose(source);
    fclose(listing);
}
