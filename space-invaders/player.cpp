#include "player.h"

Player::Player(BulletSystem* _bulletSystem, int _screenWidth, int _screenHeight) :
    bulletSystem(_bulletSystem),
    screenWidth(_screenWidth),
    screenHeight(_screenHeight)
{
    playerImage = QPixmap(":/images/player.png");

    Spawn();
}


void Player::Update()
{
    if(lives > 0)
    {
        for(auto it = bulletSystem->BulletsBegin(); it != bulletSystem->BulletsEnd(); it++)
        {
            if(it->player) continue;

            if(
                it->position.rx() > position.rx() &&
                it->position.rx() < position.rx() + playerWidth &&
                it->position.ry() > position.ry() &&
                it->position.ry() < position.ry() + playerHeight
            )
            {
                lives--;
                emit LivesUpdated(lives);
                emit PlayerHit();
                if(lives <= 0)
                {
                    emit PlayerDestroyed();
                }

                bulletSystem->DeleteBullet(it->id);
            }
        }
    }
}


void Player::Draw(QPainter* painter)
{
    if(lives == 0) return;

    QRect rect = QRect(
        position.rx(),
        position.ry(),
        playerWidth,
        playerHeight
    );

    painter->drawPixmap(rect, playerImage);
}


void Player::Spawn()
{
    lives = 3;

    position = QPoint(
        edgeSpacing,
        screenHeight - edgeSpacing - playerHeight
    );
}


void Player::Resize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    Spawn();
}


void Player::MoveLeft()
{
    if(lives == 0) return;
    position.setX(position.rx() - speed);
}


void Player::MoveRight()
{
    if(lives == 0) return;
    position.setX(position.rx() + speed);
}


void Player::Shoot()
{
    if(lives == 0) return;
    QPoint bulletPos = QPoint(
        position.rx() + playerWidth/2,
        position.ry()
    );
    bulletSystem->CreateBullet(bulletPos, true);
}
