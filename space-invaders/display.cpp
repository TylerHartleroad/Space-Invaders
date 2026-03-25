#include "display.h"

Display::Display(QWidget *parent)
    : QWidget{parent}
{
    // Initialize timer
    timer = new QTimer();
    QWidget::connect(timer, &QTimer::timeout, this, &Display::GameLoop);

    // Create Components
    fleet = Fleet();

    // Load images
    enemy = QPixmap(":/images/example");

    // Resize
    setFixedSize(fleet.GetWidth()*2, fleet.GetHeight()*3);

    StartGame();
}


void Display::GameLoop()
{
    // Update Components
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

    // Draw fleet
    QPoint fleetPos = fleet.GetPosition();
    for(auto it = fleet.AliensBegin(); it != fleet.AliensEnd(); it++)
    {
        QPoint pos = *it;
        QRect rect = QRect(
            fleetPos.rx() + pos.rx(),
            fleetPos.ry() + pos.ry(),
            fleet.GetAlienWidth(),
            fleet.GetAlienHeight()
        );
        painter.drawPixmap(rect, enemy);
    }
}
