#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <coordinates.h>

class FieldMouseFilter : public QObject
{
    Q_OBJECT
public:
    FieldMouseFilter(int squareSize, int fieldWidth, int fieldHeight, QObject* parent = nullptr);
signals:
    //! Координаты клетки, на которую нажали
    void squareClicked(Coordinates  coordinates);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
     //! Размер клетки в пикселях
    int squareSize_;
    //! Ширина и высота поля (в клетках)
    int fieldWidth_;
    int fieldHeight_;

};

class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(int width,int height, qreal squareSize,  QObject *parent = nullptr);
    ~Field();

    //! Устангавливает график вью для отображения
    void setViev(QGraphicsView* view) {view_ = view; view_->setScene(scene_);}
    QGraphicsView* view() const {return view_;}

    //! Красит квадрат с координатой coordinates кистью brush
    void paintSquare(const Coordinates& coordinates, const QBrush& brush);
    //! Снимает окраску всех квадратов
    void clearSquares();

    //! Отрисовывает текущее состояние поля
    void draw();

public slots:
    void onSquareClicked(Coordinates coordinate);

private:
    //! Отрисовать линии на поле
    void drawLines_();
    QGraphicsItemGroup* lines_{nullptr};
    //QVector<QGraphicsLineItem*> lines_;

    //! Сцена и представление
    QGraphicsScene* scene_{nullptr};
    QGraphicsView* view_{nullptr};

    //! Матрица клеток.
    QVector<QVector<QGraphicsRectItem *> > squares_;
    //! Список указателей на клетки, которые в данный момент окрашены (чтобы не делать полный перебор)
    QVector<QGraphicsRectItem*> paintedSquares_;


    //! Высотав и ширина
    int height_;    //В клеточках
    int width_;
    qreal pheight_; //В пикселях
    qreal pwidth_;

    //! Размер клетки в пикселях
    qreal squareSize_{64};
    //! Проверяет допустимость координаты для данного поля. Возвращает true если координата допустима, иначе - false
    bool checkCoordinate_(const Coordinates& coordinate) const;

    //! Фильтр событий для того, чтобы определить, по какому квадрату кликнули
    FieldMouseFilter* filter_;


signals:

};

#endif // FIELD_H
