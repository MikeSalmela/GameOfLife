#ifndef MWINDOW_H
#define MWINDOW_H

#include "grid.h"
#include "steptimer.h"

#include <QWidget>

#include <memory>


class MWindow : public QWidget
{
public:
    // \params width w and height h (wxh grid of cells), time t between autosteps, chance r of a cell
    // spawning in alive state, bool notify defines if the notify neighbour algorithm is in use.
    MWindow(unsigned w, unsigned h, unsigned t, float r, bool notify, QWidget *parent = nullptr);
private:
    std::unique_ptr<StepTimer> timer;
};

#endif // MWINDOW_H
