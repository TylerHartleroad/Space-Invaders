#include "bonusalien.h"

BonusAlien::BonusAlien(BulletSystem* _bulletSystem, PowerUpSystem* _powerUp) :
    bulletSystem(_bulletSystem),
    powerUp(_powerUp)
{
    alienImage = QPixmap(":/images/bonus_alien.png");
}


void BonusAlien::Update()
{
    if(spawned)
    {
        // Move alien
        position.setX(position.rx() - speed);
        if(position.rx() < -alienWidth)
        {
            spawned = false;
        }

        // Collide with bullets
        for(auto b = bulletSystem->BulletsBegin(); b != bulletSystem->BulletsEnd(); b++)
        {
            if(!b->player) continue;

            if(
                b->position.rx() > position.rx() &&
                b->position.ry() > position.ry() &&
                b->position.rx() < position.rx() + alienWidth &&
                b->position.ry() < position.ry() + alienHeight
            )
            {
                spawned = false;
                bulletSystem->DeleteBullet(b->id);
                powerUp->Spawn(position);
            }
        }
    }
    else
    {
        // Wait for spawn
        if(bonusDelayCount >= BONUS_SPAWN_DELAY)
        {
            bonusDelayCount = 0;
            Spawn();
        }
        else
        {
            bonusDelayCount++;
        }
    }
}

void BonusAlien::Draw(QPainter* painter)
{
    if(spawned)
    {
        QRect rect = QRect(
            position.rx(),
            position.ry(),
            alienWidth,
            alienHeight
        );
        painter->drawPixmap(rect, alienImage);
    }
}


void BonusAlien::SetScreenWidth(int width)
{
    screenWidth = width;
}


void BonusAlien::Spawn()
{
    position = QPoint(screenWidth - PADDING, PADDING);
    spawned = true;
}
