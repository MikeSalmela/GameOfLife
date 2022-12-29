#include "../include/cell.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <math.h>

Cell::Cell(unsigned i, unsigned j, bool notify, std::vector<std::vector<Cell*>> *cells, QWidget *parent) :
    QWidget(parent), pos_i(i), pos_j(j), notify(notify), cells(cells)
{
}

void Cell::update()
{
    if (shouldChange) {
        changeState();
        shouldChange = false;
    }
}

void Cell::checkIfShouldChange()
{
    if (!notify) {
        livingNeighbours = countLivingNeighbours();
    }

    if (!isAlive() && livingNeighbours == 0) {
        return;
    } else if (!isAlive() && livingNeighbours == 3) {
        shouldChange = true;
    } else if (isAlive() && (livingNeighbours <= 1 || livingNeighbours >=4)) {
        shouldChange = true;
    }
}

void Cell::setAlive()
{
    if (!isAlive()) {
        changeState();
    }
}

void Cell::addLivingNeighbour()
{
    ++livingNeighbours;
}

void Cell::removeLivingNeighbor()
{
    if (livingNeighbours > 0) {
        --livingNeighbours;
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
    QWidget::mouseReleaseEvent(event);
}

void Cell::changeState()
{
    alive = !alive;
    if (notify) {
        notifyNeighbours();
    }
    // For algorithm performance testing without displaying
    #if NO_UI == 0
        color = isAlive() ? Qt::green : Qt::red;
        repaint();
    #endif
}

void Cell::notifyNeighbours()
{
    // Beginning index
    size_t i_b = (pos_i == 0 ? 0 : pos_i - 1);
    size_t j_b = (pos_j == 0 ? 0 : pos_j - 1);

    // End index
    size_t i_e = std::min((pos_i + 2), (*cells).size());
    size_t j_e = std::min((pos_j + 2), (*cells)[0].size());

    for (size_t i = i_b; i < i_e; ++i) {
        for (size_t j = j_b; j < j_e; ++j) {
            if ((i != pos_i || j != pos_j)) {
                if (isAlive()) {
                    (*cells)[i][j]->addLivingNeighbour();
                } else {
                    (*cells)[i][j]->removeLivingNeighbor();
                }
            }
        }
    }
}

// Brute loop through all neighbours
unsigned Cell::countLivingNeighbours()
{
    unsigned count = 0;
    // Beginning index
    size_t i_b = pos_i == 0 ? 0 : pos_i - 1;
    size_t j_b = pos_j == 0 ? 0 : pos_j - 1;

    // End index
    size_t i_e = std::min((pos_i + 2), (*cells).size());
    size_t j_e = std::min((pos_j + 2), (*cells)[0].size());

    for (size_t i = i_b; i < i_e; ++i) {
        for (size_t j = j_b; j < j_e; ++j) {
            if ((i != pos_i || j != pos_j) && (*cells)[i][j]->isAlive()) {
                ++count;
            }
        }
    }
    return count;
}
