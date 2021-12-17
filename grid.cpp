#include "grid.h"
#include <QGridLayout>
#include <QDebug>

const int CELL_SIZE=20;
const int CELL_PADDING = 2;

Grid::Grid(size_t m, size_t n, QWidget *parent) : QWidget(parent), row_size(m), column_size(n)
{
    layout = new QGridLayout(this);
    cells.resize(row_size, std::vector<Cell*>(column_size));

    for (size_t i = 0; i < row_size; ++i) {
        for (size_t j = 0; j < column_size; ++j) {
            //Note: Qt handles delete of QObjects, which Cell inherits. Otherwise would use smart pointer here.
            cells[i][j]= new Cell(i, j, this);
            layout->addWidget(cells[i][j], i,j);
        }
    }
    setFixedSize((CELL_SIZE+CELL_PADDING)*column_size, (CELL_SIZE+CELL_PADDING)*row_size);
    setCellSize();
}

void Grid::setCellSize()
{
    for (auto &row : cells) {
        for (auto cell : row) {
            cell->setFixedSize(CELL_SIZE, CELL_SIZE);
        }
    }
}

// Step one step forward in the game of life
void Grid::step()
{
    checkAllCellNeighbours();
    updateCells();
}

void Grid::checkAllCellNeighbours() const
{
    for (const auto &row : cells) {
        checkCellRowNeighbours(row);
    }
}

void Grid::checkCellRowNeighbours(const std::vector<Cell*>& row) const
{
    for (const auto &cell : row) {
        cell->calculateState(cells);
    }
}

void Grid::updateCells()
{
    for (auto &row : cells) {
        for (auto &cell : row) {
            cell->update();
        }
    }
}


