#include "game.h"

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    auto display = new Display();

    auto layout = new QVBoxLayout();
    layout->addWidget(display);
    setLayout(layout);
}
