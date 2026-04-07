#include "mainwindow.h"
#include "menu.h"
#include "game.h"
#include "gameover.h"
#include <QStackedWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStackedWidget* stackedWidget = new QStackedWidget();

    auto menu = new Menu(stackedWidget);
    auto game = new Game();
    auto layout = new QVBoxLayout();
    auto gameOver = new GameOver();

    auto connectGameOverSignal = [&]() {
        QObject::connect(game, &Game::PlayerDestroyed, stackedWidget, [stackedWidget, gameOver]() {
            Game *currentGame = qobject_cast<Game*>(stackedWidget->widget(1));
            if (!currentGame) return;

            gameOver->SetScore(currentGame->GetScore());
            gameOver->SetLevel(currentGame->GetLevel());
            stackedWidget->setCurrentIndex(2);
        });
    };

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(game);
    layout->addWidget(stackedWidget);

    stackedWidget->setCurrentIndex(0);
    w.setCentralWidget(stackedWidget);
    stackedWidget->addWidget(gameOver);

    connectGameOverSignal();

    QObject::connect(gameOver, &GameOver::QuitRequest, [&]() {
        QApplication::quit();
    });

    QObject::connect(game, &Game::PlayerDestroyed, stackedWidget, [stackedWidget, gameOver, game]() {
        gameOver->SetScore(game->GetScore());
        gameOver->SetLevel(game->GetLevel());
        stackedWidget->setCurrentIndex(2);
    });

    QObject::connect(gameOver, &GameOver::RestartRequest, [&]() {

        QWidget *oldGame = stackedWidget->widget(1);
        Game *newGame = new Game();

        stackedWidget->removeWidget(oldGame);
        stackedWidget->insertWidget(1, newGame);

        delete oldGame;

        game = newGame;
        connectGameOverSignal();

        stackedWidget->setCurrentIndex(1);
    });

    w.show();
    return a.exec();
}
