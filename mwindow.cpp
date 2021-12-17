#include "mwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>

MWindow::MWindow(unsigned w, unsigned h, unsigned t, float r, QWidget *parent) : QWidget(parent)
{
    // New objects deleted by Qt as this is destroyed.
    Grid *grid = new Grid(h, w, this);
    // Magic epsilon
    if (r > 0.000001) {
        grid->setRandomState(r);
    }
    QWidget *buttonRow = new QWidget(this);
    QPushButton *stepButton = new QPushButton("step", this);
    QPushButton *startButton = new QPushButton("Start", this);
    QPushButton * exitButton = new QPushButton("Exit", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonRow);

    QObject::connect(stepButton, &QPushButton::clicked, grid, &Grid::step);
    QObject::connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    timer = std::make_unique<StepTimer>(startButton, grid, std::chrono::milliseconds(t));

    buttonLayout->addWidget(stepButton);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(exitButton);
    mainLayout->addWidget(grid);
    mainLayout->addWidget(buttonRow);

    setLayout(mainLayout);
}
