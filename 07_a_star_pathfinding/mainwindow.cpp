#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    field_ = new Field(40,45,15,this);
    field_->setViev(ui->graphicsView);
    algorithm_ = new PathfindingAlgorithm(40,45,this);
    on_pushButton_clicked();
    connect(field_,&Field::squareClicked,algorithm_,&PathfindingAlgorithm::doWork);
    connect(algorithm_,&PathfindingAlgorithm::coordinatesFound,field_,&Field::paintSquares);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    field_->draw();
}
