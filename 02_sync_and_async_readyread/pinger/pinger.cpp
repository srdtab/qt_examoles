#include "pinger.h"
#include "./ui_pinger.h"

Pinger::Pinger(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pinger)
{
    ui->setupUi(this);
    loic = new QUdpSocket(this);
    loic->bind(QHostAddress::LocalHost, 7890);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pinger::ping);
}

Pinger::~Pinger()
{
    delete ui;
}

bool Pinger::addressIsValid(const QString &hostAndPort, QHostAddress& address, quint16& port)
{
    auto lst = hostAndPort.split(':');
    if (lst.length()!=2)
        return false;
    address = QHostAddress(lst[0]);
    if(address.isNull())
        return false;

    bool convertedCorrectly = true;
    uint port_i = lst[1].toUInt(&convertedCorrectly,10);
    if(!convertedCorrectly)
        return false;
    if(port_i < 1 || port_i > 65535)
        return false;
    port = (quint16)port_i;
    return true;
}

void Pinger::on_pushButton_clicked()
{
    if(timer->isActive()){
        timer->stop();
        ui->pushButton->setText("Периодическая отправка");
    } else {
        timer->start(ui->spinBox->value());
        ui->pushButton->setText("Стоп");
    }
}

void Pinger::on_spinBox_valueChanged(int arg1)
{
    if (timer->isActive()){
        timer->stop();
        timer->start(arg1);
    }
}

void Pinger::ping()
{
    QString addr_and_port = ui->lineEdit->text();
    QHostAddress addr;
    quint16 port{0};
    if(!addressIsValid(addr_and_port,addr,port)){
        ui->textBrowser->append("Ошибка! некорректный адрес");
        return;
    }
    else {
        loic->writeDatagram(QByteArray("Hello, World!"),addr,port);
        ui->textBrowser->append(
                    QString("Отправили сообщение на %1").arg(addr_and_port));
    }
}



void Pinger::on_pushButton_2_clicked()
{
    ping();
}
