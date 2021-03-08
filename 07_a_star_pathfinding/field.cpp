#include "field.h"
Field::Field(int width, int height, qreal squareSize, QObject *parent)
    : QObject(parent), height_(height), width_(width), squareSize_(squareSize)
{
    pheight_ = height_ * squareSize_;
    pwidth_ = width_ * squareSize_;
    scene_ = new QGraphicsScene(0.0,0.0,pwidth_,pheight_,this);
    filter_ = new FieldMouseFilter(squareSize, width_, height_, this);
    scene_->installEventFilter(filter_);
    connect(filter_,&FieldMouseFilter::squareClicked,this,&Field::onSquareClicked);
    squares_.resize(height_);
    for (auto & square : squares_){
        square.resize(width_);
    }
}

Field::~Field()
{
   for(auto& line  : squares_)
       for(QGraphicsRectItem* square : line)
           delete square;
}

void Field::paintSquare(const Coordinates &coordinates, const QBrush &brush)
{
    if (!checkCoordinate_(coordinates))
       return;
   squares_[coordinates.y][coordinates.x]->setBrush(brush);
   paintedSquares_.push_back(squares_[coordinates.y][coordinates.x]);
}

void Field::clearSquares()
{
   for(auto& square : paintedSquares_)
       square->setBrush(Qt::white);
   paintedSquares_.clear();
}

void Field::draw()
{
    drawLines_();
}

void Field::drawLines_()
{
    if(!lines_)
        lines_ = scene_->createItemGroup(QList<QGraphicsItem*>());
    else
        return;

    //Рисуем горизонтальные линии
    for(int h = 0; h <= height_; ++h)
        lines_->addToGroup(
                    scene_->addLine(0,h*squareSize_,pwidth_,h*squareSize_));

    //Рисуем вертикальные линии
    for(int w = 0; w <= width_; ++w)
        lines_->addToGroup(
                    scene_->addLine(w*squareSize_,0,w*squareSize_,pheight_));

   //Рисуем квадратики
   for (int h = 0; h < height_; ++h)
       for (int w = 0; w < width_; ++w)
           squares_[h][w] = scene_->addRect(w * squareSize_ + 2, h * squareSize_ + 2,
                                            squareSize_ - 4, squareSize_ - 4, QPen(Qt::red));
}

bool Field::checkCoordinate_(const Coordinates &coordinate) const
{
        if(coordinate.x >= width_
                || coordinate.y >= height_
                || coordinate.x < 0
                || coordinate.y < 0)
            return false;
        else
            return true;
}

void Field::onSquareClicked(Coordinates coordinate)
{
    clearSquares();
    paintSquare(coordinate, Qt::red);
}

FieldMouseFilter::FieldMouseFilter(int squareSize, int fieldWidth, int fieldHeight, QObject *parent)
    : QObject(parent), squareSize_(squareSize), fieldWidth_(fieldWidth), fieldHeight_(fieldHeight)
{

}

bool FieldMouseFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress){
        const QGraphicsSceneMouseEvent* const me = static_cast<const QGraphicsSceneMouseEvent*>(event);
        const QPointF position = me->scenePos();
        Coordinates clicked;
        //qDebug() << "click" << position;
        clicked.x = static_cast<int>(position.x()/squareSize_);
        clicked.y= static_cast<int>(position.y()/squareSize_);
        qDebug() << clicked.x << clicked.y;
        emit squareClicked(clicked);
        return true;
    }
    else {
        // Стандартная обработка событий
        return QObject::eventFilter(obj, event);
    }
}
