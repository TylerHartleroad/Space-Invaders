#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = new QVBoxLayout();
    ui->centralwidget->setLayout(layout);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setGameWidget(QWidget* game)
{
    if (!ui->gameWidget) return;

    auto layout = new QVBoxLayout(ui->gameWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(game);
}
