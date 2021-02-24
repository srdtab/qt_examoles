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
    int length = SDs.length();
    quint16 mkoWords[length];
    for(int i = 0; i < length; i++){
        mkoWords[i] = static_cast<quint16>(SDs[i]);
    }

    for(int i = 0; i < length; i++){
        qDebug()<<"~"<<i<<mkoWords[i];
    }

    //Пока работаю дома и не имею доступа к ПИЛВ
    //считаю, что:
    //сд 0-3   - Х  (double)
    //сд 4-7   - Y  (double)
    //сд 8-11  - Z  (double)
    //сд 12-13 - VХ (float)
    //сд 14-15 - VY (float)
    //сд 16-17 - VZ (float)

    pdcm.Y = *(reinterpret_cast<double* >(&mkoWords[0]));  //Координаты - double'ы по IEEE 754 (64 бита, 4 слова МКО)
    pdcm.Y = *(reinterpret_cast<double* >(&mkoWords[4]));
    pdcm.Z = *(reinterpret_cast<double* >(&mkoWords[8]));
    pdcm.VX = *(reinterpret_cast<float* >(&mkoWords[12])); //Скорости - float'ы по IEEE 745 (32 бита, 2 слова МКО)
    pdcm.VY = *(reinterpret_cast<float* >(&mkoWords[14]));
    pdcm.VZ = *(reinterpret_cast<float* >(&mkoWords[16]));

    qDebug()<<pdcm.X<<pdcm.Y<<pdcm.Z<<pdcm.VX<<pdcm.VY<<pdcm.VZ;

    return pdcm;
}


void MainWindow::on_pushButton_clicked()
{

    SD.clear();
    for(int i = 0; i< 30; i++){
        SD << qrand()%0x10000;
    }
    qDebug()<<"Сгенерировали массив:";
    qDebug()<<SD;
    for(int i = 0; i< 30; i++){
        qDebug()<<i<<QString::number((int)SD[i],2).rightJustified(16,'0');
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    auto pdcm = punPDCM(SD);
    qDebug()<<"После преобразования получили:";
    qDebug()<<pdcm.X<<pdcm.Y<<pdcm.Z<<pdcm.VX<<pdcm.VY<<pdcm.VZ;
}

void MainWindow::on_pushButton_3_clicked()
{
    uint16_t x = 0x0001;
    qDebug()<<QString("%1-endian").arg(*((uint8_t *) &x) ? "little" : "big");
}
