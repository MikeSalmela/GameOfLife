#ifndef MWINDOW_H
#define MWINDOW_H
#include "grid.h"
#include "steptimer.h"
#include <QWidget>
#include <memory>


class MWindow : public QWidget
{
public:
    MWindow(unsigned w, unsigned h, unsigned t, float r, QWidget *parent = nullptr);
private:
    std::unique_ptr<StepTimer> timer;
};

#endif // MWINDOW_H
