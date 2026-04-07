#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QLabel>

class QPushButton;

class GameOver: public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    void SetScore(int score);
    void SetLevel(int level);

signals:
    void RestartRequest();
    void QuitRequest();

private:
    QLabel *scoreLabel = nullptr;
    QLabel *levelLabel = nullptr;
};

#endif // GAMEOVER_H
