#include "bunker.h"

Bunker::Bunker(BulletSystem* _bulletSystem, QPoint _position) :
    bulletSystem(_bulletSystem),
    position(_position)
{
    // Create Units
    for(int i = 0; i < BUNKER_WIDTH; i++)
    {
        for(int j = 0; j < BUNKER_HEIGHT; j++)
        {
            if(IndexFilter(i, j))
            {
                units.push_back(Unit {
                    QPoint(position.rx() + i * UNIT_SIZE, position.ry() + j * UNIT_SIZE),
                    false
                });
            }
        }
    }
}


void Bunker::Update()
{
    // Collide with bullets
    for(auto bullet_it = bulletSystem->BulletsBegin(); bullet_it != bulletSystem->BulletsEnd(); bullet_it++)
    {
        BulletSystem::Bullet bullet = *bullet_it;

        // Coarse check
        if(
            bullet.position.rx() > position.rx() &&
            bullet.position.rx() < position.rx() + GetWidth() &&
            bullet.position.ry() > position.ry() &&
            bullet.position.ry() < position.ry() + GetHeight()
        )
        {
            // Fine check
            for(auto unit_it = units.begin(); unit_it != units.end(); unit_it++)
            {
                if(unit_it->destroyed) continue;

                if(
                    bullet.position.rx() > unit_it->position.rx() &&
                    bullet.position.rx() < unit_it->position.rx() + UNIT_SIZE &&
                    bullet.position.ry() > unit_it->position.ry() &&
                    bullet.position.ry() < unit_it->position.ry() + UNIT_SIZE
                )
                {
                    bulletSystem->DeleteBullet(bullet.id);
                    if(!bullet.player) {
                        unit_it->destroyed = true;
                    }
                    break;
                }
            }
        }
    }
}


void Bunker::Draw(QPainter* painter)
{
    for(auto it = units.begin(); it != units.end(); it++)
    {
        if(!it->destroyed)
        {
            QRect rect = QRect(
                it->position.rx(),
                it->position.ry(),
                UNIT_SIZE,
                UNIT_SIZE
            );
            painter->fillRect(rect, Qt::green);
        }
    }
}


void Bunker::Spawn()
{
    for(int i = 0; i < units.size(); i++) {
        units[i].destroyed = false;
    }
}


int Bunker::GetWidth()
{
    return UNIT_SIZE * BUNKER_WIDTH;
}


int Bunker::GetHeight()
{
    return UNIT_SIZE * BUNKER_HEIGHT;
}

// Filter for bunker shape
bool Bunker::IndexFilter(int x, int y)
{
    return !(
        ((x == 0 || x == BUNKER_WIDTH-1) && y == 0) ||
        ((x > 1 && x < BUNKER_WIDTH-2) && y == BUNKER_HEIGHT-2) ||
        ((x > 0 && x < BUNKER_WIDTH-1) && y == BUNKER_HEIGHT-1)
    );
}
