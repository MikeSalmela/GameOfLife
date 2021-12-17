#include "cell.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <math.h>

Cell::Cell(unsigned i, unsigned j, std::vector<std::vector<Cell*>> *cells, QWidget *parent) :
    QWidget(parent), pos_i(i), pos_j(j), cells(cells)
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

void Cell::addLivingNeighbor()
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
    qDebug() << (int)livingNeighbours;
    QWidget::mouseReleaseEvent(event);
}

void Cell::changeState()
{
    alive = !alive;
    notifyNeighbors();
    // For algorithm performance testing without displaying
    #if NO_UI == 0
        color = isAlive() ? Qt::green : Qt::red;
        repaint();
    #endif
}

void Cell::notifyNeighbors()
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
                    (*cells)[i][j]->addLivingNeighbor();
                } else {
                    (*cells)[i][j]->removeLivingNeighbor();
                }
            }
        }
    }
}

