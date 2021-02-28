#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <square.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class FieldMouseFilter : public QObject
{
    Q_OBJECT
public:
    FieldMouseFilter(QObject* parent = nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(int height, int width, qreal squareSize,  QObject *parent = nullptr);

    //! Устангавливает график вью для отображения
    void setViev(QGraphicsView* view) {view_ = view; view_->setScene(scene_);}
    QGraphicsView* view() const {return view_;}

    //! Отрисовывает текущее состояние поля
    void draw();

    //! Возвращает размер клетки в пикселях
    qreal squareSize() const;
    //! Устанавливает размер клетки в пикселях
    void setSquareSize(const qreal &squareSize);

private:
    //! Отрисовать линии на поле
    void drawLines_();
    QGraphicsItemGroup* lines_{nullptr};
    //QVector<QGraphicsLineItem*> lines_;

    //! Сцена и представление
    QGraphicsScene* scene_{nullptr};
    QGraphicsView* view_{nullptr};

    //! Размер клетки в пикселях
    qreal squareSize_{64};
    //! Высотав и ширина
    int height_;    //В клеточках
    int width_;
    qreal pheight_; //В пикселях
    qreal pwidth_;

    FieldMouseFilter* filter_;


signals:

};

#endif // FIELD_H
