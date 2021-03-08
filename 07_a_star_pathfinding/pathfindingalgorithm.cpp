#include "pathfindingalgorithm.h"

Square::Square(PathfindingAlgorithm* algorithm, const Coordinates& coordinates, Content content)
    : algorithm_(algorithm), coordinates_(coordinates), content_(content)
{

}

const QVector<Coordinates> &Square::adjacent()
{
   if(!adjacentWasChecked_)
       findAdjacent_();
   adjacentWasChecked_ = true;
   return adjacent_;
}

void Square::findAdjacent_(){
    for (int x = coordinates_.x - 1; x <= coordinates_.x + 1; ++x)
        for(int y = coordinates_.y - 1; y <= coordinates_.y + 1; ++y){
            if(x == coordinates_.x && y == coordinates_.y)
                continue;
            if(checkAdjacency_(x,y))
                adjacent_.push_back(Coordinates(x,y));
        }
}

bool Square::checkAdjacency_(int x, int y)
{
   if(x - coordinates_.x > 1
           || x - coordinates_.x < -1
           || y - coordinates_.y > 1
           || y - coordinates_.y < -1
           || x < 0
           || y < 0
           || x > algorithm_->xSize_
           || y > algorithm_->ySize_)
       return false;
   if(algorithm_->square(x,y)->content() == Square::Nonpassable)
       return false;
   return true;
}
PathfindingAlgorithm::PathfindingAlgorithm(int xSize, int ySize, QObject *parent)
    : QObject(parent), xSize_(xSize), ySize_(ySize)
{
    squares_.resize(xSize_);
    for(auto& line : squares_)
        line.resize(ySize_);

    for(int x = 0; x < xSize_; ++x)
        for(int y = 0; y < ySize_; ++y){
            Square* square = new Square(this,Coordinates(x,y));
            square->setCoordinates(Coordinates(x, y));
            squares_[x][y] = square;
        }
}

PathfindingAlgorithm::~PathfindingAlgorithm(){
    for(int x = 0; x < xSize_; ++x)
        for(int y = 0; y < ySize_; ++y){
            delete squares_[x][y];
        }
}

void PathfindingAlgorithm::doWork(Coordinates start)
{
    auto adjacent = square(start)->adjacent();
    emit coordinatesFound(adjacent);
}
