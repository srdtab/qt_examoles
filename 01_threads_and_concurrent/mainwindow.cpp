#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    ui->textBrowser->append(QString("Поток %1: Создали основную оконную форму.")
                 .arg((quint64)QThread::currentThreadId()));
    otherThread = new QThread(this);
    otherThread->start();

    otherThreadWorker = new Worker(nullptr);
    otherThreadWorker->moveToThread(otherThread);
    connect(otherThreadWorker,&Worker::message,ui->textBrowser,&QTextBrowser::append);
    connect(otherThreadWorker,&Worker::progress,ui->progressBar,&QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    future.cancel();
    otherThreadWorker->deleteLater();
    otherThread->quit();
    otherThread->wait();

    delete ui;

}


void MainWindow::on_concurrentButton_clicked()
{
    QFuture<quint64> elapsed = QtConcurrent::run(otherThreadWorker,&Worker::doSomeWork,someWord,iterations);
    while(!elapsed.isFinished()){
        QThread::currentThread()->msleep(100);
        QApplication::processEvents();
    }
}

void MainWindow::on_threadedButton_clicked()
{

}
