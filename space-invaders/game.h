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

signals:

};

#endif // GAME_H
