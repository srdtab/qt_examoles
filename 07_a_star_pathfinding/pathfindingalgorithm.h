#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <QObject>
#include "coordinates.h"


class PathfindingAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit PathfindingAlgorithm(QObject *parent = nullptr);

signals:

};

#endif // PATHFINDINGALGORITHM_H
