#include "display.h"

Display::Display(QWidget *parent)
    : QWidget{parent},
    bulletSystem(width(), height()),
    player(&bulletSystem, width(), height()),
    fleet(&bulletSystem)
{
    // Initialize timer
    timer = new QTimer();
    QWidget::connect(timer, &QTimer::timeout, this, &Display::GameLoop);

    // Resize
    setFixedSize(fleet.GetWidth()*2, fleet.GetHeight()*3);

    // Connect
    QObject::connect(this, &Display::PlayerLeft, &player, &Player::MoveLeft);
    QObject::connect(this, &Display::PlayerRight, &player, &Player::MoveRight);
    QObject::connect(this, &Display::PlayerShoot, &player, &Player::Shoot);

    setFocusPolicy(Qt::StrongFocus);
    StartGame();
}


void Display::GameLoop()
{
    // Update Components
    bulletSystem.Update();
    player.Update();
    fleet.Update();

    update();
}


void Display::StartGame()
{
    if(gameRunning) return;

    // Initialize
    fleet.Spawn();

    timer->start(33);
}


void Display::StopGame()
{
    if(!gameRunning) return;

    fleet.Clear();

    timer->stop();
}


bool Display::IsRunning()
{
    return gameRunning;
}


void Display::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Background
    painter.fillRect(rect(), Qt::black);

    // Key Events
    if(leftDown) emit PlayerLeft();
    if(rightDown) emit PlayerRight();

    // Draw Components
    fleet.Draw(&painter);
    player.Draw(&painter);
    bulletSystem.Draw(&painter);

}


void Display::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left: leftDown = true; break;
    case Qt::Key_Right: rightDown = true; break;
    case Qt::Key_Space: if(!event->isAutoRepeat()) emit PlayerShoot(); break;
    }
}


void Display::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left: leftDown = false; break;
    case Qt::Key_Right: rightDown = false; break;
    }
}

