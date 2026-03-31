#ifndef BULLETSYSTEM_H
#define BULLETSYSTEM_H

#include <QVector>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class BulletSystem
{
public:
    struct Bullet {
        int id;
        QPoint position;
        bool player;
    };

    BulletSystem(float _screenWidth, float _screenHeight);
    void Update();
    void Draw(QPainter* painter);
    void CreateBullet(QPoint position, bool player);
    void DeleteBullet(int id);
    QVector<Bullet>::iterator BulletsBegin();
    QVector<Bullet>::iterator BulletsEnd();
    int GetBulletHeight();
    int GetBulletWidth();



private:
    QVector<Bullet> bullets;
    QVector<int> toDelete;
    int nextId = 0;
    QPixmap bulletImage;
    float screenWidth;
    float screenHeight;
    float bulletWidth = 3;
    float bulletHeight = 10;
    float bulletVelocity = 6;
};

#endif // BULLETSYSTEM_H
