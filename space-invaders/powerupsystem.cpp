#include "powerupsystem.h"

PowerUpSystem::PowerUpSystem()
{
    image = QPixmap(":/images/example.png");
}


void PowerUpSystem::Update()
{
    if(spawned)
    {
        position.setY(position.ry() + speed);
        if(position.ry() > screenHeight + size)
        {
            spawned = false;
        }
    }
}


void PowerUpSystem::Draw(QPainter* painter)
{
    if(spawned)
    {
        QRect rect = QRect(
            position.rx(),
            position.ry(),
            size,
            size
        );

        painter->drawPixmap(rect, image);
    }
}


void PowerUpSystem::Spawn(QPoint pos)
{
    position = pos;
    spawned = true;
}


void PowerUpSystem::SetScreenHeight(int h)
{
    screenHeight = h;
}


void PowerUpSystem::Despawn()
{
    spawned = false;
}


bool PowerUpSystem::IsSpawned()
{
    return spawned;
}


int PowerUpSystem::GetSize()
{
    return size;
}