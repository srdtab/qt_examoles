#include "pathfindingalgorithm.h"

PathfindingAlgorithm::PathfindingAlgorithm(QObject *parent) : QObject(parent)
{

}

Content Square::content() const
{
    return content_;
}

void Square::setContent(const Content &content)
{
    content_ = content;
}

Coordinates Square::coordinates() const
{
    return coordinates_;
}

void Square::setCoordinates(const Coordinates &coordinates)
{
    coordinates_ = coordinates;
}
