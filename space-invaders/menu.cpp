#include "menu.h"

Menu::Menu(QStackedWidget* _w, QWidget *parent)
    : w(_w), QWidget{parent}
{
    auto startButton = new QPushButton("Start Game");

    auto layout = new QVBoxLayout();

    layout->addWidget(startButton);

    QWidget::connect(startButton, &QPushButton::pressed, this, &Menu::StartGame);

    setLayout(layout);
}


void Menu::StartGame()
{
    w->setCurrentIndex(1);
}
