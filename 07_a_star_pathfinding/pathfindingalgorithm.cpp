#include "pathfindingalgorithm.h"

Square::Square(PathfindingAlgorithm* algorithm, const Coordinates* coordinates, Content& content)
    : algorithm_(algorithm), coordinates_(coordinates)
{

}

const QVector<Coordinates> &Square::adjacent()
{
   if(!adjacentWasChecked_)
       findAdjacent_();
}

void Square::findAdjacent_(){

}
PathfindingAlgorithm::PathfindingAlgorithm(int xSize, int ySize, QObject *parent)
    : QObject(parent), xSize_(xSize), ySize_(ySize)
{
    squares_.resize(xSize_);
    for(auto& line : squares_)
        line.resize(ySize_);

    for(int x = 0; x < xSize_; ++x)
        for(int y = 0; y < ySize_; ++y){
            Square* square = new Square;
            square->setCoordinates(Coordinates(x, y));
            squares_[x][y] = square;
        }
}

PathfindingAlgorithm::~PathfindingAlgorithm(){
    for(int x = 0; x < xSize_; ++x)
        for(int y = 0; y < ySize_; ++y){
            Square* square = new Square;
            square->setCoordinates(Coordinates(x, y));
            squares_[x][y] = square;
        }
}
