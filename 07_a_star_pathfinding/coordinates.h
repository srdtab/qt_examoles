#ifndef COORDINATES_H
#define COORDINATES_H
#include <QObject>

struct Coordinates{
    Coordinates(int x = 0, int y = 0);
    Coordinates(const Coordinates& other);
    int x{0};
    int y{0};
};
Q_DECLARE_METATYPE(Coordinates);

#endif // COORDINATES_H
