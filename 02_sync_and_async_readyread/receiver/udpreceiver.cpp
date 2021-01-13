#include "udpreceiver.h"
#include "./ui_udpreceiver.h"

UdpReceiver::UdpReceiver(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UdpReceiver)
{
    ui->setupUi(this);
    sct = new QUdpSocket(this);
    quint16 port = 7755;
    if(sct->bind(QHostAddress::LocalHost, port))
        ui->textBrowser->append(QString("Слушаем на порт %1").arg(port));
    else
        ui->textBrowser->append("Не удалось создать слушающий сокет");

    auto btns = this->findChildren<QRadioButton*>();
    for(auto btn : btns)
        connect(btn, &QPushButton::toggled, this, &UdpReceiver::on_radioButtonToggled);



    connect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead,Qt::AutoConnection);
}

UdpReceiver::~UdpReceiver()
{
    delete ui;
}


void UdpReceiver::on_pushButton_clicked()
{
    auto randomID = qrand();
    qDebug()<<Q_FUNC_INFO<<"ID:"<<randomID<<"Thread"<<QThread::currentThreadId()<<"- начато выполнение";

    if(sct->waitForReadyRead(10000)){
        qDebug()<<"Дождались!";
    }
    else {
        qDebug()<<"Не дождались";
    }
    qDebug()<<Q_FUNC_INFO<<"ID:"<<randomID<<"Thread"<<QThread::currentThreadId()<<"- завершено выполнение";
}

void UdpReceiver::SlotReadyRead()
{
    auto randomID = qrand();
    qDebug()<<Q_FUNC_INFO<<"ID:"<<randomID<<"Thread"<<QThread::currentThreadId()<<"- начато выполнение";
    sct->receiveDatagram();
    qDebug()<<Q_FUNC_INFO<<"ID:"<<randomID<<"Thread"<<QThread::currentThreadId()<<"- завершено выполнение";
}

void UdpReceiver::on_radioButtonToggled(bool checked)
{
    if(!checked)
        return;

    disconnect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead);

    auto btn = qobject_cast<QRadioButton*>(sender());
    if(btn->objectName()==QString("radioButton_DirectConnection")){
        ui->textBrowser->append(QString("Установили тип соеддинения Qt::DirectConnection"));
        connect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead,Qt::DirectConnection);
    }
    if(btn->objectName()==QString("radioButton_QueuedConnection")){
        ui->textBrowser->append(QString("Установили тип соеддинения Qt::QueuedConnection"));
        connect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead,Qt::QueuedConnection);
    }
    if(btn->objectName()==QString("radioButton_BlockingQueuedConnection")){
        ui->textBrowser->append(QString("Установили тип соеддинения Qt::BlockingQueuedConnection"));
        connect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead,Qt::BlockingQueuedConnection);
    }
    if(btn->objectName()==QString("radioButton_AutoConnection")){
        ui->textBrowser->append(QString("Установили тип соеддинения Qt::AutoConnection"));
        connect(sct, &QUdpSocket::readyRead, this, &UdpReceiver::SlotReadyRead,Qt::AutoConnection);
    }
}
