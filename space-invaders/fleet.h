#ifndef FLEET_H
#define FLEET_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QVector>
#include <QPainter>
#include"bulletsystem.h"

#define MOVE_DELAY_DEFAULT 15
#define BULLET_DELAY_DEFAULT 3

class Fleet : public QObject
{
    Q_OBJECT

public:
    struct Alien {
        QPoint position;
        bool alive;
        int imageIndex;
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
    void NewLevel();

signals:
    void AlienDestroyed();
    void FleetDestroyed();

private:
    // Aliens
    QVector<Alien> aliens;
    QPoint position = QPoint(0, 0);
    int rows = 5;
    int columns = 11;
    float alienWidth = 35;
    float alienHeight = 35;
    float spacing = 10;
    float width;
    float height;
    int fleetDirection = 1;

    // Relative Difficulty
    int moveDelay = MOVE_DELAY_DEFAULT;
    int delayCount = 0;
    int bulletDelay = BULLET_DELAY_DEFAULT;
    int bulletCount = 0;

    // Components
    BulletSystem* bulletSystem;

    // Images
    QVector<QPixmap> alienImages;
};

#endif // FLEET_H
