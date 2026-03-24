#include "menu.h"

Menu::Menu(QStackedWidget* _w, QWidget *parent)
    : w(_w), QWidget{parent}
{
    auto imgExample = new QLabel();
    QPixmap pix(":/images/example.png");
    imgExample->setPixmap(pix);
    auto startButton = new QPushButton("Start Game");

    auto layout = new QVBoxLayout();

    layout->addWidget(imgExample);
    layout->addWidget(startButton);

    QWidget::connect(startButton, &QPushButton::pressed, this, &Menu::StartGame);

    setLayout(layout);
}


void Menu::StartGame()
{
    w->setCurrentIndex(1);
}
