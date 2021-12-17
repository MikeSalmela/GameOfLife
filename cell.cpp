#include "cell.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <math.h>

Cell::Cell(unsigned i, unsigned j, QWidget *parent) :
    QWidget(parent), pos_i(i), pos_j(j)
{
}

void Cell::calculateState(const std::vector<std::vector<Cell*>> &cells)
{
    unsigned neighbours = countLiveNeighbors(cells);
    if (!isAlive() && neighbours == 3)
        shouldChange = true;
    else if (isAlive() && (neighbours <= 1 || neighbours >=4))
        shouldChange = true;
}

void Cell::update()
{
    if (shouldChange) {
        changeState();
        repaint();
    }
}

void Cell::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), color);
    QWidget::paintEvent(event);
    painter.end();
}

void Cell::mouseReleaseEvent(QMouseEvent *event)
{
    changeState();
    repaint();
    QWidget::mouseReleaseEvent(event);
}

unsigned Cell::countLiveNeighbors(const std::vector<std::vector<Cell *>> &cells)
{
    unsigned count = 0;
    size_t i_b = pos_i == 0 ? 0 : pos_i - 1;
    size_t j_b = pos_j == 0 ? 0 : pos_j - 1;

    size_t i_e = std::min((i_b + 3), cells.size());
    size_t j_e = std::min((j_b + 3), cells[0].size());

    for (size_t i = i_b; i < i_e; ++i) {
        for (size_t j = j_b; j < j_e; ++j) {
            if ((i != pos_i || j != pos_j) && cells[i][j]->isAlive()) {
                ++count;
            }
        }
    }
    return count;
}

void Cell::changeState()
{
    alive  = !alive;
    color = isAlive() ? Qt::green : Qt::red;
    shouldChange = false;
}

