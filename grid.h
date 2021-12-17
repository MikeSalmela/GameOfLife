#ifndef GRID_H
#define GRID_H

#include <QDebug>
#include <QGridLayout>
#include <QVector>
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
    explicit Grid(size_t m, size_t n, QWidget *parent = nullptr);
    void step();

private:
    //Cell size
    size_t row_size;
    size_t column_size;

    std::vector<std::vector<Cell*>> cells;

    QGridLayout *layout;

    void checkAllCellNeighbours() const;
    void checkCellRowNeighbours(const std::vector<Cell *> &row) const;
    void updateCells();
    void setCellSize();

};

#endif // GRID_H
