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

};

#endif // DISPLAY_H
