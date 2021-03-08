#include "coordinates.h"


Coordinates::Coordinates(int x, int y) : x(x), y(y)
{

}

Coordinates::Coordinates(const Coordinates &other)
{
    x = other.x;
    y = other.y;
}
