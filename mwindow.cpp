#include "mwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>

MWindow::MWindow(unsigned w, unsigned h, unsigned t, QWidget *parent) : QWidget(parent)
{
    // New objects deleted by Qt as window is destroyed.
    Grid *g = new Grid(h, w, this);
    QWidget *buttonRow = new QWidget(this);
    QPushButton *stepButton = new QPushButton("step", this);
    QPushButton *startButton = new QPushButton("start", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonRow);

    QObject::connect(stepButton, &QPushButton::clicked, g, &Grid::step);
    timer = std::make_unique<StepTimer>(startButton, g, std::chrono::milliseconds(t));

    buttonLayout->addWidget(stepButton);
    buttonLayout->addWidget(startButton);
    mainLayout->addWidget(g);
    mainLayout->addWidget(buttonRow);

    setLayout(mainLayout);
}
