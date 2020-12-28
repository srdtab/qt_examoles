#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

}

quint64 Worker::doSomeWork(const QString &displayString, const int &iterations)
{
    QElapsedTimer tmr;
    tmr.start();

    emit message(QString("Поток %1: начато выполнение работы.")
                 .arg((quint64)QThread::currentThreadId()));

    for(int i = 1; i <= iterations; ++i){
        QThread::currentThread()->msleep(300);
        QApplication::processEvents();
        int prgrs = 100.0*float(i)/float(iterations);
        emit progress(prgrs);
    }

    return tmr.elapsed();
}
