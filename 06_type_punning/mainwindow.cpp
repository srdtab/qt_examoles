#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

S_PDCM MainWindow::punPDCM(const QVector<int> &SDs)
{
    S_PDCM pdcm;
    //Пока работаю дома и не имею доступа к ПИЛВ
    //считаю, что:
    //сд 0-3   - Х  (double)
    //сд 4-7   - Y  (double)
    //сд 8-11  - Z  (double)
    //сд 12-13 - VХ (float)
    //сд 14-15 - VY (float)
    //сд 16-17 - VZ (float)

    //Могём подавать на вход punX SDs[i] потому что локальность у QVector такая же, как у "голого" исконно-посконного
    //массива (соседние элементы в соседних ячейках памяти). С QList такое уже не прокатит

    pdcm.X = punDouble(&SDs[0]); //Координаты - double'ы по IEEE 754 (64 бита, 4 слова МКО)
    pdcm.Y = punDouble(&SDs[4]);
    pdcm.Z = punDouble(&SDs[8]);
    pdcm.VX = punFloat(&SDs[12]);//Скорости - float'ы по IEEE 745 (32 бита, 2 слова МКО)
    pdcm.VY = punFloat(&SDs[14]);
    pdcm.VZ = punFloat(&SDs[16]);

    return pdcm;
}

double MainWindow::punDouble(const int *beginning)
{
    quint16 memory[4]{ //Обратный порядок потому что у нас Little Endian
        static_cast<quint16>(beginning[3]),
                static_cast<quint16>(beginning[2]),
                static_cast<quint16>(beginning[1]),
                static_cast<quint16>(beginning[0]),
    };
    return *reinterpret_cast<double*>(memory);
}

float MainWindow::punFloat(const int *beginning)
{
    quint16 memory[2]{ //Обратный порядок потому что у нас Little Endian
                static_cast<quint16>(beginning[1]),
                static_cast<quint16>(beginning[0]),
    };
    return *reinterpret_cast<float*>(memory);
}


void MainWindow::on_pushButton_clicked()
{

    SD.clear();
    for(int i = 0; i< 30; i++){
        SD << qrand()%0x10000;
    }
    qDebug()<<"Сгенерировали массив:";
    qDebug()<<SD;
    QString message;
    for(int i = 0; i< 30; i++){
        message.append(QString::number((int)SD[i],16).rightJustified(4,'0')).append(", ");
    }
    qDebug()<<message.chopped(2);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(SD.length()!=30){
        qDebug()<<"Сначала нужно сгенерировать СД!";
        return;
    }
    auto pdcm = punPDCM(SD);

        qDebug()<<pdcm.X<<pdcm.Y<<pdcm.Z<<pdcm.VX<<pdcm.VY<<pdcm.VZ;

        qDebug()
                <<QString::number(*reinterpret_cast<quint64*>(&pdcm.X),16)
                <<QString::number(*reinterpret_cast<quint64*>(&pdcm.Y),16)
                <<QString::number(*reinterpret_cast<quint64*>(&pdcm.Z),16)
                <<QString::number(*reinterpret_cast<quint32*>(&pdcm.VX),16)
                <<QString::number(*reinterpret_cast<quint32*>(&pdcm.VY),16)
                <<QString::number(*reinterpret_cast<quint32*>(&pdcm.VZ),16);

}

//
void MainWindow::on_pushButton_3_clicked()
{
    uint16_t x = 0x0001;
    qDebug()<<QString("%1-endian").arg(*((uint8_t *) &x) ? "little" : "big");
}
