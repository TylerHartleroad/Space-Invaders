#ifndef BONUSALIEN_H
#define BONUSALIEN_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include "bulletsystem.h"
#include "powerupsystem.h"

#define BONUS_SPAWN_DELAY (30 * 20)
#define PADDING 20

class BonusAlien : public QObject
{
public:
    BonusAlien(BulletSystem* _bulletSystem, PowerUpSystem* _powerUp);
    void Update();
    void Draw(QPainter* painter);
    void SetScreenWidth(int width);

private:
    void Spawn();

    BulletSystem* bulletSystem;
    PowerUpSystem* powerUp;
    bool spawned;
    int screenWidth = 100;
    QPoint position = QPoint(0, 0);
    int bonusDelayCount = 0;
    float alienWidth = 75;
    float alienHeight = 35;
    QPixmap alienImage;
    int speed = 10;
};

#endif // BONUSALIEN_H
