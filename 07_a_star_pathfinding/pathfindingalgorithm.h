#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <QObject>
#include "coordinates.h"

class Square{
public:
    Square();
    ~Square();
    enum Content{
       Passable = 0,
       Nonpassable = 1
    };

    Content content() const { return content_; }
    void setContent(const Content &content) { content_ = content; }

    Coordinates coordinates() const { return coordinates_; }
    void setCoordinates(const Coordinates &coordinates) { coordinates_ = coordinates; }

private:
    Content content_;
    QVector<Square*> adjacent_;
    Coordinates coordinates_;
};

class PathfindingAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit PathfindingAlgorithm(QObject *parent = nullptr);

signals:

};

#endif // PATHFINDINGALGORITHM_H
