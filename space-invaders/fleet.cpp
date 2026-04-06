#include "fleet.h"

Fleet::Fleet(BulletSystem* _bulletSystem) : bulletSystem(_bulletSystem), QObject(nullptr)
{
    width = columns * alienWidth + (columns - 1) * spacing;
    height = rows * alienHeight + (rows - 1) * spacing;

    alienImage = QPixmap(":/images/example");

    // Initialize aliens
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            aliens.push_back(Alien {
                QPoint(i * (alienWidth + spacing), j * (alienHeight + spacing)),
                true
            });
        }
    }
}


void Fleet::Update()
{
    // Move Aliens
    if(delayCount >= moveDelay)
    {
        // Move Aliens
        float newX = position.rx() + fleetDirection * (alienWidth + spacing);
        if(newX > width + alienWidth || newX < 0)
        {
            fleetDirection *= -1;
            position.setY(position.ry() + alienHeight + spacing);
        }
        else
        {
            position.setX(newX);
        }

        if(AnyAlive())
        {
            // Spawn Bullets
            if(bulletCount >= bulletDelay)
            {
                int alienIndex = rand() % aliens.size();

                while(!aliens[alienIndex].alive) {
                    alienIndex++;
                    if(alienIndex >= aliens.size())
                    {
                        alienIndex = 0;
                    }
                }

                bulletSystem->CreateBullet(aliens[alienIndex].position + position, false);
                bulletCount = 0;
            }
            else
            {
                bulletCount++;
            }
        }

        delayCount = 0;
    }
    else
    {
        delayCount++;
    }

    for(auto bullet_it = bulletSystem->BulletsBegin(); bullet_it != bulletSystem->BulletsEnd(); bullet_it++)
    {
        BulletSystem::Bullet bullet = *bullet_it;

        // Only player bullets
        if(!bullet.player) continue;

        for(auto aliens_it = AliensBegin(); aliens_it != AliensEnd(); aliens_it++)
        {
            Alien alien = *aliens_it;

            // Skip if dead
            if(!alien.alive) continue;

            // Check for collision
            int dx = abs(bullet.position.rx() - (position.rx() + alien.position.rx()));
            int dy = abs(bullet.position.ry() - (position.ry() + alien.position.ry()));

            if(
                dx < (alienWidth + bulletSystem->GetBulletWidth()) &&
                dy < (alienHeight + bulletSystem->GetBulletHeight())
            )
            {
                // Collision, destroy alien and bullet
                aliens_it->alive = false;
                bulletSystem->DeleteBullet(bullet.id);
                emit AlienDestroyed();
                if(!AnyAlive())
                {
                    emit FleetDestroyed();
                }
            }
        }
    }
}


void Fleet::Draw(QPainter* painter)
{
    for(auto it = AliensBegin(); it != AliensEnd(); it++)
    {
        if(!it->alive) continue;

        QPoint pos = it->position;
        QRect rect = QRect(
            position.rx() + pos.rx(),
            position.ry() + pos.ry(),
            alienWidth,
            alienHeight
        );
        painter->drawPixmap(rect, alienImage);
    }
}


void Fleet::Spawn()
{
    position = QPoint(0, 0);
    for(auto it = AliensBegin(); it != AliensEnd(); it++)
    {
        it->alive = true;
    }

    delayCount = 0;
    bulletCount = 0;
}


void Fleet::Clear()
{
    for(auto it = AliensBegin(); it != AliensEnd(); it++)
    {
        it->alive = false;
    }

    moveDelay = MOVE_DELAY_DEFAULT;
    bulletDelay = BULLET_DELAY_DEFAULT;
}


bool Fleet::AnyAlive()
{
    for(auto it = AliensBegin(); it != AliensEnd(); it++)
    {
        if(it->alive) return true;
    }

    return false;
}


void Fleet::NewLevel()
{
    if(bulletDelay > 0) bulletDelay--;
    if(moveDelay > 0) moveDelay--;
}


QVector<Fleet::Alien>::iterator Fleet::AliensBegin()
{
    return aliens.begin();
}

QVector<Fleet::Alien>::iterator Fleet::AliensEnd()
{
    return aliens.end();
}

int Fleet::GetRows()
{
    return rows;
}

int Fleet::GetColumns()
{
    return columns;
}

float Fleet::GetWidth()
{
    return width;
}

float Fleet::GetHeight()
{
    return height;
}

float Fleet::GetAlienHeight()
{
    return alienHeight;
}

float Fleet::GetAlienWidth()
{
    return alienWidth;
}

QPoint Fleet::GetPosition()
{
    return position;
}
