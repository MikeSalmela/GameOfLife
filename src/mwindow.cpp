#include "../include/mwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>

MWindow::MWindow(unsigned w, unsigned h, unsigned t, float r, bool notify, QWidget *parent) : QWidget(parent)
{
    // New objects deleted by Qt as this is destroyed.
    Grid *grid = new Grid(h, w, notify, this);
    // Magic epsilon
    if (r > 0.000001) {
        grid->setRandomState(r);
    }
    QPushButton *stepButton = new QPushButton("step", this);
    QPushButton *startButton = new QPushButton("Start", this);
    QPushButton *exitButton = new QPushButton("Exit", this);

    QGridLayout *mainLayout = new QGridLayout(this);

    QObject::connect(stepButton, &QPushButton::clicked, grid, &Grid::step);
    QObject::connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    timer = std::make_unique<StepTimer>(startButton, grid, std::chrono::milliseconds(t));

    mainLayout->addWidget(grid, 0, 0, 1, 3, Qt::AlignHCenter);
    mainLayout->addWidget(stepButton, 1, 0);
    mainLayout->addWidget(startButton, 1 ,1);
    mainLayout->addWidget(exitButton, 1 ,2);

    setLayout(mainLayout);
}
