#include "grid.h"
#include <QGridLayout>
#include <QDebug>
#include <chrono>
#include <random>

const int CELL_SIZE=10;
const int CELL_PADDING = 2;

Grid::Grid(size_t m, size_t n, bool notify, QWidget *parent) : QWidget(parent), rowCount(m), columnCount(n)
{
    layout = new QGridLayout(this);
    cells.resize(rowCount, std::vector<Cell*>(columnCount));

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            //Note: Qt handles delete of QWidgets, which Cell inherits. Otherwise would use smart pointers.
            cells[i][j]= new Cell(i, j, notify, &cells, this);
            layout->addWidget(cells[i][j], i,j);
        }
    }
    setFixedSize((CELL_SIZE+CELL_PADDING)*columnCount, (CELL_SIZE+CELL_PADDING)*rowCount);
    setCellSize();
}

void Grid::setCellSize()
{
    for (const auto &row : cells) {
        for (const auto cell : row) {
            cell->setFixedSize(CELL_SIZE, CELL_SIZE);
        }
    }
}

// Step one step forward in the game of life
void Grid::step()
{
    auto t1 = std::chrono::high_resolution_clock::now();

    for (auto &row : cells) {
        for (const auto cell : row) {
            cell->checkIfShouldChange();
        }
    }
    for (const auto &row : cells) {
        for (const auto cell : row) {
            cell->update();
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    qDebug() << "Elaped time for single move is" << elapsed.count() << "microseconds";
}

void Grid::setRandomState(float pAlive)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution bernoulliDist(pAlive);

    for (auto &row : cells) {
        for (auto &cell : row) {
            if (bernoulliDist(gen)) {
                cell->setAlive();
            }
        }
    }
}


