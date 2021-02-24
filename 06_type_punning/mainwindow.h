#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct S_PDCM{
    double X{0};
    double Y{0};
    double Z{0};
    float VX{0};
    float VY{0};
    float VZ{0};
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static S_PDCM punPDCM(const QVector<int>& SDs);
    static double punDouble(const int* beginning);
    static float punFloat(const int* beginning);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> SD; //В таком же формате, в котором возвращает библиотека МКО
};
#endif // MAINWINDOW_H
