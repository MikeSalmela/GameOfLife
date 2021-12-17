#include "steptimer.h"

StepTimer::StepTimer(QPushButton *button, Grid *grid, std::chrono::milliseconds ms) : button(button), grid(grid), ms(ms)
{
    connect(button, &QPushButton::clicked, this, &StepTimer::onButtonClicked);
    connect(&timer, &QTimer::timeout, this, &StepTimer::onTime);
}


void StepTimer::onButtonClicked()
{
    if (running) {
        button->setText("Stop");
        timer.start(ms);
    } else {
        button->setText("Start");
        timer.stop();
    }
    running = !running;
}

void StepTimer::onTime()
{
    grid->step();
}
