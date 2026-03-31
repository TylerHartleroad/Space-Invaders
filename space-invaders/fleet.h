#ifndef FLEET_H
#define FLEET_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QVector>
#include <QPainter>
#include"bulletsystem.h"

class Fleet : public QObject
{
    Q_OBJECT

public:
    struct Alien {
        QPoint position;
        bool alive;
    };

    explicit Fleet(BulletSystem* _bulletSystem);
    void Update();
    void Draw(QPainter* painter);
    void Spawn();
    void Clear();
    QVector<Alien>::iterator AliensBegin();
    QVector<Alien>::iterator AliensEnd();
    int GetRows();
    int GetColumns();
    float GetWidth();
    float GetHeight();
    float GetAlienWidth();
    float GetAlienHeight();
    QPoint GetPosition();
    bool AnyAlive();

signals:
    void AlienDestroyed();
    void FleetDestroyed();

private:
    // Aliens
    QVector<Alien> aliens;
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

    // Components
    BulletSystem* bulletSystem;

    // Images
    QPixmap alienImage;
};

#endif // FLEET_H
