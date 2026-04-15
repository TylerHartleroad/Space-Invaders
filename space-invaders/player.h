#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPoint>
#include <QRandomGenerator>
#include "bulletsystem.h"
#include "powerupsystem.h"

#define SHOOT_DELAY 10
#define POWER_UP_LENGTH (30 * 5)

class Player : public QObject
{
    Q_OBJECT

public:
    Player(BulletSystem* _bulletSystem, PowerUpSystem* _powerUp, int _screenWidth, int _screenHeight);
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
    void PowerUp();

    enum Power {
        MOVEMENT,
        SHOOT,
        LIFE,
        NONE
    };

    BulletSystem* bulletSystem;
    PowerUpSystem* powerUp;
    QPoint position;
    int screenWidth;
    int screenHeight;
    int playerWidth = 35;
    int playerHeight = 35;
    int edgeSpacing = 20;
    int lives = 3;
    int speed = 8;
    QPixmap playerImage;
    int shootDelayCount = 0;
    Power currentPowerUp = NONE;
    int powerCountDown = 0;
};

#endif // PLAYER_H
