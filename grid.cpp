#include "grid.h"
#include <QGridLayout>
#include <QDebug>

const int CELL_SIZE=10;
const int CELL_PADDING = 2;

Grid::Grid(size_t m, size_t n, QWidget *parent) : QWidget(parent), rowCount(m), columnCount(n)
{
    layout = new QGridLayout(this);
    cells.resize(rowCount, std::vector<Cell*>(columnCount));

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            //Note: Qt handles delete of QObjects, which Cell inherits. Otherwise would use smart pointer here.
            cells[i][j]= new Cell(i, j, &cells, this);
            layout->addWidget(cells[i][j], i,j);
        }
    }
    setFixedSize((CELL_SIZE+CELL_PADDING)*columnCount, (CELL_SIZE+CELL_PADDING)*rowCount);
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
    for (auto &row : cells) {
        for (auto &cell : row) {
            cell->checkIfShouldChange();
        }
    }
    for (auto &row : cells) {
        for (auto &cell : row) {
            cell->update();
        }
    }
}


