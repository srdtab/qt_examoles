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

    //Для отображения ответов от Worker-a
    connect(otherThreadWorker,&Worker::message,ui->textBrowser,&QTextBrowser::append);
    connect(otherThreadWorker,&Worker::progress,ui->progressBar,&QProgressBar::setValue);

    //Для обеспечения работы через классический QThread
    connect(this,&MainWindow::workRequest,otherThreadWorker,&Worker::doSomeWork,Qt::BlockingQueuedConnection);

    //Для отображения результатов выполнения Future
    connect(&watcher,&QFutureWatcher<quint64>::finished,this,&MainWindow::on_future_ready);
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
    future.cancel();
    future = QtConcurrent::run(otherThreadWorker,&Worker::doSomeWork,someWord,iterations);
    watcher.setFuture(future);
}

void MainWindow::on_threadedButton_clicked()
{
    emit workRequest(someWord, iterations);
    ui->textBrowser->append(QString("Threaded work done. Заняло %1 мс")
                            .arg(otherThreadWorker->lastElapsed()));

}

void MainWindow::on_naiveCallButton_clicked()
{
    otherThreadWorker->doSomeWork(someWord,iterations);
}

void MainWindow::on_future_ready()
{
    ui->textBrowser->append(QString("Future is now. Заняло %1 мс")
                            .arg(future.result()));
}
