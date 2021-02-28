#include "field.h"
Field::Field(int height, int width, qreal squareSize, QObject *parent)
    : height_(height), width_(width), squareSize_(squareSize), QObject(parent)
{
    setSquareSize(squareSize_);
    scene_ = new QGraphicsScene(0.0,0.0,pheight_,pwidth_,this);
    filter_ = new FieldMouseFilter(this);
    scene_->installEventFilter(filter_);
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
}

qreal Field::squareSize() const
{
    return squareSize_;
}

void Field::setSquareSize(const qreal &squareSize)
{
    squareSize_ = squareSize;
    pheight_ = height_ * squareSize_;
    pwidth_ = width_ * squareSize_;
}



FieldMouseFilter::FieldMouseFilter(QObject *parent) : QObject(parent)
{

}

bool FieldMouseFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress){
        const QGraphicsSceneMouseEvent* const me = static_cast<const QGraphicsSceneMouseEvent*>(event);
                   const QPointF position = me->scenePos();
        qDebug() << "click" << position;
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
