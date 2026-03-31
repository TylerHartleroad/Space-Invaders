#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include "fleet.h"

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = nullptr);
    void StartGame();
    void StopGame();
    bool IsRunning();

signals:
    void scoreChanged(int newScore);
    void levelChanged(int newLevel);
    void livesChanged(int newLives);

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void GameLoop();

private:
    QTimer* timer;
    bool gameRunning = false;

    // Components
    Fleet fleet;

    // Images
    QPixmap enemy;

    int score = 0;
    int level = 1;
    int lives = 3;

};

#endif // DISPLAY_H
