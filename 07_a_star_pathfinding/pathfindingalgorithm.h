#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <QObject>
#include <QVector>
#include "coordinates.h"

class PathfindingAlgorithm;

class Square{
public:

    //! Возможные виды контента, которыми может быть заполнена кнопка
    enum Content{
       Passable = 0,
       Nonpassable = 1
    };
    Square(PathfindingAlgorithm* algorithm, const Coordinates* coordinates, Content& content);
    ~Square();

    //! Чем заполнен квадрат
    Content content() const { return content_; }
    void setContent(const Content &content) { content_ = content; }

    //! Координаты квадрата
    Coordinates coordinates() const { return coordinates_; }
    void setCoordinates(const Coordinates &coordinates) { coordinates_ = coordinates; }

    //! Возвращает список всех соседних клеток
    const QVector<Coordinates>& adjacent();

private:
    PathfindingAlgorithm* algorithm_{nullptr}; //Алгоритм, к которому относится этот квадрат
    Content content_{Content::Passable}; //Что именно лежит в нашей клетке
    Coordinates coordinates_; //Координаты рассматриваемой клетки
    QVector<Coordinates> adjacent_; //Вектор координат соседей
    bool adjacentWasChecked_{false}; //Проводили ли уже поиск соседей (чтобы лишний раз не вычислять)
    void findAdjacent_(); //Формирует вектор соседей
};

class PathfindingAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit PathfindingAlgorithm(int xSize, int ySize, QObject *parent = nullptr);
    ~PathfindingAlgorithm();
private:
    int xSize_;//Ширина в клетках
    int ySize_;//Высота в клетках
    QVector<QVector<Square*> > squares_;
signals:

};

#endif // PATHFINDINGALGORITHM_H
