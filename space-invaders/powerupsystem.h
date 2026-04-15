#ifndef POWERUPSYSTEM_H
#define POWERUPSYSTEM_H

#include <QPainter>

class PowerUpSystem
{
public:
    PowerUpSystem();
    void Update();
    void Draw(QPainter* painter);
    void Spawn(QPoint pos);
    void Despawn();
    void SetScreenHeight(int h);
    bool IsSpawned();
    int GetSize();

    QPoint position = QPoint(0, 0);

private:
    bool spawned = false;
    int speed = 10;
    int size = 25;
    int screenHeight = 100;
    QPixmap image;
};

#endif // POWERUPSYSTEM_H
