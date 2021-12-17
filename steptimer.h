#ifndef STEPTIMER_H
#define STEPTIMER_H

#include <QObject>
#include <QTimer>
#include <QPushButton>
#include "grid.h"

/*
 * \class StepTimer
 * \brief Steps the game forward with interval defined in milliseconds
 */

class StepTimer : public QObject
{
    Q_OBJECT
public:
    explicit StepTimer(QPushButton *button, Grid* grid, std::chrono::milliseconds ms);

public slots:
    void onButtonClicked();

private:
    bool running {false};
    QPushButton *button;
    Grid *grid;
    QTimer timer;
    std::chrono::milliseconds ms;

    void onTime();
};

#endif // STEPTIMER_H
