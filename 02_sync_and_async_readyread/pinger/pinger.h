#ifndef PINGER_H
#define PINGER_H

#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Pinger; }
QT_END_NAMESPACE

class Pinger : public QWidget
{
    Q_OBJECT

public:
    Pinger(QWidget *parent = nullptr);
    ~Pinger();

    static bool addressIsValid(const QString &hostAndPort, QHostAddress& address, quint16& port);

private slots:
    void on_pushButton_clicked();

    void ping();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Pinger *ui;

    QUdpSocket* loic;

    QTimer* timer;
};
#endif // PINGER_H
