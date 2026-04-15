#include "player.h"

Player::Player(BulletSystem* _bulletSystem, PowerUpSystem* _powerUp, int _screenWidth, int _screenHeight) :
    bulletSystem(_bulletSystem),
    powerUp(_powerUp),
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

    // Shoot cooldown
    if(shootDelayCount > 0) shootDelayCount--;

    // Power up
    if(powerUp->IsSpawned())
    {
        if(
            powerUp->position.rx() + powerUp->GetSize() > position.rx() &&
            powerUp->position.ry() + powerUp->GetSize() > position.ry() &&
            powerUp->position.rx() < position.rx() + playerWidth &&
            powerUp->position.ry() < position.ry() + playerHeight
        )
        {
            powerUp->Despawn();
            PowerUp();
        }
    }

    if(powerCountDown > 0)
    {
        powerCountDown--;
    }
    else
    {
        currentPowerUp = NONE;
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
    int moveSpeed = speed;
    if(currentPowerUp == MOVEMENT) moveSpeed *= 2;
    position.setX(position.rx() - moveSpeed);
}


void Player::MoveRight()
{
    if(lives == 0) return;
    int moveSpeed = speed;
    if(currentPowerUp == MOVEMENT) moveSpeed *= 2;
    position.setX(position.rx() + moveSpeed);
}


void Player::Shoot()
{
    // Can't shoot if dead
    if(lives == 0) return;

    // Wait for delay
    if(shootDelayCount > 0 && currentPowerUp != SHOOT) return;

    shootDelayCount = SHOOT_DELAY;

    // Spawn bullet
    QPoint bulletPos = QPoint(
        position.rx() + playerWidth/2,
        position.ry()
    );
    bulletSystem->CreateBullet(bulletPos, true);
}


void Player::PowerUp()
{
    int index = QRandomGenerator::global()->bounded(static_cast<int>(3));
    currentPowerUp = static_cast<Power>(index);

    if(currentPowerUp == LIFE)
    {
        lives++;
        emit LivesUpdated(lives);
        currentPowerUp = NONE;
    }
    else
    {
        powerCountDown = POWER_UP_LENGTH;
    }
}