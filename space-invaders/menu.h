#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QStackedWidget* _w, QWidget *parent = nullptr);

signals:

private slots:
    void StartGame();

private:
    QStackedWidget* w;
};

#endif // MENU_H
