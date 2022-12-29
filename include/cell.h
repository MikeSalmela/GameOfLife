#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QWidget>

#include <vector>

/*
 * \class Cell
 * \brief Represent single cell with UI and states.
 *
 * Offers two different modes of operation, counting the living neighbour cells when ordered to
 * with countLivingNeighbours() or keeping track of them by notifyNeighbours() cells every time a cell changes state.
 * Operation mode is defined by boolean notify, where notifyNeighbours mode is on when said variable is true.
 */

class Cell : public QWidget
{
    Q_OBJECT

public:
    Cell(unsigned i, unsigned j, bool notify, std::vector<std::vector<Cell*>> *cells, QWidget *parent = nullptr);

    // Check neighbouring cells and update value of should change
    void checkIfShouldChange();

    // Change alive state if it should change
    void update();

    void addLivingNeighbour();
    void removeLivingNeighbor();

    bool isAlive() const { return alive; }
    void setAlive();

    void paintEvent(QPaintEvent *event) override;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void changeState();
    void notifyNeighbours();
    unsigned countLivingNeighbours();

    bool alive {false};
    bool shouldChange {false};
    QColor color {Qt::red};

    size_t pos_i;
    size_t pos_j;
    bool notify {false};

    const std::vector<std::vector<Cell*>> *cells;
    char livingNeighbours = 0;
};

#endif // CELL_H
