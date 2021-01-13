#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QWidget>
#include <QUdpSocket>
#include <QDebug>
#include <QThread>
#include <QNetworkDatagram>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class UdpReceiver; }
QT_END_NAMESPACE

class UdpReceiver : public QWidget
{
    Q_OBJECT

public:
    UdpReceiver(QWidget *parent = nullptr);
    ~UdpReceiver();

private slots:
    void on_pushButton_clicked();
    void SlotReadyRead();
    void on_radioButtonToggled(bool checked);

private:
    Ui::UdpReceiver *ui;
    QUdpSocket* sct;
};
#endif // UDPRECEIVER_H
