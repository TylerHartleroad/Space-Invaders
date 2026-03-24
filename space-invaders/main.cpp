#include "mainwindow.h"
#include "menu.h"
#include "game.h"
#include <QStackedWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStackedWidget* stackedWidget = new QStackedWidget();

    auto menu = new Menu(stackedWidget);
    auto game = new Game();

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(game);

    stackedWidget->setCurrentIndex(0);
    w.setCentralWidget(stackedWidget);

    w.show();
    return a.exec();
}
