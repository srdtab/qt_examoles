#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>

class Square : public QObject
{
    Q_OBJECT
public:
    explicit Square(QObject *parent = nullptr);

signals:

};

#endif // SQUARE_H
