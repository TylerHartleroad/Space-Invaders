#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPoint>
#include "bulletsystem.h"

class Player : public QObject
{
    Q_OBJECT

public:
    Player(BulletSystem* _bulletSystem, int _screenWidth, int _screenHeight);
    void Update();
    void Draw(QPainter* painter);
    void Spawn();
    void Resize(int w, int h);

signals:
    void LivesUpdated(int lives);
    void PlayerHit();
    void PlayerDestroyed();

public slots:
    void MoveLeft();
    void MoveRight();
    void Shoot();

private:
    BulletSystem* bulletSystem;
    QPoint position;
    int screenWidth;
    int screenHeight;
    int playerWidth = 35;
    int playerHeight = 35;
    int edgeSpacing = 20;
    int lives = 3;
    int speed = 8;
    QPixmap playerImage;
};

#endif // PLAYER_H
