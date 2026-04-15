#include "bulletsystem.h"

BulletSystem::BulletSystem(float _screenWidth, float _screenHeight) : screenWidth(_screenWidth), screenHeight(_screenHeight)
{
    bulletImage = QPixmap(":/images/bullet.png");
}


void BulletSystem::Update()
{
    // Delete bullets
    for(int i = 0; i < toDelete.size(); i++)
    {
        int id = toDelete[i];
        for(int i = 0; i < bullets.size(); i++)
        {
            if(bullets[i].id == id)
            {
                bullets.remove(i);
                break;
            }
        }
    }

    toDelete.clear();

    for(int i = 0; i < bullets.size(); i++)
    {
        Bullet bullet = bullets[i];
        QPoint pos = bullet.position;
        if(bullet.player)
        {
            bullets[i].position.setY(bullet.position.ry() - playerBulletVelocity);
        }
        else
        {
            bullets[i].position.setY(bullet.position.ry() + alienBulletVelocity);
        }

        if(pos.ry() < 0 || pos.ry() > screenHeight)
        {
            DeleteBullet(bullet.id);
        }
    }
}


void BulletSystem::Draw(QPainter* painter)
{
    for(auto it = bullets.begin(); it != bullets.end(); it++)
    {
        Bullet bullet = *it;
        QRect rect = QRect(
            bullet.position.rx() - bulletWidth/2,
            bullet.position.ry() - bulletHeight/2,
            bulletWidth,
            bulletHeight
        );
        painter->drawPixmap(rect, bulletImage);
    }
}


void BulletSystem::Resize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}


void BulletSystem::CreateBullet(QPoint position, bool player)
{
    bullets.push_back(Bullet {
        nextId,
        position,
        player
    });

    nextId++;
}


void BulletSystem::DeleteBullet(int id)
{
    toDelete.push_back(id);
}


QVector<BulletSystem::Bullet>::iterator BulletSystem::BulletsBegin()
{
    return bullets.begin();
}


QVector<BulletSystem::Bullet>::iterator BulletSystem::BulletsEnd()
{
    return bullets.end();
}


int BulletSystem::GetBulletHeight()
{
    return bulletHeight;
}


int BulletSystem::GetBulletWidth()
{
    return bulletWidth;
}
