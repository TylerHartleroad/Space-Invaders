#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include "display.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    int GetScore();
    int GetLevel();

signals:
    void PlayerDestroyed();

private:
    Display *display = nullptr;
    int n_score = 0;
    int n_level = 0;
    int n_lives = 0;

};

#endif // GAME_H
