#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "bulletsystem.h"
#include "fleet.h"
#include "player.h"

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = nullptr);
    void StartGame();
    void StopGame();
    bool IsRunning();

signals:
    void PlayerLeft();
    void PlayerRight();
    void PlayerShoot();

private slots:
    void ScoreAdded();
    void NewLevel();
    void LivesChanged(int newLives);

protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void GameLoop();

private:
    QTimer* timer;
    bool gameRunning = false;

    // Components
    BulletSystem bulletSystem;
    Player player;
    Fleet fleet;

    // Keys
    bool leftDown = false;
    bool rightDown = false;

    // Images
    QPixmap enemy;

    int score = 0;
    int level = 1;
    int lives = 3;

    int alienScore = 100;

};

#endif // DISPLAY_H
