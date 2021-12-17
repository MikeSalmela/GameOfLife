#include "mainwindow.h"
#include "grid.h"
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
{

    QWidget *window = new QWidget;
    Grid *g = new Grid(25, 25, this);
    QWidget *buttonRow = new QWidget(parent);

    QVBoxLayout *main_layout = new QVBoxLayout(window);

    QHBoxLayout *button_l = new QHBoxLayout(buttonRow);

    QPushButton *stepButton = new QPushButton("test", this);
    QPushButton *startButton = new QPushButton("start", this);

    button_l->addWidget(stepButton);
    button_l->addWidget(startButton);

    main_layout->addWidget(g);
    main_layout->addWidget(buttonRow);
    main_layout->addLayout(button_l);

    window->setLayout(main_layout);
    window->show();
}

MainWindow::~MainWindow()
{
}


