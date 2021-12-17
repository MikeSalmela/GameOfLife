#ifndef GRID_H
#define GRID_H

#include <QDebug>
#include <QGridLayout>
#include <QWidget>

#include <vector>

#include "cell.h"

/*
 * \class Grid
 * \brief Contains Cells and handles their layout.
 */
class Grid : public QWidget
{
    Q_OBJECT
public:
    // Create m*n grid
    explicit Grid(size_t m, size_t n, bool notify, QWidget *parent = nullptr);
    void step();

    void setRandomState(float pAlive);

private:
    //Cell count
    size_t rowCount;
    size_t columnCount;

    std::vector<std::vector<Cell*>> cells;

    QGridLayout *layout;
    void setCellSize();

};

#endif // GRID_H
