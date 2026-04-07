#include "gameover.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

GameOver::GameOver(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    auto label = new QLabel("GAME OVER");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: white; font-size: 32px;");

    scoreLabel = new QLabel("Score: 0");
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("color: white; font-size: 20px;");

    levelLabel = new QLabel("Level: 1");
    levelLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setStyleSheet("color: white; font-size: 20px;");

    auto button = new QPushButton("Restart");
    auto quitButton = new QPushButton("Quit");

    button->setStyleSheet(
        "QPushButton {"
        "  color: white;"
        "  background-color: black;"
        "  border: 2px solid white;"
        "  padding: 10px;"
        "}"
        "QPushButton:hover {"
        "  background-color: white;"
        "  color: black;"
        "}"
        );

    quitButton->setStyleSheet(
        "QPushButton {"
        "  color: white;"
        "  background-color: black;"
        "  border: 2px solid white;"
        "  padding: 10px;"
        "}"
        "QPushButton:hover {"
        "  background-color: white;"
        "  color: black;"
        "}"
        );

    layout->addStretch();
    layout->addWidget(label);
    layout->addSpacing(10);
    layout->addWidget(scoreLabel);
    layout->addWidget(levelLabel);
    layout->addSpacing(20);
    layout->addWidget(button, 0, Qt::AlignCenter);
    layout->addWidget(quitButton, 0, Qt::AlignCenter);
    layout->addStretch();

    setStyleSheet("background-color: black;");

    connect(button, &QPushButton::clicked, this, &GameOver::RestartRequest);

    connect(quitButton, &QPushButton::clicked, this, &GameOver::QuitRequest);
}


void GameOver::SetScore(int score)
{
    scoreLabel->setText("Score: " + QString::number(score));
}


void GameOver::SetLevel(int level)
{
    levelLabel->setText("Level: " + QString::number(level));
}
