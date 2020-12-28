#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QtGlobal>
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void workRequest(QString str, int iterations);

private slots:
    void on_concurrentButton_clicked();

    void on_threadedButton_clicked();

    void on_naiveCallButton_clicked();

    void on_future_ready();

private:
    Ui::MainWindow *ui;

    QThread* otherThread;
    const int iterations{30};
    const QString someWord{"Многопоточность"};
    Worker* otherThreadWorker;
    Worker* thisThreadWorker;

    //Будущий результат вычислений от QtConcurrent::run
    //НЕ ЗАБЫТЬ ОТМЕНИТЬ В ЗАКРЫТИИ ОКНА, ЧТОБЫ ТРЕД НЕ БЕЖАЛ
    QFuture<quint64> future;
    QFutureWatcher<quint64> watcher;
};
#endif // MAINWINDOW_H
