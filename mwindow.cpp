#include "mwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>

MWindow::MWindow(unsigned w, unsigned h, unsigned t, QWidget *parent) : QWidget(parent)
{
    // New objects deleted by Qt as this is destroyed.
    Grid *grid = new Grid(h, w, this);
    QWidget *buttonRow = new QWidget(this);
    QPushButton *stepButton = new QPushButton("step", this);
    QPushButton *startButton = new QPushButton("Start", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonRow);

    QObject::connect(stepButton, &QPushButton::clicked, grid, &Grid::step);
    timer = std::make_unique<StepTimer>(startButton, grid, std::chrono::milliseconds(t));

    buttonLayout->addWidget(stepButton);
    buttonLayout->addWidget(startButton);
    mainLayout->addWidget(grid);
    mainLayout->addWidget(buttonRow);

    setLayout(mainLayout);
}
