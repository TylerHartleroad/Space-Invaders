#include "game.h"

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    display = new Display();

    connect(display, &Display::PlayerDestroyed, this, &Game::PlayerDestroyed);
    auto layout = new QVBoxLayout();
    layout->addWidget(display);
    setLayout(layout);
}


int Game::GetScore()
{
    if (!display)
    {
        return 0;
    }

    return display->GetScore();
}


int Game::GetLevel()
{
    if (!display)
    {
        return 1;
    }

    return display->GetLevel();
}
