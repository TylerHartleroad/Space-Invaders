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
    QObject::connect(&fleet, &Fleet::AlienDestroyed, this, &Display::ScoreAdded);
    QObject::connect(&fleet, &Fleet::FleetDestroyed, this, &Display::NewLevel);
    QObject::connect(&player, &Player::LivesUpdated, this, &Display::LivesChanged);
    QObject::connect(&player, &Player::PlayerDestroyed, this, &Display::PlayerDestroyed);

    setFocusPolicy(Qt::StrongFocus);
    score = 0;
    level = 1;
    lives = 3;

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

    // Draw score, level, lives
    painter.setPen(Qt::white);
    QFont font("Courier", 12, QFont::Bold);
    painter.setFont(font);

    painter.drawText(10, 20, "Score: " + QString::number(score));
    painter.drawText(width() - 100, 20, "Level: " + QString::number(level));
    painter.drawText(width() - 100, height() - 10, "Lives: " + QString::number(lives));

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


void Display::ScoreAdded()
{
    score += alienScore;
}


void Display::NewLevel()
{
    level++;
    fleet.Spawn();
}


void Display::LivesChanged(int newLives)
{
    lives = newLives;
}


int Display::GetScore()
{
    return score;
}


int Display::GetLevel()
{
    return level;
}

