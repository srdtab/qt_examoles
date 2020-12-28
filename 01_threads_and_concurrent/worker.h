#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QElapsedTimer>
#include <QThread>
#include <QApplication>
#include <QDebug>
#include <cmath>

/**
 * @brief The Worker class - класс со специальными медленными функциями-болванками для работы в отдельном треде
 */
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public slots:
    //! \brief doSomeWork - Прогоняет заданное число итераций цикла, каждая по 300 мсек.
    //! На каждой итерации испускает сигнал с процентом готовности.
    //! \param displayString - Просто строка для отображения, чтобы показать, как передавать строку.
    //! \param iterations - Число циклов.
    //! \return Фактически прошедшее время в мсек.
    quint64 doSomeWork(const QString& displayString, const int& iterations);

    quint64 lastElapsed(){return lastElapsed_;}

signals:
    //! \brief progress - Сигнал о текущем прогрессе выполнения задачи
    //! \param percent - Значение прогресса в процентах
    void progress(int percent);

    //! \brief message - Сигнал с сообщением о работе класса.
    //! \param text - Текст сообщения.
    void message(QString text);

signals:

private:
    quint64 lastElapsed_{0};

};

#endif // WORKER_H
