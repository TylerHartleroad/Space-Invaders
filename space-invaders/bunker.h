#ifndef BUNKER_H
#define BUNKER_H

#include <QPoint>
#include <QVector>
#include <QPainter>
#include "bulletsystem.h"

#define UNIT_SIZE 10
#define BUNKER_WIDTH 7
#define BUNKER_HEIGHT 7

class Bunker
{
public:
    Bunker(BulletSystem* _bulletSystem, QPoint _position);
    void Update();
    void Draw(QPainter* painter);
    void Spawn();

    static int GetWidth();
    static int GetHeight();

private:
    BulletSystem* bulletSystem;

    struct Unit {
        QPoint position;
        bool destroyed;
    };

    QVector<Unit> units;

    QPoint position;

    bool IndexFilter(int x, int y);
};

#endif // BUNKER_H
