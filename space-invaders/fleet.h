#ifndef FLEET_H
#define FLEET_H

#include <QPoint>
#include <QRect>
#include <QVector>

class Fleet
{
public:
    Fleet();
    void Update();
    void Spawn();
    void Clear();
    QVector<QPoint>::iterator AliensBegin();
    QVector<QPoint>::iterator AliensEnd();
    int GetRows();
    int GetColumns();
    float GetWidth();
    float GetHeight();
    float GetAlienWidth();
    float GetAlienHeight();
    QPoint GetPosition();

private:
    QVector<QPoint> aliens;
    QPoint position;
    int rows = 5;
    int columns = 11;
    float alienWidth = 35;
    float alienHeight = 35;
    float spacing = 10;
    float width;
    float height;
    int moveDelay = 15;
    int delayCount = 0;
    int fleetDirection = 1;
};

#endif // FLEET_H
